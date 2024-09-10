static void arrange_indirection_tokens_between( wxString& type,
                                                wxString& identifier )
{
    // TBD:: FIXME:: return value of operators !

    while ( identifier[0u] == _T('*') ||
            identifier[0u] == _T('&')
          )
    {
        type += identifier[0u];
        identifier.erase(0,1);

        if ( !identifier.length() ) return;
    }
}