void CPushable::StopSound( void )
{
	Vector dist = pev->oldorigin - pev->origin;
	if ( dist.Length() <= 0 )
		STOP_SOUND( ENT(pev), CHAN_WEAPON, m_soundNames[m_lastSound] );
}