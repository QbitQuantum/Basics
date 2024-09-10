void RuleOfTwoSoft::VisitStmt(Stmt *s)
{
    CXXOperatorCallExpr *op = dyn_cast<CXXOperatorCallExpr>(s);
    if (op) {
        FunctionDecl *func = op->getDirectCallee();
        if (func && func->getNameAsString() == "operator=") {
            CXXMethodDecl *method = dyn_cast<CXXMethodDecl>(func);
            if (method && method->getParent()) {
                CXXRecordDecl *record = method->getParent();
                const bool hasCopyCtor = record->hasNonTrivialCopyConstructor();
                const bool hasCopyAssignOp = record->hasNonTrivialCopyAssignment();
                if (hasCopyCtor && !hasCopyAssignOp && !isBlacklisted(record)) {
                    string msg = "Using assign operator but class " + record->getQualifiedNameAsString() + " has copy-ctor but no assign operator";
                    emitWarning(s->getLocStart(), msg);
                }
            }
        }
    } else if (CXXConstructExpr *ctorExpr = dyn_cast<CXXConstructExpr>(s)) {
        CXXConstructorDecl *ctorDecl = ctorExpr->getConstructor();
        CXXRecordDecl *record = ctorDecl->getParent();
        if (ctorDecl->isCopyConstructor() && record) {
            const bool hasCopyCtor = record->hasNonTrivialCopyConstructor();
            const bool hasCopyAssignOp = record->hasNonTrivialCopyAssignment();
            if (!hasCopyCtor && hasCopyAssignOp && !isBlacklisted(record)) {
                string msg = "Using copy-ctor but class " + record->getQualifiedNameAsString() + " has a trivial copy-ctor but non trivial assign operator";
                emitWarning(s->getLocStart(), msg);
            }
        }
    }
}