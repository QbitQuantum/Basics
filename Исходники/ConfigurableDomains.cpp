bool CConfigurableDomains::renameDomain(const string& strName, const string& strNewName, string& strError)
{
    CConfigurableDomain* pConfigurableDomain = findConfigurableDomain(strName, strError);

    if (!pConfigurableDomain) {

        return false;
    }

    log_info("Renaming configurable domain \"%s\" to \"%s\"", strName.c_str(), strNewName.c_str());

    // Rename
    return pConfigurableDomain->rename(strNewName, strError);
}