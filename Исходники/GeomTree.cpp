void GeomTree::RayTriIntersect(int numRays, const vector3f &origin, const vector3f *dirs, int triIdx, isect_t *isects) const
{
	const vector3f a(m_vertices[m_indices[triIdx+0]]);
	const vector3f b(m_vertices[m_indices[triIdx+1]]);
	const vector3f c(m_vertices[m_indices[triIdx+2]]);

	vector3f v0_cross, v1_cross, v2_cross;
	const vector3f n = (c-a).Cross(b-a);
	const float nominator = n.Dot(a-origin);

	v0_cross = (c-origin).Cross(b-origin);
	v1_cross = (b-origin).Cross(a-origin);
	v2_cross = (a-origin).Cross(c-origin);

	for (int i=0; i<numRays; i++) {
		const float v0d = v0_cross.Dot(dirs[i]);
		const float v1d = v1_cross.Dot(dirs[i]);
		const float v2d = v2_cross.Dot(dirs[i]);

		if (((v0d > 0) && (v1d > 0) && (v2d > 0)) ||
			 ((v0d < 0) && (v1d < 0) && (v2d < 0))) {
			const float dist = nominator / dirs[i].Dot(n);
			if ((dist > 0) && (dist < isects[i].dist)) {
				isects[i].dist = dist;
				isects[i].triIdx = triIdx/3;
			}
		}
	}
}