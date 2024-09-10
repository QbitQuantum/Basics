double Vertex::interpolateZ(const Coordinate &p, const Coordinate &p0, 
		const Coordinate &p1)
{
	double segLen = p0.distance(p1);
	double ptLen = p.distance(p0);
	double dz = p1.z - p0.z;
	double pz = p0.z + dz * (ptLen / segLen);
	return pz;
}