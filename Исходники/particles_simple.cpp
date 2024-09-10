//-----------------------------------------------------------------------------
// Purpose: Destructor
//-----------------------------------------------------------------------------
CParticleEffect::~CParticleEffect( void )
{
#if defined( _DEBUG )
	int index = g_ParticleEffects.Find( this );
	Assert( g_ParticleEffects.IsValidIndex(index) );
	g_ParticleEffects.Remove( index );
#endif
	// HACKHACK: Prevent re-entering the destructor, clear m_Flags.
	// For some reason we'll get a callback into NotifyRemove() after being deleted!
	// Investigate dangling pointer
	m_Flags = 0;

#if !defined( _XBOX )
	if ( ( m_nToolParticleEffectId != TOOLPARTICLESYSTEMID_INVALID ) && clienttools->IsInRecordingMode() )
	{
		KeyValues *msg = new KeyValues( "OldParticleSystem_Destroy" );
		msg->SetInt( "id", m_nToolParticleEffectId );
		msg->SetFloat( "time", gpGlobals->curtime );
		ToolFramework_PostToolMessage( HTOOLHANDLE_INVALID, msg );
		m_nToolParticleEffectId = TOOLPARTICLESYSTEMID_INVALID; 
	}
#endif
}