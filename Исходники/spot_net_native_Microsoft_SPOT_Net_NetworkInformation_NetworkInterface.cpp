HRESULT Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_NetworkInterface::GetNetworkInterface___STATIC__MicrosoftSPOTNetNetworkInformationNetworkInterface__U4( CLR_RT_StackFrame& stack )
{
    NATIVE_PROFILE_CLR_NETWORK();
    TINYCLR_HEADER();

    SOCK_NetworkConfiguration config; 
    CLR_UINT32                type = 0;
    CLR_RT_HeapBlock*         pConfig;
    CLR_UINT32                interfaceIndex = stack.Arg0().NumericByRef().u4;
    CLR_RT_HeapBlock&         top            = stack.PushValueAndClear();
    RSAKey*                   key            = NULL;

    TINYCLR_CLEAR(config);

    TINYCLR_CHECK_HRESULT(SOCK_CONFIGURATION_LoadConfiguration( interfaceIndex, &config ));    
        
    type = SOCK_NETWORKCONFIGURATION_FLAGS_TYPE__value(config.flags);
    
    switch(type)
    {
    case SOCK_NETWORKCONFIGURATION_FLAGS_NETWORK_INTERFACE:
        {
            TINYCLR_CHECK_HRESULT(g_CLR_RT_ExecutionEngine.NewObjectFromIndex( top, g_CLR_RT_WellKnownTypes.m_NetworkInterface ));
            break;
        }
    case SOCK_NETWORKCONFIGURATION_FLAGS_WIRELESS:
        {
            TINYCLR_CHECK_HRESULT(g_CLR_RT_ExecutionEngine.NewObjectFromIndex( top, g_CLR_RT_WellKnownTypes.m_Wireless80211 ));
            break;
        }
    default:
        {
            /// Unknown type, not supported.
            TINYCLR_SET_AND_LEAVE(CLR_E_FAIL);
            break;
        }
    }
    
    pConfig = top.Dereference(); FAULT_ON_NULL(pConfig);
    
    pConfig[ FIELD___flags                ].SetInteger( config.flags      );
    pConfig[ FIELD___ipAddress            ].SetInteger( config.ipaddr     );
    pConfig[ FIELD___gatewayAddress       ].SetInteger( config.gateway    );
    pConfig[ FIELD___subnetMask           ].SetInteger( config.subnetmask );
    pConfig[ FIELD___dnsAddress1          ].SetInteger( config.dnsServer1 );
    pConfig[ FIELD___dnsAddress2          ].SetInteger( config.dnsServer2 );    
    pConfig[ FIELD___networkInterfaceType ].SetInteger( config.networkInterfaceType );
    pConfig[ FIELD___interfaceIndex       ].SetInteger( interfaceIndex    );

    TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance( pConfig[ FIELD___macAddress ], config.macAddressLen, g_CLR_RT_WellKnownTypes.m_UInt8 ));   

    memcpy( pConfig[ FIELD___macAddress ].DereferenceArray()->GetFirstElement(), config.macAddressBuffer, config.macAddressLen );

    /// Type specific load.
    switch(type)
    {
    case SOCK_NETWORKCONFIGURATION_FLAGS_WIRELESS:
        {
            CLR_UINT32 wirelessIndex = SOCK_NETWORKCONFIGURATION_FLAGS_SUBINDEX__value(config.flags);
            SOCK_WirelessConfiguration wirelessConfig;
            
            TINYCLR_CHECK_HRESULT(SOCK_CONFIGURATION_LoadWirelessConfiguration( wirelessIndex, &wirelessConfig ));

            pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Authentication ].SetInteger( WIRELESS_FLAG_AUTHENTICATION__value(wirelessConfig.wirelessFlags) );
            pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Encryption     ].SetInteger( WIRELESS_FLAG_ENCRYPTION__value    (wirelessConfig.wirelessFlags) );
            pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Radio          ].SetInteger( WIRELESS_FLAG_RADIO__value         (wirelessConfig.wirelessFlags) );

            TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__NetworkKey ], wirelessConfig.networkKeyLength, g_CLR_RT_WellKnownTypes.m_UInt8 )); 
            TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_Array::CreateInstance( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__ReKeyInternal ], wirelessConfig.reKeyLength, g_CLR_RT_WellKnownTypes.m_UInt8 )); 

            UINT32 dataFlag = WIRELESS_FLAG_DATA__value(wirelessConfig.wirelessFlags);
            if (dataFlag & WIRELESS_FLAG_DATA_ENCRYPTED)
            {
                key = RetrieveWirelessEncryptionKey();
            }

            if (key == NULL)
            {   
                wirelessConfig.passPhrase[ WIRELESS_PASSPHRASE_LENGTH - 1 ] = 0;
                TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_String::CreateInstance( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__PassPhrase ], wirelessConfig.passPhrase ));                
                if(wirelessConfig.networkKeyLength > 0)
                {
                    memcpy( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__NetworkKey ].DereferenceArray()->GetFirstElement(), wirelessConfig.networkKey, wirelessConfig.networkKeyLength );                
                }
                if(wirelessConfig.reKeyLength > 0)
                {
                    memcpy( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__ReKeyInternal ].DereferenceArray()->GetFirstElement(), wirelessConfig.reKeyInternal, wirelessConfig.reKeyLength );
                }
            }
            else
            {   
                char passPhrase[ WIRELESS_PASSPHRASE_LENGTH ];
                
                Decrypt( (BYTE *)key, (BYTE *)wirelessConfig.passPhrase, WIRELESS_PASSPHRASE_LENGTH - 1, (BYTE *)passPhrase, WIRELESS_PASSPHRASE_LENGTH - 1 );
                passPhrase[ WIRELESS_PASSPHRASE_LENGTH - 1 ] = 0;
                TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_String::CreateInstance( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__PassPhrase ], passPhrase ));

                if(wirelessConfig.networkKeyLength > 0)
                {
                    Decrypt( (BYTE *)key, (BYTE *)wirelessConfig.networkKey, wirelessConfig.networkKeyLength, pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__NetworkKey ].DereferenceArray()->GetFirstElement(), wirelessConfig.networkKeyLength );
                }

                if(wirelessConfig.reKeyLength > 0)
                {
                    Decrypt( (BYTE *)key, (BYTE *)wirelessConfig.reKeyInternal, wirelessConfig.reKeyLength, pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__ReKeyInternal ].DereferenceArray()->GetFirstElement(), wirelessConfig.reKeyLength );                
                }
            }

            TINYCLR_CHECK_HRESULT(CLR_RT_HeapBlock_String::CreateInstance( pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Ssid ], wirelessConfig.ssid ));                

            pConfig[ Library_spot_net_native_Microsoft_SPOT_Net_NetworkInformation_Wireless80211::FIELD__Id ].SetInteger( wirelessIndex );

            break;
        }
    default:
        {
            break;
        }
    }

        
    TINYCLR_NOCLEANUP();
}