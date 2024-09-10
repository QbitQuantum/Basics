//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CDarknessLightSourcesSystem::RemoveLightSource( CInfoDarknessLightSource *pEntity )
{
	for ( int i = m_LightSources.Count() - 1; i >= 0; i-- )
	{
		if ( m_LightSources[i].hEntity == pEntity )
		{
			m_LightSources.Remove(i);
		}
	}
}