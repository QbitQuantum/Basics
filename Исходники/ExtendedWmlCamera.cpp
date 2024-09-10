void ExtendedWmlCamera::DollyZoom( float fDistance )
{
	Vector3f in(GetDirection());
	in.Normalize();
	Vector3f translate( in * fDistance );

	// if new camera point is past target point, ignore this dolly request
	Vector3f newEye = GetLocation() + translate;
	Vector3f normDir = GetDirection();
	normDir.Normalize();
	if ( newEye.Dot(normDir) < m_ptTarget.Dot(normDir) ) {

		if (!m_bUsePerspective)
			OrthoDollyZoom( fDistance );

		SetTargetFrame( GetLocation() + translate, GetLeft(), GetUp(), m_ptTarget );
	}
}