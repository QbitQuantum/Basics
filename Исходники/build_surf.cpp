bool	isInside(const CPolygon &poly, const NLPACS::CSurfElement &elem)
{
	uint	i, j;

	if (poly.getNumVertices() <= 2)
		return false;
	
	CVector		pnorm = (poly.Vertices[0]-poly.Vertices[1])^(poly.Vertices[2]-poly.Vertices[1]);
	pnorm.normalize();

	for (i=0; i<3; ++i)
	{
		const CVector	&v = (*elem.Vertices)[elem.Tri[i]];
		bool			inside = true;

		for (j=0; j<poly.Vertices.size(); ++j)
		{
			const CVector	&v0 = poly.Vertices[j],
							&v1 = (j == poly.Vertices.size()-1) ? poly.Vertices[0] : poly.Vertices[j+1];

			if ((pnorm^(v1-v0)) * (v-v1) > 0.0f)
			{
				inside = false;
				break;
			}
		}

		if (inside)
			return true;
	}
	return false;
}