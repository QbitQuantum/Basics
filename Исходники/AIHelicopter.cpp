AI_Helicopter::~AI_Helicopter()
{
	FREE_HSTRING(m_hstrDeathMessage);
	FREE_HSTRING(m_hstrDeath0_3rdMessage);
	FREE_HSTRING(m_hstrDeath1_3rdMessage);
	FREE_HSTRING(m_hstrDeath2_3rdMessage);

	if ( m_pHelicopterState )
	{
		FACTORY_DELETE(m_pHelicopterState);
        m_pHelicopterState = LTNULL;
        m_pVehicleState = LTNULL;
        m_pState = LTNULL;
	}

	if ( -1 != m_iObjectGunner && m_apObjects[m_iObjectGunner] )
	{
		HOBJECT hGunner = m_apObjects[m_iObjectGunner]->m_hObject;
		if ( hGunner )
		{
			CCharacter* pGunner = (CCharacter*)g_pLTServer->HandleToObject(hGunner);
			if ( pGunner )
			{
				Unlink(hGunner);
				pGunner->RemoveObject();
			}
		}
	}
}