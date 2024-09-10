void Sample_8_9::draw()
{
	GLubyte values[6];

	OGLError err;
	OGLInspector inspector;

	if (m_prevSink != m_sink)
	{
		m_bImagSprt = inspector.ImagingSupported();
		if (m_bImagSprt)
		{
			glMinmax(GL_MINMAX, GL_RGB, m_sink);

			if (err.checkError())
			{
				glEnable(GL_MINMAX);
				glResetMinmax(GL_MINMAX);
			}
			else
				m_bImagSprt = false;
		}
		else
		{
			m_prevSink = m_sink;
			printf ("GL_ARB_imaging is not supported\n");
		}
	}

	glRasterPos2i(5, 5);
	glDrawPixels( m_image.sizeX(), m_image.sizeY(), GL_RGB,
			GL_UNSIGNED_BYTE, m_image.data() );

	if (m_prevSink != m_sink)
	{
		m_prevSink = m_sink;
		glGetMinmax(GL_MINMAX,GL_TRUE,GL_RGB,GL_UNSIGNED_BYTE,values);

		printf("====== MIN-MAX ======\n");
		printf("Red : min = %d max = %d\n",values[0],values[3]);
		printf("Green: min = %d max = %d\n",values[1],values[4]);
		printf("Blue : min = %d max = %d\n",values[3],values[5]);
	}
}