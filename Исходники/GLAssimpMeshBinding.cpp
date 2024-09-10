	void GLAssimpMeshBinding::load(const aiScene *scene, const aiMesh *mesh) {
		// only process if we haven't already loaded this - otherwise is just GL reload
		if (!this->mesh) {
			Property *prop = btGetContext()->appProperties->get("debug_assimp");
			if (prop) {
				debugAssimp = prop->getBoolValue();
			}
			this->mesh = mesh;
			hasBones = (mesh->mNumBones > 0);
			if (hasBones) {
				vertSkinnedAtts = new GLAssimpSkinnedMeshVertex[mesh->mNumVertices];
			} else {
				vertBasicAtts = new GLAssimpMeshVertex[mesh->mNumVertices];
			}
			if (hasBones) {
				for (U32 i = 0; i < mesh->mNumVertices; i++) {
					aiVector3D vert = mesh->mVertices[i];
					aiVector3D normal = mesh->mNormals[i];
					aiVector3D uv = mesh->mTextureCoords[0][i];
					vertSkinnedAtts[i].position = Vector3f(vert.x, vert.y, vert.z);
					vertSkinnedAtts[i].normal = Vector3f(normal.x, normal.y, normal.z);
					vertSkinnedAtts[i].uv = Vector2f(uv.x, uv.y);
					vertSkinnedAtts[i].bones = Vector4b(0, 0, 0, 0);
					vertSkinnedAtts[i].weights = Vector4f(0, 0, 0, 0);
				}
				U32 *weightCounts = new U32[mesh->mNumVertices];
				memset(weightCounts, 0, mesh->mNumVertices * 4);
				BOOL32 discardedWeights = FALSE;
				for (U8 i = 0; i < (U8)mesh->mNumBones; i++) {
					aiBone *bone = mesh->mBones[i];
					for (U32 j = 0; j < bone->mNumWeights; j++) {
						U32 vertIdx = bone->mWeights[j].mVertexId;
						F32 weight = bone->mWeights[j].mWeight;
						U32 weightNum = weightCounts[vertIdx];
						if (weightNum < 4) {
							vertSkinnedAtts[vertIdx].bones[weightNum] = i;
							vertSkinnedAtts[vertIdx].weights[weightNum] = weight;
							weightCounts[vertIdx]++;
						} else {
							discardedWeights = TRUE;
						}
					}
				}
				delete [] weightCounts;
				if (discardedWeights) {
					logmsg("AssimpBind Warning: Too many bone weights - discarding!");
				}
			} else {
				for (U32 i = 0; i < mesh->mNumVertices; i++) {
					aiVector3D vert = mesh->mVertices[i];
					aiVector3D normal = mesh->mNormals[i];
					aiVector3D uv = mesh->mTextureCoords[0][i];
					vertBasicAtts[i].position = Vector3f(vert.x, vert.y, vert.z);
					vertBasicAtts[i].normal = Vector3f(normal.x, normal.y, normal.z);
					vertBasicAtts[i].uv = Vector2f(uv.x, uv.y);
				}
			}
			loadMaterials(scene->mMaterials[mesh->mMaterialIndex]);
		}
		U16 *faceIndices = new U16[this->mesh->mNumFaces * 3];
		for (U32 i = 0; i < this->mesh->mNumFaces; i++) {
			aiFace face = this->mesh->mFaces[i];
			faceIndices[i*3] = face.mIndices[0];
			faceIndices[i*3+1] = face.mIndices[1];
			faceIndices[i*3+2] = face.mIndices[2];
		}
		loadGeometry(this->mesh, faceIndices);
		delete [] faceIndices;
	}