bool ReferencesResolver::resolve(ASTNode const& _root)
{
    try
    {
        _root.accept(*this);
    }
    catch (FatalError const&)
    {
        solAssert(m_errorOccurred, "");
    }
    return !m_errorOccurred;
}