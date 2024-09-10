// ------------------------------------------------------------------------------------------------
IfcVector3 TempMesh::ComputePolygonNormal(const IfcVector3* vtcs, size_t cnt, bool normalize)
{
	std::vector<IfcFloat> temp((cnt+2)*3);
	for( size_t vofs = 0, i = 0; vofs < cnt; ++vofs )
	{
		const IfcVector3& v = vtcs[vofs];
		temp[i++] = v.x;
		temp[i++] = v.y;
		temp[i++] = v.z;
	}

	IfcVector3 nor;
	NewellNormal<3, 3, 3>(nor, cnt, &temp[0], &temp[1], &temp[2]);
	return normalize ? nor.Normalize() : nor;
}