Vector3 OpenGLRenderer::Unproject(Number x, Number y, const Matrix4 &cameraMatrix, const Matrix4 &projectionMatrix, const Polycode::Rectangle &viewport) {
	Vector3 coords;
	GLfloat wx, wy, wz;
	GLdouble cx, cy, cz;

	GLdouble mv[16];
	Matrix4 camInverse = cameraMatrix.Inverse();
	Matrix4 cmv;
	cmv.identity();
	cmv = cmv * camInverse;
    
	for(int i=0; i < 16; i++) {
		mv[i] = cmv.ml[i];
	}
    
	GLint vp[4] = {viewport.x, viewport.y, viewport.w, viewport.h};
    
	GLdouble _sceneProjectionMatrix[16];
	for(int i=0; i < 16; i++) {
		_sceneProjectionMatrix[i] = projectionMatrix.ml[i];
	}	
	
	wx = ( Number ) x;
	wy = ( Number ) vp[3] - ( Number ) y;
	glReadPixels( x * backingResolutionScaleX, wy * backingResolutionScaleY, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &wz );
	
	gluUnProject( wx, wy, wz, mv, _sceneProjectionMatrix, vp, &cx, &cy, &cz );
	
	coords = Vector3( cx, cy, cz );
	
	return coords;	
}