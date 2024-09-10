char Facet::isVertexAbove(const Vertex & v) const
{
	Vector3F dv = *v.m_v - getCentroid();
	dv.normalize();
	return dv.dot(m_normal) > 0.0f;
}