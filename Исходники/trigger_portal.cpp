//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTriggerPortal::DisabledThink( void )
{
	// If we've got no disabled entities left, we're done
	if ( !m_hDisabledForEntities.Count() )
	{
		SetContextThink( NULL, gpGlobals->curtime, TRIGGER_DISABLED_THINK );
		return;
	}

	for ( int i = m_hDisabledForEntities.Count()-1; i >= 0; i-- )
	{
		CBaseEntity *pEntity = m_hDisabledForEntities[i];
		if ( !pEntity || !IsTouchingPortal(pEntity) )
		{
			m_hDisabledForEntities.Remove(i);
		}
	}

	SetContextThink( &CTriggerPortal::DisabledThink, gpGlobals->curtime + 0.1, TRIGGER_DISABLED_THINK );
}