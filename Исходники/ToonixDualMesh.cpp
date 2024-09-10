void TXDualEdge::Project(TXOctree *dualmesh, TXEdge* edge) 
{
	if(edge->m_triangles.size()!=2)
	{
		edge->m_isboundary = true;
		return;
	}

	TXTriangle* t1 = edge->m_triangles[0];
	TXTriangle* t2 = edge->m_triangles[1];

	CVector3f tn1 = t1->m_norm;
	CVector3f tn2 = t2->m_norm;

	float ff = tn1.Dot(tn2);
	bool fac = (ff > 0);

	CVector4f n1(tn1.GetX(),tn1.GetY(),tn1.GetZ(),-tn1.Dot(t1->m_v[0]->m_pos));
	CVector4f N1;
	N1.Absolute(n1);

	CVector4f n2(tn2.GetX(),tn2.GetY(),tn2.GetZ(),-tn2.Dot(t2->m_v[0]->m_pos));
	CVector4f N2;
	N2.Absolute(n2);

	CVector4f n;
	n.Sub(n2,n1);

	float t[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};

	// if the edge should be projected on two surfaces, it will intersect
	// the plane passing orig and the intersection line of the two surfaces
	// these are the 12 possible intersections
	if (n.GetX() - n.GetY() != 0) t[1] = - (n1.GetX() - n1.GetY()) / (n.GetX() - n.GetY());
	if (n.GetX() - n.GetZ() != 0) t[2] = - (n1.GetX() - n1.GetZ()) / (n.GetX() - n.GetZ());
	if (n.GetX() - n.GetW() != 0) t[3] = - (n1.GetX() - n1.GetW()) / (n.GetX() - n.GetW());
	if (n.GetX() + n.GetY() != 0) t[4] = - (n1.GetX() + n1.GetY()) / (n.GetX() + n.GetY());
	if (n.GetX() + n.GetZ() != 0) t[5] = - (n1.GetX() + n1.GetZ()) / (n.GetX() + n.GetZ());
	if (n.GetX() + n.GetW() != 0) t[6] = - (n1.GetX() + n1.GetW()) / (n.GetX() + n.GetW());
	if (n.GetY() - n.GetZ() != 0) t[7] = - (n1.GetY() - n1.GetZ()) / (n.GetY() - n.GetZ());
	if (n.GetY() - n.GetW() != 0) t[8] = - (n1.GetY() - n1.GetW()) / (n.GetY() - n.GetW());
	if (n.GetY() + n.GetZ() != 0) t[9] = - (n1.GetY() + n1.GetZ()) / (n.GetY() + n.GetZ());
	if (n.GetY() + n.GetW() != 0)t[10] = - (n1.GetY() + n1.GetW()) / (n.GetY() + n.GetW());
	if (n.GetZ() - n.GetW() != 0)t[11] = - (n1.GetZ() - n1.GetW()) / (n.GetZ() - n.GetW());
	if (n.GetZ() + n.GetW() != 0)t[12] = - (n1.GetZ() + n1.GetW()) / (n.GetZ() + n.GetW());

	int p1 = 0, p2;
	while (p1 < 13) 
	{
		p2 = 13;
		for (int i=1; i<13; i++) 
		{
			if (t[i] > t[p1] && t[i] < t[p2])p2 = i;
		}

		// the part that is projected on one of the surfaces
		CVector4f pos1, pos2;
		pos1.ScaleAdd(t[p1],n,n1);
		pos2.ScaleAdd(t[p2],n,n1);


		CVector4f mid;
		mid.Add(pos1,pos2);
		mid.ScaleInPlace(0.5);

		CVector4f MID;
		MID.Absolute(mid);

		p1 = p2;

		// the surface projected on
		int tp;
		if (MID.GetX() >= MID.GetY() && MID.GetX() >= MID.GetZ() && MID.GetX() >= MID.GetW())
		  tp = MID.GetX() > 0 ? PX : NX;
		else if (MID.GetY() >= MID.GetZ() && MID.GetY() >= MID.GetW())
		  tp = MID.GetY() > 0 ? PY : NY;
		else if (MID.GetZ() >= MID.GetW())
		  tp = MID.GetZ() > 0 ? PZ : NZ;
		else
		  tp = MID.GetW() > 0 ? PW : NW;

		// project this part on the surface
		TXDualEdge *dualedge = new TXDualEdge(edge, fac,tp, pos1, pos2);
		dualmesh[tp].Insert(dualedge);
	}

}