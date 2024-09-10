void QGetEnv::VisitStmt(clang::Stmt *stmt)
{
    // Lets check only in function calls. Otherwise there are too many false positives, it's common
    // to implicit cast to bool when checking pointers for validity, like if (ptr)

    CXXMemberCallExpr *memberCall = dyn_cast<CXXMemberCallExpr>(stmt);
    if (!memberCall)
        return;

    CXXMethodDecl *method = memberCall->getMethodDecl();
    if (!method)
        return;

    CXXRecordDecl *record = method->getParent();
    if (!record || record->getNameAsString() != "QByteArray") {
        return;
    }

    std::vector<CallExpr *> calls = Utils::callListForChain(memberCall);
    if (calls.size() != 2)
        return;

    CallExpr *qgetEnvCall = calls.back();

    FunctionDecl *func = qgetEnvCall->getDirectCallee();

    if (!func || func->getNameAsString() != "qgetenv")
        return;

    string methodname = method->getNameAsString();
    string errorMsg;
    std::string replacement;
    if (methodname == "isEmpty") {
        errorMsg = "qgetenv().isEmpty() allocates.";
        replacement = "qEnvironmentVariableIsEmpty";
    } else if (methodname == "isNull") {
        errorMsg = "qgetenv().isNull() allocates.";
        replacement = "qEnvironmentVariableIsSet";
    } else if (methodname == "toInt") {
        errorMsg = "qgetenv().toInt() is slow.";
        replacement = "qEnvironmentVariableIntValue";
    }

    if (!errorMsg.empty()) {
        std::vector<FixItHint> fixits;
        if (isFixitEnabled(FixitAll)) {
            const bool success = FixItUtils::transformTwoCallsIntoOne(m_ci, qgetEnvCall, memberCall, replacement, fixits);
            if (!success) {
                queueManualFixitWarning(memberCall->getLocStart(), FixitAll);
            }
        }

        errorMsg += " Use " + replacement + "() instead";
        emitWarning(memberCall->getLocStart(), errorMsg.c_str(), fixits);
    }
}