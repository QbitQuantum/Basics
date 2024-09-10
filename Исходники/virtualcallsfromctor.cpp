SourceLocation VirtualCallsFromCTOR::containsVirtualCall(clang::CXXRecordDecl *classDecl, clang::Stmt *stmt, std::vector<Stmt*> &processedStmts)
{
    if (stmt == nullptr)
        return {};

    // already processed ? we don't want recurring calls
    if (std::find(processedStmts.cbegin(), processedStmts.cend(), stmt) != processedStmts.cend())
        return {};

    processedStmts.push_back(stmt);

    std::vector<CXXMemberCallExpr*> memberCalls;
    Utils::getChilds2<CXXMemberCallExpr>(stmt, memberCalls);

    for (CXXMemberCallExpr *callExpr : memberCalls) {
        CXXMethodDecl *memberDecl = callExpr->getMethodDecl();
        if (memberDecl == nullptr || dyn_cast<CXXThisExpr>(callExpr->getImplicitObjectArgument()) == nullptr)
            continue;

        if (memberDecl->getParent() == classDecl) {
            if (memberDecl->isPure()) {
                return callExpr->getLocStart();
            } else {
                if (containsVirtualCall(classDecl, memberDecl->getBody(), processedStmts).isValid())
                    return callExpr->getLocStart();
            }
        }
    }

    return {};
}