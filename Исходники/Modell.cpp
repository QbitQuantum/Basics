Modell::Modell(glm::mat4& matrix, const char * modelpath)
{
	mat = matrix;

	Importer importer;
	const aiScene* scene = NULL;
	
	//gibt es die Datei
	std::ifstream fin(modelpath);
	if(!fin.fail()) {
		fin.close();
	}
	else{
		printf("Fehler beim laden des Modells: %s\n", modelpath);
		printf("%s\n", importer.GetErrorString());
		system("PAUSE");
		exit(EXIT_FAILURE);
	}

	scene = importer.ReadFile( modelpath,/* aiProcess_Triangulate | */aiProcessPreset_TargetRealtime_Quality);

	if( !scene)
	{
		printf("%s\n", importer.GetErrorString());
		system("PAUSE");
		exit(EXIT_FAILURE);
	}else{
		mesh = scene->mMeshes[0];

		int indexcount = mesh->mNumFaces * 3;
		int vertexcount = mesh->mNumVertices *3;
		int normcount = mesh->mNumVertices *3;
		int uvCoordcount = mesh->mNumVertices *2;

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) 
		{
            const aiFace* face = &mesh->mFaces[i];
			
			unsigned int index = face->mIndices[0];
			indices.push_back(index);

			index = face->mIndices[1];
			indices.push_back(index);

			index = face->mIndices[2];
			indices.push_back(index);
        }


		//index = 0;
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) 
		{
			glm::vec3 positions;

			positions.x = mesh->mVertices[i].x;
			positions.y = mesh->mVertices[i].y;
			positions.z = mesh->mVertices[i].z;

			pos.push_back(positions);

			glm::vec3 norm;
			norm.x = mesh->mNormals[i].x;
			norm.y = mesh->mNormals[i].y;
			norm.z = mesh->mNormals[i].z;

			normals.push_back(norm);

			glm::vec2 tex;
			//es koennten auch mehrere texturen am objekt sein. Wir supporten vorerst nur eine
			if (mesh->mTextureCoords[0]) 
			{
				tex.x = mesh->mTextureCoords[0][i].x;
				tex.y = mesh->mTextureCoords[0][i].y;

				uvs.push_back(tex);
			}
		}
		if (mesh->mMaterialIndex >= 0) {

		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		aiColor3D colorDIF (0.f,0.f,0.f);
		aiColor3D colorSPEC (0.f,0.f,0.f);
		material->Get(AI_MATKEY_COLOR_DIFFUSE,colorDIF);
		material->Get(AI_MATKEY_COLOR_DIFFUSE,colorSPEC);

		diffuseMAT.r = colorDIF.r;
		diffuseMAT.g = colorDIF.g;
		diffuseMAT.b = colorDIF.b;

		specularMAT.r = colorSPEC.r;
		specularMAT.g = colorSPEC.g;
		specularMAT.b = colorSPEC.b;

		Texture textureloader;
		diffuseMaps = textureloader.loadMaterialTextures(modelpath, material, aiTextureType_DIFFUSE, "diffuse");
		//textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

		specularMaps = textureloader.loadMaterialTextures(modelpath, material, aiTextureType_SPECULAR, "specular");
		//textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	calcHitbox();
	
	positioncount = vertexcount;
	indicescount = indexcount;
	normalscount = normcount;
	uvcount = uvCoordcount;

	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, positioncount/*Anzahl Knoten*/  * sizeof(float), &pos[0], GL_STATIC_DRAW); 
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicescount /*Anzahl Indizes*/ * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normalscount /*Anzahl Indizes*/ * sizeof(float), &normals[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvcount /*Anzahl Indizes*/ * sizeof(float), &uvs[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	minX = getMinX();
	minY = getMinY();
	minZ = getMinZ();
	maxX = getMaxX();
	maxY = getMaxY();
	maxZ = getMaxZ();
	box = calcBox();
}