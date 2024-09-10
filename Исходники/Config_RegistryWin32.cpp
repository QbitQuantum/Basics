long Win32Registry::getInt( const char *section,
                            const char *field,
                            const char *descriptive_field,
                            long default_val )
{
    DWORD val = default_val;
    DWORD size = sizeof( val );
    DWORD type;

    {
        // try read user setting

        if ( RegQueryValueExA(
                 m_user_key, field, 0, &type, (LPBYTE)&val, &size )
             != ERROR_SUCCESS || type != REG_DWORD )
        {
            // didnt work... try read machine key

            if ( RegQueryValueExA( m_machine_key,
                                   field,
                                   0,
                                   &type,
                                   (LPBYTE)&val,
                                   &size ) != ERROR_SUCCESS
                 || type != REG_DWORD )
            {
                // still didnt work. Use default
                // and write default to machine key

                RegSetValueExA( m_machine_key,
                                field,
                                0,
                                REG_DWORD,
                                (LPBYTE)&val,
                                sizeof( val ) );
            }
        }
    }

    return val;
}