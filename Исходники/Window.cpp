void Window::setMatrix(Matrix4 camera, Matrix4 world) {
	glMatrixMode(GL_MODELVIEW);  
	Matrix4 temp;
	temp = camera * world;
	temp.transpose();
	glLoadMatrixd(temp.getPointer());
}