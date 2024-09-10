void VIICanvas::Render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();
	
	glTranslatef(0,0,-mDistanceOrigin);
	glRotatef(this->mAngleX,1,0,0);
	glRotatef(this->mAngleY,0,1,0);

	MeshManager* manager = MeshManager::getSingleton();
	if(manager->existActiveMesh())
	{
		Mesh* mesh = manager->getActiveMesh();
		std::set<Face*> faces = mesh->getFaces();
		float posA[3],posB[3],posC[3];
		float colorA[3],colorB[3],colorC[3];
		
		if(this->mShowEdges)
		{
			glColor3f(0.0,0.0,0.0);
			glEnable(GL_POLYGON_OFFSET_LINE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
			glPolygonOffset(-1.0,-1.0);
			glBegin(GL_TRIANGLES);
			for(std::set<Face*>::iterator i = faces.begin();i!=faces.end();i++)
			{
				Face* face = *i;
				face->getA()->getPosition().getArray(posA);
				face->getB()->getPosition().getArray(posB);
				face->getC()->getPosition().getArray(posC);
				glVertex3fv(posA);
				glVertex3fv(posB);
				glVertex3fv(posC);
			}
			glEnd();
			glDisable(GL_POLYGON_OFFSET_LINE);
			glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		}
		
		int curMetaDataId = mesh->getCurMetaDataId();
		float maxValue = 0,minValue=0;
		float deltaMinMaxValue=0.0;
		if(curMetaDataId != 0)
		{
			std::set<Vertex*> vertex = mesh->getVertices();
			std::set<Vertex*>::iterator iter = vertex.begin();
			std::pair<std::string,float> data = (*iter)->getMetaData(curMetaDataId);
			maxValue = data.second;
			minValue = data.second;
			++iter;
			for(iter;iter!=vertex.end();iter++)
			{
				data = (*iter)->getMetaData(curMetaDataId);
				if(data.second > maxValue)
				{
					maxValue = data.second;
				}
				if(data.second < minValue)
				{
					minValue = data.second;
				}
			}
			deltaMinMaxValue = maxValue - minValue;
		}
		
		glColor3f(0.5,0.5,0.5);
		glBegin(GL_TRIANGLES);
		for(std::set<Face*>::iterator i = faces.begin();i!=faces.end();i++)
		{
			Face* face = *i;
			face->getA()->getPosition().getArray(posA);
			face->getB()->getPosition().getArray(posB);
			face->getC()->getPosition().getArray(posC);
			if(curMetaDataId == 0)
			{
				glVertex3fv(posA);
				glVertex3fv(posB);
				glVertex3fv(posC);
			}
			else
			{
				std::pair<std::string,float> dataA,dataB,dataC;
				dataA = face->getA()->getMetaData(curMetaDataId);
				dataB = face->getB()->getMetaData(curMetaDataId);
				dataC = face->getC()->getMetaData(curMetaDataId);
				
				Vector3 color1 = mMinColor;
				Vector3 color2 = mMaxColor - mMinColor;//(1,0,0);
				Vector3 colorVecA = color1 + color2 * ((dataA.second - minValue)/deltaMinMaxValue);
				Vector3 colorVecB = color1 + color2 * ((dataB.second - minValue)/deltaMinMaxValue);
				Vector3 colorVecC = color1 + color2 * ((dataC.second - minValue)/deltaMinMaxValue);
				
				colorVecA.getArray(colorA);
				colorVecB.getArray(colorB);
				colorVecC.getArray(colorC);
				glColor3fv(colorA);
				glVertex3fv(posA);
				glColor3fv(colorB);
				glVertex3fv(posB);
				glColor3fv(colorC);
				glVertex3fv(posC);
			}
		}
		glEnd();
	}
	
	
	glFlush();
	SwapBuffers();
}