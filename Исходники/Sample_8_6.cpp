void Sample_8_6::draw()
{
	OGLError err;
	OGLInspector inspector;

	if (m_fltrType != NONE)
	{
		if (inspector.ImagingSupported())
		{
			setFilter();

			if (err.checkError())
				glEnable(GL_CONVOLUTION_2D);
			else
				m_fltrType = NONE;
		}
		else
		{
			printf ("GL_ARB_imaging is not supported\n");
			m_fltrType = NONE;
		}
	}

	glRasterPos2i(5, 5);
	glDrawPixels( m_image.sizeX(), m_image.sizeY(), GL_RGB,
			GL_UNSIGNED_BYTE, m_image.data() );

	glDisable(GL_CONVOLUTION_2D);

}