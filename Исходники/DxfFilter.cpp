	virtual void add3dFace(const DL_3dFaceData& face)
	{
		//TODO: understand what this really is?!
		CCVector3 P[4];
		for (unsigned i=0; i<4; ++i)
		{
			P[i] = CCVector3(	static_cast<PointCoordinateType>(face.x[i]),
								static_cast<PointCoordinateType>(face.y[i]),
								static_cast<PointCoordinateType>(face.z[i]) );
		}
		
		//create the 'faces' mesh if necessary
		if (!m_faces)
		{
			ccPointCloud* vertices = new ccPointCloud("vertices");
			m_faces = new ccMesh(vertices);
			m_faces->setName("Faces");
			m_faces->addChild(vertices);
			m_faces->setVisible(true);
			vertices->setEnabled(false);
			vertices->setLocked(true);
			
			m_root->addChild(m_faces);
		}
		
		ccPointCloud* vertices = dynamic_cast<ccPointCloud*>(m_faces->getAssociatedCloud());
		if (!vertices)
		{
			assert(false);
			return;
		}
		
		int vertIndexes[4] = {-1, -1, -1, -1};
		unsigned addedVertCount = 4;
		//check if the two last vertices are the same
		if (P[2].x == P[3].x && P[2].y == P[3].y && P[2].z == P[3].z)
			addedVertCount = 3;

		//current face color
		colorType col[3];
		colorType* faceCol = 0;
		if (getCurrentColour(col))
			faceCol = col;


		//look for already defined vertices
		unsigned vertCount = vertices->size();
		if (vertCount)
		{
			//DGM TODO: could we be smarter?
			for (unsigned i=0; i<addedVertCount; ++i)
			{
				for (unsigned j=0; j<vertCount; ++j)
				{
					const CCVector3* Pj = vertices->getPoint(j);
					if (P[i].x == Pj->x && P[i].y == Pj->y && P[i].z == Pj->z)
					{
						bool useCurrentVertex = true;

						//We must also check that the color is the same (if any)
						if (faceCol || vertices->hasColors())
						{
							const colorType* _faceCol = faceCol ? faceCol : ccColor::white;
							const colorType* _vertCol = vertices->hasColors() ? vertices->getPointColor(j) : ccColor::white;
							useCurrentVertex = (_faceCol[0] == _vertCol[0] && _faceCol[1] == _vertCol[1] && _faceCol[2] == _vertCol[2]);
						}

						if (useCurrentVertex)
						{
							vertIndexes[i] = static_cast<int>(j);
							break;
						}
					}
				}
			}
		}

		//now create new vertices
		unsigned createdVertCount = 0;
		{
			for (unsigned i=0; i<addedVertCount; ++i)
				if (vertIndexes[i] < 0)
					++createdVertCount;
		}

		if (createdVertCount != 0)
		{
			//reserve memory for the new vertices
			if (!vertices->reserve(vertCount+createdVertCount))
			{
				ccLog::Error("[DxfImporter] Not enough memory!");
				return;
			}

			for (unsigned i=0; i<addedVertCount; ++i)
			{
				if (vertIndexes[i] < 0)
				{
					vertIndexes[i] = static_cast<int>(vertCount++);
					vertices->addPoint(P[i]);
				}
			}
		}

		//number of triangles to add
		unsigned addTriCount = (addedVertCount == 3 ? 1 : 2);

		//now add the corresponding face(s)
		if (!m_faces->reserve(m_faces->size() + addTriCount))
		{
			ccLog::Error("[DxfImporter] Not enough memory!");
			return;
		}
		m_faces->addTriangle(vertIndexes[0], vertIndexes[1], vertIndexes[2]);
		if (addedVertCount == 4)
			m_faces->addTriangle(vertIndexes[0], vertIndexes[2], vertIndexes[3]);

		//add per-triangle normals
		{
			//normals table
			NormsIndexesTableType* triNormsTable = m_faces->getTriNormsTable();
			bool firstTime = false;
			if (!triNormsTable)
			{
				triNormsTable = new NormsIndexesTableType(); 
				m_faces->setTriNormsTable(triNormsTable);
				m_faces->addChild(triNormsTable);
				firstTime = true;
			}

			//add 1 or 2 new entries
			unsigned triNormCount = triNormsTable->currentSize();
			if (!triNormsTable->reserve(triNormsTable->currentSize() + addTriCount))
			{
				ccLog::Error("[DxfImporter] Not enough memory!");
				return;
			}
			
			CCVector3 N = (P[1]-P[0]).cross(P[2]-P[0]);
			N.normalize();
			triNormsTable->addElement(ccNormalVectors::GetNormIndex(N.u));
			if (addTriCount == 2)
			{
				N = (P[2]-P[0]).cross(P[3]-P[0]);
				N.normalize();
				triNormsTable->addElement(ccNormalVectors::GetNormIndex(N.u));
			}

			//per-triangle normals indexes
			if (firstTime)
			{
				if (!m_faces->reservePerTriangleNormalIndexes())
				{
					ccLog::Error("[DxfImporter] Not enough memory!");
					return;
				}
				m_faces->showNormals(true);
			}
			int n1 = static_cast<int>(triNormCount);
			m_faces->addTriangleNormalIndexes(n1, n1, n1);
			if (addTriCount == 2)
			{
				int n2 = static_cast<int>(triNormCount+1);
				m_faces->addTriangleNormalIndexes(n2, n2, n2);
			}
		}

		//and now for the color
		if (faceCol)
		{
			//RGB field already instantiated?
			if (vertices->hasColors())
			{
				for (unsigned i=0; i<createdVertCount; ++i)
					vertices->addRGBColor(faceCol);
			}
			//otherwise, reserve memory and set all previous points to white by default
			else if (vertices->setRGBColor(ccColor::white))
			{
				//then replace the last color(s) by the current one
				for (unsigned i=0; i<createdVertCount; ++i)
					vertices->setPointColor(vertCount-1-i,faceCol);
				m_faces->showColors(true);
			}
		}
		else if (vertices->hasColors())
		{
			//add default color if none is defined!
			for (unsigned i=0; i<createdVertCount; ++i)
				vertices->addRGBColor(ccColor::white);
		}
	}