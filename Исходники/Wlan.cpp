bool Wlan::StartHostedNet( const char * ssid, const char * key, int maxPeers )
{
    bool result = false;

    if (OpenHandle()) {
        WLAN_HOSTED_NETWORK_REASON reason = {};
        WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS settings = {};

        settings.dwMaxNumberOfPeers = maxPeers;
        size_t ssidLen = strlen( ssid );
        settings.hostedNetworkSSID.uSSIDLength = ssidLen;
        memcpy( settings.hostedNetworkSSID.ucSSID, (void*) ssid, ssidLen );

        if (WlanHostedNetworkSetProperty(
            m_handle,
            WLAN_HOSTED_NETWORK_OPCODE::wlan_hosted_network_opcode_connection_settings,
            sizeof( WLAN_HOSTED_NETWORK_CONNECTION_SETTINGS ),
            &settings,
            &reason,
            NULL ) == ERROR_SUCCESS) {

            size_t keyLength = strlen( key ) + 1;

            if (WlanHostedNetworkSetSecondaryKey( m_handle, keyLength, (PUCHAR) key, TRUE, TRUE, &reason, NULL ) == ERROR_SUCCESS) {
                result = (WlanHostedNetworkStartUsing( m_handle, &reason, NULL ) == ERROR_SUCCESS);
            }
        }
    }

    return result;
}