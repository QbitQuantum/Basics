//-----------------------------------------------------------------------------
void 
CameraPlugin::position3dCamera( AbstractLocalSpace& selected,
											float distance,
											float /*elevation*/ )
{
	if (&selected)
	{
		Vec3 direction = selected.position() - m_Camera.position();
		float fDirection = direction.length();
		if( fDirection > 0 )
		{
			direction /= fDirection;
			m_Camera.setForward( direction );
			m_Camera.regenerateOrthonormalBasisUF( m_Camera.forward() );
		}

		const Vec3 behind = selected.forward() * -distance;
		m_Camera.setPosition (selected.position() + behind);
		m_Camera.target = selected.position();
	}
	else
	{
		Vec3 forward = -Vec3::up + Vec3::forward;
		forward = forward.normalized();
		const Vec3 behind = forward * -distance;
		m_Camera.setPosition( behind );
		m_Camera.target = Vec3::zero;
	}

	m_Camera.doNotSmoothNextMove ();	
}