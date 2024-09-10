void NaviCubeImplementation::drawNaviCube(bool pickMode) {
	// initializes stuff here when we actually have a context
    // FIXME actually now that we have Qt5, we could probably do this earlier (as we do not need the opengl context)
	if (!m_NaviCubeInitialised) {
		QtGLWidget* gl = static_cast<QtGLWidget*>(m_View3DInventorViewer->viewport());
		if (gl == NULL)
			return;
		initNaviCube(gl);
		m_NaviCubeInitialised = true;
	}

	SoCamera* cam = m_View3DInventorViewer->getSoRenderManager()->getCamera();

	if (!cam)
		return;

	handleResize();

	// Store GL state.
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	GLfloat depthrange[2];
	glGetFloatv(GL_DEPTH_RANGE, depthrange);
	GLdouble projectionmatrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, projectionmatrix);

	glDepthMask(GL_TRUE);
	glDepthRange(0.0, 1.0);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glDisable(GL_LIGHTING);
	//glDisable(GL_BLEND);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glTexEnvf(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_TRUE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(GL_CCW);

	glAlphaFunc( GL_GREATER, 0.25);
	glEnable( GL_ALPHA_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	const float NEARVAL = 0.1f;
	const float FARVAL = 10.0f;
	const float dim = NEARVAL * float(tan(M_PI / 8.0))*1.2;
	glFrustum(-dim, dim, -dim, dim, NEARVAL, FARVAL);

	SbMatrix mx;
	mx = cam->orientation.getValue();

	mx = mx.inverse();
	mx[3][2] = -5.0;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadMatrixf((float*) mx);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	if (pickMode) {
		glDisable(GL_BLEND);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glShadeModel(GL_FLAT);
		glDisable(GL_DITHER);
		glDisable(GL_POLYGON_SMOOTH);
	}
	else {
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	glClear(GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, (void*) m_VertexArray.data());
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, m_TextureCoordArray.data());

	if (!pickMode) {
		// Draw the axes
		glDisable(GL_TEXTURE_2D);
		float a=1.1f;

		static GLubyte xbmp[] = { 0x11,0x11,0x0a,0x04,0x0a,0x11,0x11 };
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex3f(-1 , -1, -1);
		glVertex3f(+1 , -1, -1);
		glEnd();
	    glRasterPos3d(a, -a, -a);
	    glBitmap(8, 7, 0, 0, 0, 0, xbmp);

		static GLubyte ybmp[] = { 0x04,0x04,0x04,0x04,0x0a,0x11,0x11 };
		glColor3f(0, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(-1 , -1, -1);
		glVertex3f(-1 , +1, -1);
		glEnd();
	    glRasterPos3d( -a, a, -a);
	    glBitmap(8, 7, 0, 0, 0, 0, ybmp);

		static GLubyte zbmp[] = { 0x1f,0x10,0x08,0x04,0x02,0x01,0x1f };
		glColor3f(0, 0, 1);
		glBegin(GL_LINES);
		glVertex3f(-1 , -1, -1);
		glVertex3f(-1 , -1, +1);
		glEnd();
	    glRasterPos3d( -a, -a, a);
	    glBitmap(8, 7, 0, 0, 0, 0, zbmp);

		glEnable(GL_TEXTURE_2D);
	}

	// Draw the cube faces
	if (pickMode) {
		for (vector<Face*>::iterator f = m_Faces.begin(); f != m_Faces.end(); f++) {
			glColor3ub((*f)->m_PickId, 0, 0);
			glBindTexture(GL_TEXTURE_2D, (*f)->m_PickTextureId);
			glDrawElements(GL_TRIANGLE_FAN, (*f)->m_VertexCount, GL_UNSIGNED_BYTE, (void*) &m_IndexArray[(*f)->m_FirstVertex]);
		}
	}
	else {
		for (int pass = 0; pass < 3 ; pass++) {
			for (vector<Face*>::iterator f = m_Faces.begin(); f != m_Faces.end(); f++) {
				if (pickMode) { // pick should not be drawn in tree passes
					glColor3ub((*f)->m_PickId, 0, 0);
					glBindTexture(GL_TEXTURE_2D, (*f)->m_PickTextureId);
				} else {
					if (pass != (*f)->m_RenderPass)
						continue;
					QColor& c = (m_HiliteId == (*f)->m_PickId) && (pass < 2) ? m_HiliteColor : (*f)->m_Color;
					glColor4f(c.redF(), c.greenF(), c.blueF(),c.alphaF());
					glBindTexture(GL_TEXTURE_2D, (*f)->m_TextureId);
				}
				glDrawElements(GL_TRIANGLE_FAN, (*f)->m_VertexCount, GL_UNSIGNED_BYTE, (void*) &m_IndexArray[(*f)->m_FirstVertex]);
			}
		}
	}


	// Draw the rotate buttons
	glEnable(GL_CULL_FACE);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glDisable(GL_DEPTH_TEST);
	glClear(GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 1, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	for (vector<int>::iterator b = m_Buttons.begin(); b != m_Buttons.end(); b++) {
		if (pickMode)
			glColor3ub(*b, 0, 0);
		else {
			QColor& c = (m_HiliteId ==(*b)) ? m_HiliteColor : m_ButtonColor;
			glColor3f(c.redF(), c.greenF(), c.blueF());
		}
		glBindTexture(GL_TEXTURE_2D, m_Textures[*b]);

		glBegin(GL_QUADS);
		glTexCoord2f(0, 0);
		glVertex3f(0.0f, 1.0f, 0.0f);
		glTexCoord2f(1, 0);
		glVertex3f(1.0f, 1.0f, 0.0f);
		glTexCoord2f(1, 1);
		glVertex3f(1.0f, 0.0f, 0.0f);
		glTexCoord2f(0, 1);
		glVertex3f(0.0f, 0.0f, 0.0f);
		glEnd();
	}

	// Draw the view menu icon
	if (pickMode) {
		glColor3ub(TEX_VIEW_MENU_FACE, 0, 0);
		glBindTexture(GL_TEXTURE_2D, m_Textures[TEX_VIEW_MENU_FACE]);
	}
	else {
		if (m_HiliteId == TEX_VIEW_MENU_FACE) {
			QColor& c = m_HiliteColor;
			glColor4f(c.redF(), c.greenF(), c.blueF(),c.alphaF());
			glBindTexture(GL_TEXTURE_2D, m_Textures[TEX_VIEW_MENU_FACE]);

			glBegin(GL_QUADS); // DO THIS WITH VERTEX ARRAYS
			glTexCoord2f(0, 0);
			glVertex3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1, 0);
			glVertex3f(1.0f, 1.0f, 0.0f);
			glTexCoord2f(1, 1);
			glVertex3f(1.0f, 0.0f, 0.0f);
			glTexCoord2f(0, 1);
			glVertex3f(0.0f, 0.0f, 0.0f);
			glEnd();
		}

		glColor3ub(255,255,255);
		glBindTexture(GL_TEXTURE_2D, m_Textures[TEX_VIEW_MENU_ICON]);
	}

	glBegin(GL_QUADS); // FIXME do this with vertex arrays
	glTexCoord2f(0, 0);
	glVertex3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(1, 0);
	glVertex3f(1.0f, 1.0f, 0.0f);
	glTexCoord2f(1, 1);
	glVertex3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0, 1);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();


	glPopMatrix();

	// Restore original state.

	glDepthRange(depthrange[0], depthrange[1]);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(projectionmatrix);

	glPopAttrib();
}