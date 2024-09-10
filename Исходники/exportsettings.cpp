    bool ExportSettingsManager::MarshalAllSettings( CHAR* strDestBuffer, DWORD dwBufferSize, bool bNewLines, ExportSettingsEntry* pRoot )
    {
        bool bResult = true;
        if( !pRoot )
        {
            size_t dwRootCount = GetRootCategoryCount();
            for( size_t i = 0; i < dwRootCount; ++i )
            {
                bResult &= MarshalAllSettings( strDestBuffer, dwBufferSize, bNewLines, GetRootCategory( i ) );
            }
            return bResult;
        }

        if( pRoot->m_Type == ExportSettingsEntry::CT_CATEGORY && pRoot->m_pFirstChild )
        {
            bResult &= MarshalAllSettings( strDestBuffer, dwBufferSize, bNewLines, pRoot->m_pFirstChild );
        }
        else
        {
            size_t dwCurrentLen = strlen( strDestBuffer );
            CHAR* strCurrentSpot = strDestBuffer + dwCurrentLen;
            const CHAR* strSettingName = pRoot->m_CommandLineOptionName.SafeString();
            size_t dwNameLen = strlen( strSettingName );
            if( dwCurrentLen + dwNameLen + 1 > dwBufferSize )
                return false;
            strcat_s( strDestBuffer, dwBufferSize, strSettingName );
            strcat_s( strDestBuffer, dwBufferSize, "=" );
            dwCurrentLen += ( dwNameLen + 1 );

            switch( pRoot->m_CurrentValue.m_Type )
            {
            case ExportVariant::VT_STRING:
                {
                    const CHAR* strValue = pRoot->GetValueString();
                    size_t dwValueLen = strlen( strValue );
                    if( dwCurrentLen + dwValueLen + 1 > dwBufferSize )
                    {
                        *strCurrentSpot = '\0';
                        return false;
                    }
                    strcat_s( strDestBuffer, dwBufferSize, strValue );
                    break;
                }
            case ExportVariant::VT_INT:
            case ExportVariant::VT_BOOL:
                {
                    INT iValue = 0;
                    if( pRoot->m_CurrentValue.m_Type == ExportVariant::VT_BOOL )
                        iValue = pRoot->GetValueBool();
                    else
                        iValue = pRoot->GetValueInt();
                    CHAR strValue[32] = {0};
                    _itoa_s( iValue, strValue, 10 );
                    size_t dwValueLen = strlen( strValue );
                    if( dwCurrentLen + dwValueLen + 1 > dwBufferSize )
                    {
                        *strCurrentSpot = '\0';
                        return false;
                    }
                    strcat_s( strDestBuffer, dwBufferSize, strValue );
                    break;
                }
            case ExportVariant::VT_FLOAT:
                {
                    float fValue = pRoot->GetValueFloat();
                    CHAR strValue[32];
                    sprintf_s( strValue, "%0.5f", fValue );
                    size_t dwValueLen = strlen( strValue );
                    if( dwCurrentLen + dwValueLen + 1 > dwBufferSize )
                    {
                        *strCurrentSpot = '\0';
                        return false;
                    }
                    strcat_s( strDestBuffer, dwBufferSize, strValue );
                    break;
                }
            }
            if( bNewLines )
            {
                strcat_s( strDestBuffer, dwBufferSize, ";\n" );
            }
            else
            {
                strcat_s( strDestBuffer, dwBufferSize, ";" );
            }
        }

        if( pRoot->m_pSibling )
        {
            bResult &= MarshalAllSettings( strDestBuffer, dwBufferSize, bNewLines, pRoot->m_pSibling );
        }

        return bResult;
    }