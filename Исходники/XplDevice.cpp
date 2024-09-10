bool XplDevice::HandleMsgForUs
(
    XplMsg* _pMsg
)
{
    if ( _pMsg->GetType() == XplMsg::c_xplCmnd )
    {
        if ( "config" == _pMsg->GetSchemaClass() )
        {
            poco_debug ( devLog, "config message");
            if ( "current" == _pMsg->GetSchemaType() )
            {
                // Config values request
                if ( "request" == toLower ( _pMsg->GetValue ( "command" ) ) )
                {
                    SendConfigCurrent();
                    return true;
                }
            }
            else if ( "list" == _pMsg->GetSchemaType() )
            {
                // Config list request
                if ( string ( "request" ) == toLower ( _pMsg->GetValue ( "command" ) ) )
                {
                    SendConfigList();
                    return true;
                }
            }
            else if ( "response" == _pMsg->GetSchemaType() )
            {
                uint32 i;
                for ( i=0; i<m_configItems.size(); ++i )
                {
                    // Clear the existing config item values
                    XplConfigItem* pItem = m_configItems[i];
                    pItem->ClearValues();

                    // Copy all the new values from the message into the config item
                    XplMsgItem const* pValues = _pMsg->GetMsgItem ( pItem->GetName() );
                    if ( NULL != pValues )
                    {
                        for ( uint32 j=0; j<pValues->GetNumValues(); ++j )
                        {
                            string value = pValues->GetValue ( j );
                            if ( !value.empty() )
                            {
                                pItem->AddValue ( value );
                            }
                        }
                    }
                }

                // Configure the XplDevice
                Configure();

                // Save configuration
                SaveConfig();
                m_bConfigRequired = false;

                // Set the config event
                //SetEvent( m_hConfig );
//         m_hConfig->set();
                //configTaskManager.start(new SampleTask("ConfigTask"));
                cout << "posted reconfig from thread " << Thread::currentTid()  << "\n";
                configNotificationCenter.postNotification ( new DeviceConfigNotification() );
                cout << "posted reconfig from thread " << Thread::currentTid()  << "\n";

                // Send a heartbeat so everyone gets our latest status
                m_pComms->SendHeartbeat ( m_completeId, m_heartbeatInterval, m_version );
                SetNextHeartbeatTime();
                return true;
            }
        }
        else if ( "hbeat" == _pMsg->GetSchemaClass() )
        {
            if ( "request" == _pMsg->GetSchemaType() )
            {
                // We've been asked to send a heartbeat
                if ( m_bConfigRequired )
                {
                    // Send a config heartbeat
                    m_pComms->SendConfigHeartbeat ( m_completeId, m_heartbeatInterval, m_version );
                }
                else
                {
                    // Send a heartbeat
                    m_pComms->SendHeartbeat ( m_completeId, m_heartbeatInterval, m_version );
                }

                // Calculate the time of the next heartbeat
                SetNextHeartbeatTime();
            }
        }
    }

    return false;
}