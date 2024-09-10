void MeshManipulator::smoothSurface(const Ray * r)
{
	VertexAdjacency adj = m_topo->getAdjacency(m_intersect->m_componentIdx);
	
	Vector3F *p = &m_mesh->vertices()[m_intersect->m_componentIdx];
    Vector3F d = adj.center() - *p;
	*p += d * .7f;
	
	Plane pl(m_intersect->m_hitN, m_intersect->m_hitP);

    Vector3F hit;
    float t;
	if(!pl.rayIntersect(*r, hit, t, 1)) return;
	
	d = hit - *p;
	float minD = d.length();
	float curD;
	
	VertexAdjacency::VertexNeighbor *neighbor;
    for(neighbor = adj.firstNeighbor(); !adj.isLastNeighbor(); neighbor = adj.nextNeighbor()) {
        d = hit - *(neighbor->v->m_v);
        curD = d.length();
		if(curD < minD) {
			minD = curD;
			m_intersect->m_componentIdx = neighbor->v->getIndex();
		}
    }
}