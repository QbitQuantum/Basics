        std::string createGUID32()
        {
            UUID guid;
            std::memset( &guid, 0, sizeof( UUID ) );

            RPC_STATUS status = UuidCreateSequential( &guid );
            if( RPC_S_OK != status )
            {
                throw E_UNEXPECTED;
            }

            //m_guid = guid;

            //UUID m_guid;
            WCHAR* wzGuid;
            HRESULT hr = StringFromCLSID( guid, &wzGuid );
            if( FAILED( hr ) )
            {
                throw hr;
            }

            std::wstring guid_wstr( wzGuid );
            guid_wstr = guid_wstr.substr( 1, guid_wstr.length() - 2 );
            std::string guid_str( guid_wstr.begin(), guid_wstr.end() );
            return guid_str;
        }