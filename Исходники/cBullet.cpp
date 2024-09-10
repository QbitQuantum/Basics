void	cBullet::Update()
{ 
	if( m_pResourceFile->GetKey() == "virus" )
	{
		m_vRotation.y += 0.25f * D3DX_PI * _GETSINGLE( cSystemMgr )->GetDeltaTime();

	}
	if( m_vPos.z > 200.0f || m_vPos.z < -50.0f )
	{
		DestroyObject();
	}
	DirectionMove();
	DirectionRotation();
	Translation();
}