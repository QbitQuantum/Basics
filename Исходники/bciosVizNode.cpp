void BCIViz::findNeighbours()
{
	if(!checkHull()) return;
	const int numTri = m_hull->getNumFace();
	
	Vector3F d;
	d.x = fDriverPos.x;
	d.y = fDriverPos.y;
	d.z = fDriverPos.z;
	
	d.normalize();
	
	m_hitTriangle = 0;
	for(int i = 0; i < numTri; i++)
	{
		Facet f = m_hull->getFacet(i);
		Vertex p0 = f.getVertex(0);
		
		const Vector3F nor = f.getNormal();
		
		float ddotn = d.dot(nor);
		
		if(ddotn < 10e-5 && ddotn > -10e-5) continue;
		
		float t = p0.dot(nor) / ddotn; 
		if(t < 0.f) continue;
		
		Vertex p1 = f.getVertex(1);
		Vertex p2 = f.getVertex(2);
		
		m_hitTriangle = i;
		m_hitP = d * t; 

		Vector3F e01 = p1 - p0;
		Vector3F e02 = p2 - p0;
		Vector3F tmp = e01.cross(e02);
		if(tmp.dot(nor) < 0.f) {
			Vertex sw = p1;
			p1 = p2;
			p2 = sw;
		}
		
		e01 = p1 - p0;
		Vector3F x0 = m_hitP - p0;
		
		Vector3F e12 = p2 - p1;
		Vector3F x1 = m_hitP - p1;
		
		Vector3F e20 = p0 - p2;
		Vector3F x2 = m_hitP - p2;
		
		neighbourId[0] = p0.getIndex();
		neighbourId[1] = p1.getIndex();
		neighbourId[2] = p2.getIndex();
		
		if(e01.cross(x0).dot(nor) < 0.f) continue;
		if(e12.cross(x1).dot(nor) < 0.f) continue;
		if(e20.cross(x2).dot(nor) < 0.f) continue;
		
		return;
	}
}