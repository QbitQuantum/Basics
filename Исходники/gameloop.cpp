void	OGLViewMatrix(const vec3& dir, const vec3& up, const vec3& loc)
// Multiplies the current OpenGL matrix by the view matrix corresponding to the given parameters.
{
	matrix m;
	vec3 Z = dir.cross(up);
	m.SetColumn(0, -Z);
	m.SetColumn(1, up);
	m.SetColumn(2, dir);
	m.SetColumn(3, loc);
	m.Invert();
	float	mat[16];

	// Copy to the 4x4 layout.
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 3; row++) {
			mat[col * 4 + row] = m.GetColumn(col).Get(row);
		}
		if (col < 3) {
			mat[col * 4 + 3] = 0;
		} else {
			mat[col * 4 + 3] = 1;
		}
	}

	// Apply to the current OpenGL matrix.
	glMultMatrixf(mat);
}