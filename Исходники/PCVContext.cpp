void PCVContext::setViewDirection(const CCVector3& V)
{
	if (!m_pixBuffer || !m_pixBuffer->isValid())
		return;

	m_pixBuffer->makeCurrent();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
    glLoadIdentity();

	CCVector3 U(0,0,1);
	if (1-fabs(V.dot(U)) < 1.0e-4)
	{
		U.y = 1;
		U.z = 0;
	}

	gluLookAt(-V.x,-V.y,-V.z,0.0,0.0,0.0,U.x,U.y,U.z);
	glGetFloatv(GL_MODELVIEW_MATRIX, m_viewMat);
	glPopMatrix();
}