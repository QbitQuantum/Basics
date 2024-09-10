AABB operator*(const Mat3 &m, const AABB &a)
{
	Vec2 omin = a.min();
	Vec2 omax = a.max();

	Vec2 rmin = m[2].xy;
	Vec2 rmax = m[2].xy;

	float p, q;

	for (unsigned j = 0; j < 2; ++j)
		for (unsigned i = 0; i < 2; ++i)
		{
			p = omin[i] * m[i][j];
			q = omax[i] * m[i][j];

			if (p < q) std::swap(p, q);
			rmin[j] += p;
			rmax[j] += q;
		}
	return{ (rmin + rmax) / 2, (rmin - rmax) / 2 };
}