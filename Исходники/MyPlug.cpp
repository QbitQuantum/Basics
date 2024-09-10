void readSubMesh(IOReadBase* pRead, iModelData* pModelData, const CSubMesh& sharedSubMesh)
{
	iLodMesh* pMesh = &pModelData->getMesh();
	std::string strMaterialName = readString(pRead);
	int nSubID=pMesh->getSubCount();
	pModelData->setRenderPass(nSubID,nSubID,strMaterialName);
	
// 	if(listener)
// 		listener->processMaterialName(pMesh, &materialName);
// 	sm->setMaterialName(materialName);

	// bool useSharedVertices
	bool useSharedVertices;
	pRead->Read(&useSharedVertices,sizeof(bool));
	CSubMesh& subMesh=pMesh->addSubMesh();
	if (useSharedVertices)
	{
		subMesh.pos			=sharedSubMesh.pos;
		subMesh.weight		=sharedSubMesh.weight;
		subMesh.bone		=sharedSubMesh.bone;
		subMesh.normal		=sharedSubMesh.normal;
		subMesh.color		=sharedSubMesh.color;
		subMesh.texcoord	=sharedSubMesh.texcoord;
		subMesh.texcoord2	=sharedSubMesh.texcoord2;
	}

	// sm->indexData->indexStart = 0;
	unsigned int indexCount = 0;
	pRead->Read(&indexCount,sizeof(unsigned int));
	//sm->indexData->indexCount = indexCount;

	// bool indexes32Bit
	bool idx32bit;
	pRead->Read(&idx32bit,sizeof(bool));

	if (idx32bit)
	{
		MessageBoxW(0,L"Can't read idx32bit",L"Error",0);
		VertexIndex vertexIndex;
		for (size_t i=0;i<indexCount;++i)
		{
			unsigned int uVertexIndex;
			pRead->Read(&uVertexIndex,sizeof(unsigned int));
			vertexIndex.p=uVertexIndex;
			vertexIndex.n=uVertexIndex;
			vertexIndex.c=uVertexIndex;
			vertexIndex.uv1=uVertexIndex;
			vertexIndex.b=uVertexIndex;
			vertexIndex.w=uVertexIndex;
			subMesh.m_setVertexIndex.push_back(vertexIndex);
		}
	}
	else // 16-bit
	{
		VertexIndex vertexIndex;
		for (size_t i=0;i<indexCount;++i)
		{
			unsigned short uVertexIndex;
			pRead->Read(&uVertexIndex,sizeof(unsigned short));
			vertexIndex.p=uVertexIndex;
			vertexIndex.n=uVertexIndex;
			vertexIndex.c=uVertexIndex;
			vertexIndex.uv1=uVertexIndex;
			vertexIndex.b=uVertexIndex;
			vertexIndex.w=uVertexIndex;
			subMesh.m_setVertexIndex.push_back(vertexIndex);
		}
	}

	// M_GEOMETRY stream (Optional: present only if useSharedVertices = false)
	if (!useSharedVertices)
	{
		unsigned short streamID;
		unsigned int uLength;
		pRead->Read(&streamID,sizeof(unsigned short));
		pRead->Read(&uLength,sizeof(unsigned int));
		if (streamID != M_GEOMETRY)
		{
			MessageBoxW(0,L"Missing geometry data in mesh file",L"readSubMesh",0);
		}
		readGeometry(pRead, subMesh);
	}


	// Find all bone assignments, submesh operation, and texture aliases (if present)
	if (!pRead->IsEof())
	{
		unsigned short streamID;
		unsigned int uLength;
		pRead->Read(&streamID,sizeof(unsigned short));
		pRead->Read(&uLength,sizeof(unsigned int));
		while(!pRead->IsEof() &&
			(streamID == M_SUBMESH_BONE_ASSIGNMENT ||
			streamID == M_SUBMESH_OPERATION ||
			streamID == M_SUBMESH_TEXTURE_ALIAS))
		{
			switch(streamID)
			{
			case M_SUBMESH_OPERATION:
			//	readSubMeshOperation(stream, pMesh, sm);
				// unsigned short operationType
				unsigned short opType;
				pRead->Read(&opType,sizeof(unsigned short));
				//sm->operationType = static_cast<RenderOperation::OperationType>(opType);
				break;
			case M_SUBMESH_BONE_ASSIGNMENT:
				{
					//readSubMeshBoneAssignment(stream, pMesh, sm);
					VertexBoneAssignment assign;

					// unsigned int vertexIndex;
					pRead->Read(&(assign.vertexIndex),sizeof(unsigned int));
					// unsigned short boneIndex;
					pRead->Read(&(assign.boneIndex),sizeof(unsigned short));
					// float weight;
					pRead->Read(&(assign.weight),sizeof(float));
break;
					unsigned long uBone = 0;
					unsigned long uWeight = 0;
					// get
					subMesh.getBone(assign.vertexIndex,uBone);
					subMesh.getWeight(assign.vertexIndex,uWeight);
					// add
					for (size_t i=0;i<4;++i)
					{
						if (((unsigned char*)&uWeight)[i]==0)
						{
							((unsigned char*)&uWeight)[i] = assign.weight*255;
							((unsigned char*)&uBone)[i] = assign.boneIndex;
							break;
						}
					}
					// set
					subMesh.setBone(assign.vertexIndex,uBone);
					subMesh.setWeight(assign.vertexIndex,uWeight);

					//sub->addBoneAssignment(assign);
				}
				break;
			case M_SUBMESH_TEXTURE_ALIAS:
				//readSubMeshTextureAlias(stream, pMesh, sm);
				std::string aliasName = readString(pRead);
				std::string textureName = readString(pRead);
				//sub->addTextureAlias(aliasName, textureName);
				break;
			}

			if (!pRead->IsEof())
			{
				pRead->Read(&streamID,sizeof(unsigned short));
				pRead->Read(&uLength,sizeof(unsigned int));
			}

		}
		if (!pRead->IsEof())
		{
			// Backpedal back to start of non-submesh stream
			pRead->Move(-STREAM_OVERHEAD_SIZE);
		}
	}
}