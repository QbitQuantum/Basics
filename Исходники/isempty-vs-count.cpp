void IsEmptyVSCount::VisitStmt(clang::Stmt *stmt)
{
    ImplicitCastExpr *cast = dyn_cast<ImplicitCastExpr>(stmt);
    if (!cast || cast->getCastKind() != clang::CK_IntegralToBoolean)
        return;

    CXXMemberCallExpr *memberCall = dyn_cast<CXXMemberCallExpr>(*(cast->child_begin()));
    CXXMethodDecl *method = memberCall ? memberCall->getMethodDecl() : nullptr;

    if (!StringUtils::functionIsOneOf(method, {"size", "count", "length"}))
        return;

    if (!StringUtils::classIsOneOf(method->getParent(), QtUtils::qtContainers()))
        return;

    emitWarning(stmt->getLocStart(), "use isEmpty() instead");
}