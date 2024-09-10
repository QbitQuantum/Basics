// Draw feature with respect to the world frame
void COpenGlDisplay::drawCurrentFeatures(CSLAM* SLAM)
{
	if (0 == SLAM->m_nMatches)
	{
		return;
	}

	Point3f location, sigma;
	Quaternion axis;
	char text[10];

	PointsMap* map_p = SLAM->map; 
	while (NULL != map_p)
	{
		if (true == map_p->isMatching)
		{
			glPushMatrix();

			location.x = (float)map_p->xyz.x;
			location.y = (float)map_p->xyz.y;

			if (TRUE == SLAM->isCompensate)
			{
				location.z = (float)(map_p->xyz.z + SLAM->m_deep)/2.0;
			} 
			else
			{
				location.z = (float)map_p->xyz.z;
			}

			glTranslatef(location.x,location.y,location.z);      // Move Left 1.5 Units And Into The Screen 6.0 
			glColor3f( 1.0f, 0.0f, 0.0f );
			_itoa_s(map_p->ID, text, 10);
			drawText(text, 0.3);
			
			sigma.x = (float)map_p->sigma.x;
			sigma.y = (float)map_p->sigma.y;
			sigma.z = (float)map_p->sigma.z;

			axis = map_p->axis;
			float angle = 2*atan2(sqrt(axis.x*axis.x+axis.y*axis.y+axis.z*axis.z), axis.r);
			angle = angle*180/3.141593f;

			//glTranslatef(location.x,location.y,location.z);
			glRotated(angle, -axis.x, -axis.y, -axis.z); 
			glScaled(min(4.0f,sigma.x),min(4.0f,sigma.y),min(4.0f,sigma.z));
			glEnable(GL_LIGHTING);

			if (true == map_p->isLoop)
			{
				glColor3f( 0.0f, 1.0f, 0.0f );
			} 
			else
			{
				glColor3f( 1.0f, 0.0f, 0.0f );
			}

			glutWireSphere(3.0f, 10,10);
			glPopMatrix();
		}
		map_p = map_p->next;
	}
}