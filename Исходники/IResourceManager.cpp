bool IResourceManager::LoadSimpleMesh(wchar_t* meshName, LPDIRECT3DTEXTURE9 meshTexture)
{
	ISimpleMesh *tempMesh;
	FILE *file;
	_wfopen_s(&file,meshName,L"rb");
	if(file == NULL)
		return false;
	DWORD verticesCount;
	DWORD additionalVertices;
	DWORD indicesCount;
	DWORD textureVertices;
	bool founded = false;
	fread(&verticesCount,sizeof(DWORD),1,file);
	fread(&additionalVertices,sizeof(DWORD),1,file);
	fread(&indicesCount,sizeof(DWORD),1,file);
	fread(&textureVertices,sizeof(DWORD),1,file);
	SimpleVertex *vertices = new SimpleVertex[verticesCount+additionalVertices];
	additionalVertices = 0;
	//position reading
	for(DWORD i = 0; i < verticesCount; i++)
	{
		fread(&vertices[i].position[0],sizeof(float),1,file);
		fread(&vertices[i].position[1],sizeof(float),1,file);
		fread(&vertices[i].position[2],sizeof(float),1,file);
	}
	//indices reading
	DWORD *indices = new DWORD[indicesCount*3];
	for(DWORD i = 0; i < indicesCount*3; i++)
	{
		fread(&indices[i],sizeof(DWORD),1,file);
		vertices[indices[i]].texCoord[0] = -100.0f;
	}
	//texture vertices reading
	float *texture = new float[textureVertices*3];
	for(DWORD i = 0; i < textureVertices*3; i++)
	{
		fread(&texture[i],sizeof(float),1,file);
	}
	DWORD textureInd;
	for(DWORD i = 0; i < indicesCount*3; i++)
	{
		fread(&textureInd,sizeof(DWORD),1,file);
		if(vertices[indices[i]].texCoord[0] == -100.0f)
		{
			vertices[indices[i]].texCoord[0] = texture[textureInd*3];
			vertices[indices[i]].texCoord[1] = 1.0f-texture[textureInd*3+1];
		}else{
			founded = false;
			for(DWORD j = verticesCount-1; j < verticesCount+additionalVertices; j++)
				if(vertices[j].position[0] == vertices[indices[i]].position[0])
					if(vertices[j].position[1] == vertices[indices[i]].position[1])
						if(vertices[j].position[2] == vertices[indices[i]].position[2])
								if(vertices[j].texCoord[0] == texture[textureInd*3])
										if(vertices[j].texCoord[1] == 1.0f-texture[textureInd*3+1])
										{
											indices[i] = j;
											founded = true;
											break;
										}
			if(!founded)
			{
				vertices[verticesCount+additionalVertices].position[0] = vertices[indices[i]].position[0];
				vertices[verticesCount+additionalVertices].position[1] = vertices[indices[i]].position[1];
				vertices[verticesCount+additionalVertices].position[2] = vertices[indices[i]].position[2];
				vertices[verticesCount+additionalVertices].texCoord[0] = texture[textureInd*3];
				vertices[verticesCount+additionalVertices].texCoord[1] = 1.0f-texture[textureInd*3+1];
				indices[i] = verticesCount + additionalVertices;
				additionalVertices++;
			}
		}
	}
	tempMesh = new ISimpleMesh(vertices,verticesCount+additionalVertices,indices,indicesCount*3,meshTexture,NULL,NULL,NULL);
	delete []texture;
	if(this->firstSimpleMesh == NULL)
	{
		this->firstSimpleMesh = new resourceQueue<ISimpleMesh>;
		this->firstSimpleMesh->resourcePath = meshName;
		this->firstSimpleMesh->resource = tempMesh;
		this->firstSimpleMesh->next = NULL;
		this->lastSimpleMesh = this->firstSimpleMesh;
	}else{
		resourceQueue<ISimpleMesh> *temp = new resourceQueue<ISimpleMesh>;
		temp->resourcePath = meshName;
		temp->resource = tempMesh;
		temp->next = NULL;
		this->lastSimpleMesh->next = temp;
		this->lastSimpleMesh = temp;
	}
	return true;
}