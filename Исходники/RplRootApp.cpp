void CRplRootApp::Run()
{
	CSimpleTimer oFarCfgIniTimer;
	int nFarCfgIniLastModification = GetLastModificationOfFile(FAR_CFG_INI);
        struct stat statBuffer;

	registerToNMS();

	while (!CApp::IsStop())
	{
		TouchPidFile(g_pApp->m_szAppPidFile);

                if(stat(NET_DESTROY_LINKB, &statBuffer) == 0)
                {
                    SimpleMac_SendNetworkDestroy();
                    remove(NET_DESTROY_LINKB);
                }
		//
		ipv6_stack_poll();
        netifs_poll();
        udp_ipv6_poll();

#ifdef _6LPND_SUPPORT
		CheckSignals();
		SixLPRPCDiscOutR_RunStep();
		continue;
#endif

		if ( m_oConsolidatedMsgCheckTimer.IsSignaling() )
		{
#ifdef STORING_MODE
			if ( RplInstance_ModeOfOperation( &g_oRplInstance ) >= MOP_STORING_WITHOUT_MULTICAST &&
				 !g_oRplInstance.m_oRplConfig.m_u8TopologyInStoringMode )
			{
				CheckRIBForNotifications( );
			}
			else
#endif
			{
				if ( !m_shpoCnsDaoMsg->OptionListEmpty( ) )
				{
					m_pMgmtClientLink->SendMessage( m_shpoCnsDaoMsg );
					// clear message -> reused
					m_shpoCnsDaoMsg->OptionListReset( );
				}
			}

			if ( !m_shpoCnsTopoNotifMsg->OptionListEmpty( ) )
			{
				m_pMgmtClientLink->SendMessage( m_shpoCnsTopoNotifMsg );
				// clear message -> reused
				m_shpoCnsTopoNotifMsg->OptionListReset( );
                m_shpoCnsTopoNotifMsg->m_uSendMaxRetries = DEFAULT_SEND_MAX_RETRIES;
			}

			m_oConsolidatedMsgCheckTimer.SetTimer( m_stCfg.m_nConsolidatedMsgIntervalSec * 1000 );
		}

		RplInstance_RunStep(&g_oRplInstance);

        m_oNetStat.Poll();

		if (m_oTopologyCleanupTimer.GetElapsedSec() >= m_stCfg.m_nRplTopologyCleanupIntervalSec)
        {
            if ( m_pRplTopology->CleanupTopology ( &NotifyIsActiveInRplTopology ) )
				m_pRplTopology->SaveNodesNo();

			m_oTopologyCleanupTimer = CMicroSec();
		}

        if ( m_oShortAddrMapCleanupTimer.GetElapsedSec ( ) >= m_stCfg.m_nShortAddrMapIntervalSec / 2 )
        {
            m_oShortAddrMgr.Cleanup ( m_stCfg.m_nShortAddrMapIntervalSec );
            m_oShortAddrMapCleanupTimer = CMicroSec ( );
        }

		m_pRplTopology->UpdateIfDirty(UPDATE_EMERG_NONE);

		CheckSignals();

		if (g_pApp->m_stCfg.m_nTopologyMgmtMsgsEnabled)
		{
			MgmtProtocol::CMgmtPMessage::Ptr pMsg = m_pMgmtClientLink->ReadMessage();
			if (pMsg != NULL)
			{	RplRootProcessor_AcceptMgmtMessage(pMsg);
			}
		}

		if ( oFarCfgIniTimer.IsSignaling( ) )
		{
			oFarCfgIniTimer.SetTimer( FAR_CFG_INI_CHECK_MS );

			int nNewFarCfgIniLastModification = GetLastModificationOfFile( FAR_CFG_INI );
			if ( nNewFarCfgIniLastModification > nFarCfgIniLastModification )
			{
				NLOG_INFO( "Reload "FAR_CFG_INI", new_modif=%d>last_modif=%d", nNewFarCfgIniLastModification, nFarCfgIniLastModification );
				ReloadConfiguration( );
				nFarCfgIniLastModification = nNewFarCfgIniLastModification;
			}
		}

	}
}