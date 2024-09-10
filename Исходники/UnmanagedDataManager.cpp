///////////////////////////////////////////////////////////////////////////////
/// \brief
/// Parses the filter into an MgStringCollection
///
void MgUnmanagedDataManager::ParseFilter(CREFSTRING filter, MgStringCollection* filters)
{
    if (!filter.empty())
    {
        wchar_t* token = const_cast<wchar_t*>(filter.c_str());
        const wchar_t* delimit = L";, \t\r\n\v\f";
        wchar_t* state = NULL;

        for (token = _wcstok(token, delimit, &state);
             token != NULL;
             token = _wcstok(NULL, delimit, &state))
        {
            filters->Add(token);
        }
    }
}