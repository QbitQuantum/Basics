inline mat3 inverse(mat3 const& m)
{
	scalar_t const d = 1 / m.determinant();
	if (d != 0)
	{
		scalar_t const id = 1 / d;
		return mat3(
			vec3(
				 id * (m.y.y * m.z.z - m.y.z * m.z.y),
				-id * (m.x.y * m.z.z - m.x.z * m.z.y),
				 id * (m.x.y * m.y.z - m.x.z * m.y.y)),

			 vec3(
				-id * (m.y.x * m.z.z - m.y.z * m.z.x),
				 id * (m.x.x * m.z.z - m.x.z * m.z.x),
				-id * (m.x.x * m.y.z - m.x.z * m.y.x)),

			vec3(
				 id * (m.y.x * m.z.y - m.y.y * m.z.x),
				-id * (m.x.x * m.z.y - m.x.y * m.z.x),
				 id * (m.x.x * m.y.y - m.x.y * m.y.x)));
	}
	else
	{
		return mat3::identity();
	}
}