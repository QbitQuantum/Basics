bool Face3::is_degenerate() const {

	Vector3 normal = vec3_cross(vertex[0] - vertex[1], vertex[0] - vertex[2]);
	return (normal.length_squared() < CMP_EPSILON2);
}