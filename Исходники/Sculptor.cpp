void Sculptor::movePointsToward(const Vector3F & d, const float & fac, bool normalize, Vector3F * vmod)
{
	if(m_active->numSelected() < 1) return;
	Array<int, VertexP> * vs = m_active->vertices;
	
	Vector3F tod;
	float wei;
	vs->begin();
	while(!vs->end()) {
		
		VertexP * l = vs->value();
		wei = *l->index->t4;
		
		const Vector3F p0(*(l->index->t1));
		
		tod = d - *(l->index->t1);
		if(normalize) tod.normalize();
		*(l->index->t1) += tod * fac * wei * m_strength;
		if(vmod) {
			*(l->index->t1) += *vmod * wei * m_strength;
		}
	
		m_tree->displace(l, *(l->index->t1), p0);
		vs->next();
	}
}