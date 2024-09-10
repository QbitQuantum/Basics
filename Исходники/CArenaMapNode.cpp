void CArenaMapNode::initialize(const std::string &filePath)
{
	FILE *fp;
	char tag[4];
	void *memoryPtr;
	uint16_t version;
	uint16_t partCount;
	int totalIndexCount;
	int indexLayoutSize;
	int totalVertexCount;
	int vertexLayoutSize;
	char meshNameTemp[MAP_PART_NAME_ARRAY_LENGTH + 1];
	uint32_t definingVerticesCount;
	uint32_t definingTrianglesCount;

	std::string materialFilePath = filePath;
	utils::changeExt(materialFilePath, "mat");

	if(!(fp = fopen(filePath.c_str(), "rb")))
	{
		CLogger::failedLoadWarning(filePath, "File not found or broken");
		return;
	}

	m_filePath = filePath;

	fread(tag, sizeof(char), 4, fp);

	if(strncmp(tag, "MAA", 3) != 0)
	{
		fclose(fp);
		CLogger::failedLoadWarning(filePath, "File tag is not MAA");
		return;
	}

	fread(&version, sizeof(uint16_t), 1, fp);

	if(version != 1)
	{
		fclose(fp);
		CLogger::failedLoadWarning(filePath, "Unsupported MAA version");
		return;
	}

	vertexLayoutSize = 64;

	fread(&partCount, sizeof(uint16_t), 1, fp);
	fread(&totalVertexCount, sizeof(uint32_t), 1, fp);
	fread(&totalIndexCount, sizeof(uint32_t), 1, fp);

	indexLayoutSize = sizeof(uint32_t);

	fread(&definingVerticesCount, sizeof(uint32_t), 1, fp);
	fread(&definingTrianglesCount, sizeof(uint32_t), 1, fp);

	for(uint16_t i = 0; i < partCount; i++)
	{
		int start;
		CMapPart p = CMapPart();

		// Make sure the temp will be null-terminated.
		memset(meshNameTemp, '\0', MAP_PART_NAME_ARRAY_LENGTH + 1);
		fread(meshNameTemp, sizeof(char), MAP_PART_NAME_ARRAY_LENGTH, fp);

		memcpy(p.m_name, meshNameTemp, 32);

		fread(&start, sizeof(uint32_t), 1, fp);
		fread(&p.m_count, sizeof(uint32_t), 1, fp);

		p.m_startPtr = (void *)((intptr_t)start);

		p.setMaterial(m_resourceManager->getMaterial(materialFilePath, meshNameTemp));

		m_parts.push_back(p);

		InfoLog << "Part: " << meshNameTemp << NL;
	}

	glGenVertexArrays(1, &m_vaoId);
	glBindVertexArray(m_vaoId);

	glGenBuffers(1, &m_vboId);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboId);

	glBufferData(GL_ARRAY_BUFFER, totalVertexCount * vertexLayoutSize, 0, GL_STATIC_DRAW);

	memoryPtr = glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	fread(memoryPtr, vertexLayoutSize, totalVertexCount, fp);
	glUnmapBuffer(GL_ARRAY_BUFFER);

	glVertexAttribPointer(OPENGL_VXA_POSITION_ID,  3, GL_FLOAT, GL_FALSE, 64, (void *)(0));
	glEnableVertexAttribArray(OPENGL_VXA_POSITION_ID);
	glVertexAttribPointer(OPENGL_VXA_NORMAL_ID,    3, GL_FLOAT, GL_FALSE, 64, (void *)(12));
	glEnableVertexAttribArray(OPENGL_VXA_NORMAL_ID);
	glVertexAttribPointer(OPENGL_VXA_TEXCOORD0_ID, 2, GL_FLOAT, GL_FALSE, 64, (void *)(24));
	glEnableVertexAttribArray(OPENGL_VXA_TEXCOORD0_ID);
	glVertexAttribPointer(OPENGL_VXA_TANGENT_ID,   4, GL_FLOAT, GL_FALSE, 64, (void *)(32));
	glEnableVertexAttribArray(OPENGL_VXA_TANGENT_ID);
	glVertexAttribPointer(OPENGL_VXA_WEIGHT0_ID,   1, GL_FLOAT, GL_FALSE, 64, (void *)(48));
	glEnableVertexAttribArray(OPENGL_VXA_WEIGHT0_ID);
	glVertexAttribPointer(OPENGL_VXA_WEIGHT1_ID,   1, GL_FLOAT, GL_FALSE, 64, (void *)(52));
	glEnableVertexAttribArray(OPENGL_VXA_WEIGHT1_ID);
	glVertexAttribPointer(OPENGL_VXA_WEIGHT2_ID,   1, GL_FLOAT, GL_FALSE, 64, (void *)(56));
	glEnableVertexAttribArray(OPENGL_VXA_WEIGHT2_ID);
	glVertexAttribPointer(OPENGL_VXA_WEIGHT3_ID,   1, GL_FLOAT, GL_FALSE, 64, (void *)(60));
	glEnableVertexAttribArray(OPENGL_VXA_WEIGHT3_ID);

	glGenBuffers(1, &m_iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_iboId);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, totalIndexCount * indexLayoutSize, 0, GL_STATIC_DRAW);

	memoryPtr = glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
	fread(memoryPtr, indexLayoutSize, totalIndexCount, fp);
	glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


	m_vertices = 0;
	m_indices = 0;
	m_materials = 0;

	uint32_t int32Temp;
	unsigned char ucTemp;
	float flTemp;

	if(definingTrianglesCount > 0)
	{
		m_vertices = new btScalar[definingVerticesCount * 3];
		m_indices = new int[definingTrianglesCount * 3];
		m_materials = new int[definingTrianglesCount];

		for(unsigned int i = 0; i < definingVerticesCount * 3; i++)
		{
			fread(&flTemp, sizeof(float), 1, fp);
			m_vertices[i] = (btScalar)flTemp;
		}

		for(unsigned int i = 0; i < definingTrianglesCount * 3; i++)
		{
			fread(&int32Temp, sizeof(uint32_t), 1, fp);
			m_indices[i] = (int)int32Temp;
		}

		for(unsigned int i = 0; i < definingTrianglesCount; i++)
		{
			fread(&ucTemp, sizeof(unsigned char), 1, fp);
			m_materials[i] = (int)ucTemp;
		}



		setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
		update();

		m_gMaterials = 0;
		m_tivm = 0;
		m_trimeshShape = 0;
		m_rigidBody = 0;

		int totalMaterials = 1;

		m_gMaterials = new CustomMaterial[totalMaterials];
		m_gMaterials[0].m_friction = 1.0f;
		m_gMaterials[0].m_restitution = 0.1f;
		m_gMaterials[0].m_foo1 = 1;
		m_gMaterials[0].m_foo2 = 1;

		m_tivm = new btTriangleIndexVertexMaterialArray(definingTrianglesCount,
								  m_indices,
								  3 * sizeof(int),
								  definingVerticesCount,
								  m_vertices,
								  3 * sizeof(btScalar),
								  totalMaterials,
								  (unsigned char *)m_gMaterials,
								  sizeof(CustomMaterial),
								  m_materials,
								  sizeof(int));

		bool useQuantizedAabbCompression = true;
		// Create the multimaterial mesh shape
		m_trimeshShape  = new btMultimaterialTriangleMeshShape(
		(btTriangleIndexVertexMaterialArray*)m_tivm,
		useQuantizedAabbCompression);

		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(m_position.x, m_position.y, m_position.z));

		m_rigidBody = new btCollisionObject();
		m_rigidBody->setCollisionShape(m_trimeshShape);
		m_rigidBody->setWorldTransform(groundTransform);
		m_rigidBody->setCollisionFlags(m_rigidBody->getCollisionFlags() |
			btCollisionObject::CF_CUSTOM_MATERIAL_CALLBACK | btCollisionObject::CF_STATIC_OBJECT);
	}

	fclose(fp);
}