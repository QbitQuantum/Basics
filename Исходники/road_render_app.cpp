void Mouse(int button, int state, int x, int y)
{
	if (state != GLUT_UP)
		return;

	switch (button) 
	{
	case GLUT_LEFT_BUTTON:

#ifdef TEXTURE_STROKE_APP
		gPath.push_back( gtl::Vec3f(x, windowHeight-y, 0) );
#endif
		if (g_vectorPath.isEmpty()) 
		{
			g_vectorPath.moveTo(x, windowHeight-y);
		} 
		else 
		{
			g_vectorPath.lineTo(x, windowHeight-y);
			// g_vectorPath.curveTo(x, windowHeight-y);
		}
		g_stroker.process(g_vectorPath, g_pen);
		glutPostRedisplay();
		break;
	
	case GLUT_RIGHT_BUTTON:

#ifdef TEXTURE_STROKE_APP		
		gPath.clear();
#endif
		g_vectorPath.clear();
		g_stroker.clear();
		glutPostRedisplay();
		break;
	}
}