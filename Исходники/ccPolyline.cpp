void ccPolyline::drawMeOnly(CC_DRAW_CONTEXT& context)
{
	//no picking enabled on polylines
	if (MACRO_DrawPointNames(context))
		return;

	unsigned vertCount = size();
	if (vertCount < 2)
		return;

	bool draw = false;

	if (MACRO_Draw3D(context))
	{
		draw = !m_mode2D;
	}
	else if (m_mode2D)
	{
		bool drawFG = MACRO_Foreground(context);
		draw = ((drawFG && m_foreground) || (!drawFG && !m_foreground));
	}

	if (draw)
	{
		//standard case: list names pushing
		bool pushName = MACRO_DrawEntityNames(context);
		if (pushName)
			glPushName(getUniqueIDForDisplay());

		if (colorsShown())
			ccGL::Color3v(m_rgbColor.rgb);

		//display polyline
		if (vertCount > 1)
		{
			if (m_width != 0)
			{
				glPushAttrib(GL_LINE_BIT);
				glLineWidth(static_cast<GLfloat>(m_width));
			}

			//DGM: we do the 'GL_LINE_LOOP' manually as I have a strange bug
			//on one on my graphic card with this mode!
			//glBegin(m_isClosed ? GL_LINE_LOOP : GL_LINE_STRIP);
			glBegin(GL_LINE_STRIP);
			for (unsigned i=0; i<vertCount; ++i)
			{
				ccGL::Vertex3v(getPoint(i)->u);
			}
			if (m_isClosed)
			{
				ccGL::Vertex3v(getPoint(0)->u);
			}
			glEnd();

			//display arrow
			if (m_showArrow && m_arrowIndex < vertCount && (m_arrowIndex > 0 || m_isClosed))
			{
				const CCVector3* P0 = getPoint(m_arrowIndex == 0 ? vertCount-1 : m_arrowIndex-1);
				const CCVector3* P1 = getPoint(m_arrowIndex);
				//direction of the last polyline chunk
				CCVector3 u = *P1 - *P0;
				u.normalize();

				if (m_mode2D)
				{
					u *= -m_arrowLength;
					static const PointCoordinateType s_defaultArrowAngle = static_cast<PointCoordinateType>(15.0 * CC_DEG_TO_RAD);
					static const PointCoordinateType cost = cos(s_defaultArrowAngle);
					static const PointCoordinateType sint = sin(s_defaultArrowAngle);
					CCVector3 A(cost * u.x - sint * u.y,  sint * u.x + cost * u.y, 0);
					CCVector3 B(cost * u.x + sint * u.y, -sint * u.x + cost * u.y, 0);
					glBegin(GL_POLYGON);
					ccGL::Vertex3v((A+*P1).u);
					ccGL::Vertex3v((B+*P1).u);
					ccGL::Vertex3v((  *P1).u);
					glEnd();
				}
				else
				{
					if (!c_unitArrow)
					{
						c_unitArrow = QSharedPointer<ccCone>(new ccCone(0.5,0.0,1.0));
						c_unitArrow->showColors(true);
						c_unitArrow->showNormals(false);
						c_unitArrow->setVisible(true);
						c_unitArrow->setEnabled(true);
					}
					if (colorsShown())
						c_unitArrow->setTempColor(m_rgbColor);
					else
						c_unitArrow->setTempColor(context.pointsDefaultCol);
					//build-up unit arrow own 'context'
					CC_DRAW_CONTEXT markerContext = context;
					markerContext.flags &= (~CC_DRAW_ENTITY_NAMES); //we must remove the 'push name flag' so that the sphere doesn't push its own!
					markerContext._win = 0;

					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();
					ccGL::Translate(P1->x,P1->y,P1->z);
					ccGLMatrix rotMat = ccGLMatrix::FromToRotation(CCVector3(0,0,1),u);
					glMultMatrixf(rotMat.inverse().data());
					glScalef(m_arrowLength,m_arrowLength,m_arrowLength);
					ccGL::Translate(0.0,0.0,-0.5);
					c_unitArrow->draw(markerContext);
					glPopMatrix();
				}
			}

			if (m_width != 0)
			{
				glPopAttrib();
			}
		}

		//display vertices
		if (m_showVertices)
		{
			glPushAttrib(GL_POINT_BIT);
			glPointSize((GLfloat)m_vertMarkWidth);

			glBegin(GL_POINTS);
			for (unsigned i=0; i<vertCount; ++i)
			{
				ccGL::Vertex3v(getPoint(i)->u);
			}
			glEnd();

			glPopAttrib();
		}

		if (pushName)
			glPopName();
	}
}