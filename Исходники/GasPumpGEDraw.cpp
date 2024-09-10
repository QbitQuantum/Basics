void GasPumpGEDraw::update()
{
	AcGeVector3d v = m_endPt - m_startPt;
	v.normalize();
	m_angle = v.angleTo( AcGeVector3d::kXAxis, -AcGeVector3d::kZAxis );
}