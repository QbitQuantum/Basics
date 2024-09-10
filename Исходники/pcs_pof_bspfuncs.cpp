// Please only call this on triangulated meshes.. that makes the rest of my coding easier
void SplitIntersecting(std::vector<pcs_polygon> &polygons, vector3d plane_point, vector3d plane_normal)
{
	std::vector<pcs_polygon> newpolys;
	unsigned int i;
	for (i = 0; i < polygons.size(); i++)
	{
		if (Intersects(polygons[i], plane_point, plane_normal))
		{
			SplitPolygon(polygons, i, plane_point, plane_normal, newpolys);
		}
	}
	// add new polygons

	int in = polygons.size();
	polygons.resize(in+newpolys.size());
	for (i = 1; i < newpolys.size(); i++)
	{
		polygons[in+i] = newpolys[i];
	}
}