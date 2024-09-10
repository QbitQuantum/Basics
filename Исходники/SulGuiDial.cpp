bool CSulGuiDial::eventMouseRelease( CSulGuiCanvas* pCanvas, float local_x, float local_y, float x, float y )
{
	// NOTE: because we have flipped the y-axis to have 0,0 in top,left corner.. means that the degress for
	// circle is also flipped on the y-axis. which means that our angle calculation is going clockwise.
	// we need to fix this when presenting this value to the user of this class.
	float w = getW();
	float h = getH();

	float xx = local_x - (w/2.0f);
	float yy = local_y-(h/2.0f);

	float a = atan2( yy, xx );
	
	m_deg = sigma::RAD2DEG( a );

	if ( m_deg<0 )
		m_deg = 180.0f + (180.0f+m_deg);

	osg::Quat q( sigma::DEG2RAD(m_deg), osg::Vec3(0,0,1) );
	osg::Matrix m = m_mt->getMatrix();
	m.setRotate( q );
	m_mt->setMatrix( m );

	return true;
}