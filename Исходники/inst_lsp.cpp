//------------------------------------------------------------------------
//  InstallNewChain()
//
//------------------------------------------------------------------------
int InstallNewChain( LPWSAPROTOCOL_INFOW BaseProtocolInfoBuff,
                     DWORD               dwLayeredProviderCatalogId )
    {
    int               iStatus = ERROR_SUCCESS;
    int               iError = ERROR_SUCCESS;
    WSAPROTOCOL_INFOW ProtocolChainProtoInfo;
    

    // See if we are layering on top of base provider or a chain

    if (BaseProtocolInfoBuff->ProtocolChain.ChainLen == BASE_PROTOCOL)
        {
        // Layering on top of a base protocol:

        ProtocolChainProtoInfo = *BaseProtocolInfoBuff;

        ProtocolChainProtoInfo.ProviderId = RestrictedProviderChainId;
        
        if ( (wcslen(BaseProtocolInfoBuff->szProtocol) + wcslen(CHAIN_PREFIX))
           > WSAPROTOCOL_LEN )
            {
            // The name will be too long use a simpler one...
            wcscpy( ProtocolChainProtoInfo.szProtocol,
                    SIMPLE_CHAIN_NAME );
            }
        else
            {
            wcscpy( ProtocolChainProtoInfo.szProtocol,
                    CHAIN_PREFIX );
            wcscat( ProtocolChainProtoInfo.szProtocol,
                    BaseProtocolInfoBuff->szProtocol );
            }
     
        ProtocolChainProtoInfo.ProtocolChain.ChainLen = 2;
        ProtocolChainProtoInfo.ProtocolChain.ChainEntries[0]
                = dwLayeredProviderCatalogId;
        ProtocolChainProtoInfo.ProtocolChain.ChainEntries[1]
                = BaseProtocolInfoBuff->dwCatalogEntryId;
            
        iStatus = WSCInstallProvider( (GUID*)&RestrictedProviderChainId,
                                      LSP_PATH,
                                      &ProtocolChainProtoInfo,
                                      1,
                                      &iError );
        }
    else
        {
        // Layering on top of an existing chain:

        if (BaseProtocolInfoBuff->ProtocolChain.ChainLen >= MAX_PROTOCOL_CHAIN)
            {
            // The chain is going to be too long...
            return SOCKET_ERROR;
            }

        ProtocolChainProtoInfo = *BaseProtocolInfoBuff;

        ProtocolChainProtoInfo.ProviderId = RestrictedProviderChainId;

        if ( (wcslen(BaseProtocolInfoBuff->szProtocol) + wcslen(CHAIN_PREFIX))
           > WSAPROTOCOL_LEN )
            {
            // The name will be too long use a simpler one...
            wcscpy( ProtocolChainProtoInfo.szProtocol,
                    SIMPLE_CHAIN_NAME );
            }
        else
            {
            wcscpy( ProtocolChainProtoInfo.szProtocol,
                    CHAIN_PREFIX );
            wcscat( ProtocolChainProtoInfo.szProtocol,
                    BaseProtocolInfoBuff->szProtocol );
            }

        ProtocolChainProtoInfo.ProtocolChain.ChainLen
                = 1 + BaseProtocolInfoBuff->ProtocolChain.ChainLen;

        ProtocolChainProtoInfo.ProtocolChain.ChainEntries[0]
                = dwLayeredProviderCatalogId;

        for (int i=0; i<BaseProtocolInfoBuff->ProtocolChain.ChainLen; i++)
            {
            ProtocolChainProtoInfo.ProtocolChain.ChainEntries[1+i]
                = BaseProtocolInfoBuff->ProtocolChain.ChainEntries[i];
            }

        iStatus = WSCInstallProvider( (GUID*)&RestrictedProviderChainId,
                                      LSP_PATH,
                                      &ProtocolChainProtoInfo,
                                      1,
                                      &iError );
        }

    return iStatus;
    }