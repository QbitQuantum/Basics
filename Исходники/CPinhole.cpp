CVector3D CPinhole::Ray_Direction(CPoint2D _pt) const {
	CVector3D direction = m_u * _pt.x + m_v * _pt.y - m_w * m_d;
	direction.Normalize();
	return direction;
}