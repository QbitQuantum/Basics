Point3d ViewportUtil::cameraLocal() {
	float mat[16];
	glGetFloatv(GL_MODELVIEW_MATRIX,mat);
	Matrix4d m;
	m.set(mat);
	m.invert();
	Point3d p(0,0,0);
	m.transform(&p);
	return p;
}