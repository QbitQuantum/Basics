void CParticleSystemQuery::PostSimulate( ) 
{
#if defined( CLIENT_DLL )
	TProjectedTextureInfo *pInfo;

	while( m_ProjectedInfoAdds.PopItem( &pInfo ) == true )
	{
		m_ActiveProjectedInfos.AddToTail( pInfo );
	}

	for( int i = 0; i < m_ActiveProjectedInfos.Count(); i++ )
	{
		if ( m_ActiveProjectedInfos[ i ]->m_bUsedThisFrame == false )
		{
			delete m_ActiveProjectedInfos[ i ]->m_pEntity;
			m_ActiveProjectedInfos.Remove( i );
			i--;
			continue;
		}
		if ( m_ActiveProjectedInfos[ i ]->m_pEntity == NULL )
		{
			m_ActiveProjectedInfos[ i ]->m_pEntity = C_EnvProjectedTexture::Create();
		}

		m_ActiveProjectedInfos[ i ]->m_pEntity->SetAbsOrigin( m_ActiveProjectedInfos[ i ]->m_vOrigin );
		m_ActiveProjectedInfos[ i ]->m_pEntity->SetMaterial( m_ActiveProjectedInfos[ i ]->m_pMaterial );
		m_ActiveProjectedInfos[ i ]->m_pEntity->SetLightColor( m_ActiveProjectedInfos[ i ]->m_r * 255, m_ActiveProjectedInfos[ i ]->m_g * 255, m_ActiveProjectedInfos[ i ]->m_b * 255, m_ActiveProjectedInfos[ i ]->m_a * 255 );
		m_ActiveProjectedInfos[ i ]->m_pEntity->SetSize( m_ActiveProjectedInfos[ i ]->m_flSize );
		m_ActiveProjectedInfos[ i ]->m_pEntity->SetRotation( m_ActiveProjectedInfos[ i ]->m_flRotation );
	}
#endif // #if defined( CLIENT_DLL )
}