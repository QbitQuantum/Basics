bool ConvexPolyhedron3D::planeSplits(const Plane3D& p) const
{
	ClosedInterval x;
	x.setEmpty();
	Real vpos;
	for(int i=0; i<numVertices; i++)
	{
		vpos = p.distance(vertices[i]);
		x.expand(vpos);

		if(x.contains(Zero))
			return true;
	}

	return false;
}