// Catch existing reserves
bool ReserveCandidates::registerReserveStatement(Stmt *stm)
{
    auto memberCall = dyn_cast<CXXMemberCallExpr>(stm);
    if (!memberCall)
        return false;

    CXXMethodDecl *methodDecl = memberCall->getMethodDecl();
    if (!methodDecl || methodDecl->getNameAsString() != "reserve")
        return false;

    CXXRecordDecl *decl = methodDecl->getParent();
    if (!QtUtils::isAReserveClass(decl))
        return false;

    ValueDecl *valueDecl = Utils::valueDeclForMemberCall(memberCall);
    if (!valueDecl)
        return false;

    if (!clazy_std::contains(m_foundReserves, valueDecl))
        m_foundReserves.push_back(valueDecl);

    return true;
}