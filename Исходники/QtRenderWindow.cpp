QtRenderWindow::QtRenderWindow(QWidget* parent, QGLFormat format) : QGLWidget(format, parent)
{
	makeCurrent();
	deviceContext = wglGetCurrentDC();
	glContext = wglGetCurrentContext();
	onMakeCurrent();

	mRealtime = false;
	mNeedsUpdate = true;
}