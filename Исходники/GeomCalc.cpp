 // if the point is on the left of the triangle, then it is in the triangle
BOOL CPoint3D::IsInTheTriangle(CPoint3D p1, CPoint3D p2, CPoint3D p3) const
{
	CVector3D normal = (p2-p1)*(p3-p2);
	normal.Normalize();
	if (	this->IsAtTheLeftOf(p1, p2, normal)==0 ||
			this->IsAtTheLeftOf(p2, p3, normal)==0 ||
			this->IsAtTheLeftOf(p3, p1, normal)==0)
	{
		return 0;				//one the triangle's side
	}
	else
	{
		if (	this->IsAtTheLeftOf(p1, p2, normal)==1 &&
				this->IsAtTheLeftOf(p2, p3, normal)==1 &&
				this->IsAtTheLeftOf(p3, p1, normal)==1	)
		{
			return 1;			//in the triangle
		}
		else
			return -1;			//out the triangle
	}
}