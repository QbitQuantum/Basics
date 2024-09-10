bool CEditableElementCommon::intersect(const NLMISC::CVector &rayStart, const NLMISC::CVector &rayEnd, NLMISC::CVector &rayHit, const NLMISC::CMatrix &mat)
{
	//return true;
	//CMatrix mat = mesh()->getMatrix();
	CMatrix imat = mat;
	imat.invert();
	//rayEnd = imat * rayEnd;
	//rayStart = imat * rayStart;
	
	uint32 i;
	for(i = 0; i<NbFaces; i++)
	{
		CTriangle tri;
		tri.V0 = mat * Vertices[Indices[i*3+0]];
		tri.V1 = mat * Vertices[Indices[i*3+1]];
		tri.V2 = mat * Vertices[Indices[i*3+2]];
		
		CPlane p;
		p.make(tri.V0,tri.V1,tri.V2);
		CVector hit;
		bool res = tri.intersect(rayStart,rayEnd,hit,p);
		if(res)
		{
			rayHit = hit;
			return true;
		}
	}
	
	
	return false;
}