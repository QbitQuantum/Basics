CFloatVector CFace::CalcCenterf (CModel* po)
{
	CFloatVector	*pv = po->m_vertsf.Buffer ();
	short				*pfv = m_verts;
	int				i;

	CFloatVector	c;

c.SetZero ();
for (i = m_nVerts; i; i--, pfv++)
	c += pv [*pfv];
c /= static_cast<float> (m_nVerts);
return c;
}