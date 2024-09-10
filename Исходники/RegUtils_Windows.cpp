        int Key::numValues() const
        {
            HKEY hKey;
            LONG lRtn = RegOpenKeyExW( m_hRootKey, m_wsPath.c_str(),
                                       0, KEY_QUERY_VALUE, &hKey );
            if (lRtn != ERROR_SUCCESS) {
                BP_THROW( "RegOpenKeyExW(" + wideToUtf8(m_wsPath)
                          + ") returned: " + bp::conv::toString( lRtn ) );
            }

            DWORD dwNumValues;
            lRtn = RegQueryInfoKeyW( hKey, NULL, NULL, NULL, NULL, NULL, NULL, 
                                     &dwNumValues,
                                     NULL, NULL, NULL, NULL );
            if (lRtn != ERROR_SUCCESS) {
                BP_THROW( "RegQueryInfoKeyW(" + wideToUtf8(m_wsPath)
                          + ") returned: " + bp::conv::toString( lRtn ) );
            }

            return static_cast<int>( dwNumValues );
        }