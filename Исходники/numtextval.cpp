static bool wxIsNumeric(const wxString& val)
{
    for (unsigned int i = 0; i < val.Length(); ++i)
    {
        // Allow for "," (French) as well as "." -- in future we should
        // use wxSystemSettings or other to do better localisation
        if (!wxIsNumeric(val[i]))
            return false;
    }

    return true;
}