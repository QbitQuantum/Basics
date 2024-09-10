void MeshImporter::LoadWeight(FbxMesh* fbxMesh, MeshEntry* mesh)
{
	int numSkin = fbxMesh->GetDeformerCount(FbxDeformer::eSkin);
	
	if (numSkin == 0)
	{
		return;
	}

	assert(numSkin == 1);

	// Assume only one deformer
	FbxSkin* fbxSkin = static_cast<FbxSkin*>(fbxMesh->GetDeformer(0, FbxDeformer::eSkin));
	int numCluster = fbxSkin->GetClusterCount();
	int numControlPoints = fbxMesh->GetControlPointsCount();
	vector<VertexWeight> tmpWeightList(numControlPoints);

	for (int i = 0; i < numCluster; i++)
	{
		FbxCluster* fbxCluster = fbxSkin->GetCluster(i);

		if (!fbxCluster->GetLink())
		{
			continue;
		}

		unsigned int boneIndex = model->skeleton->bones.size();

		assert(fbxCluster->GetLinkMode() == FbxCluster::eNormalize);

		// Read skeleton bones data (transformation matrix of each bone)
		string boneName(fbxCluster->GetLink()->GetName());

		if (!model->skeleton->FindBoneByName(boneName))
		{
			if (boneIndex >= MAXBONE)
			{
				PrintTab("Too many bones to load!!");
			}
			else
			{
				// Read weights of each vertex
				int numIndexInCluster = fbxCluster->GetControlPointIndicesCount();
				int* indicesInCluster = fbxCluster->GetControlPointIndices();
				double* weights = fbxCluster->GetControlPointWeights();

				for (int j = 0; j < numIndexInCluster; j++)
				{
					tmpWeightList[indicesInCluster[j]].AddBoneData(boneIndex, weights[j]);
				}

				// Normalize weights
				/*for (int inVert = 0; inVert < tmpWeightList.size(); inVert++)
				{
					tmpWeightList[inVert].Normalize();
				}*/

				// Read animation bone matrix
				FbxAMatrix fbxGlobalBoneBaseMatrix;// = fbxCluster->GetLink()->EvaluateGlobalTransform().Inverse().Transpose();

				FbxAMatrix referenceGlobalInitPosition;
				FbxAMatrix clusterGlobalInitPosition;

				fbxCluster->GetTransformMatrix(referenceGlobalInitPosition);
				fbxCluster->GetTransformLinkMatrix(clusterGlobalInitPosition);

				fbxGlobalBoneBaseMatrix = clusterGlobalInitPosition.Inverse() * referenceGlobalInitPosition;

				// To be considered when importing Maya fbx model
				//FbxAMatrix geoMatrix = GetTransformMatrix(fbxCluster->GetLink());

				Bone bone;
				bone.name = boneName;
				bone.boneIndex = boneIndex;
				bone.fbxNode = fbxCluster->GetLink();
				bone.globalBindposeInverseMatrix = fbxGlobalBoneBaseMatrix;

				model->skeleton->bones.push_back(bone);
			}
		}
	}

	// Deployed in the index
	for (unsigned int i = 0; i < mesh->numVertices; i++)
	{
		mesh->vertices[i].boneIndices.x = tmpWeightList[mesh->indices[i]].boneWeight[0].first;
		mesh->vertices[i].boneIndices.y = tmpWeightList[mesh->indices[i]].boneWeight[1].first;
		mesh->vertices[i].boneIndices.z = tmpWeightList[mesh->indices[i]].boneWeight[2].first;
		mesh->vertices[i].boneIndices.w = tmpWeightList[mesh->indices[i]].boneWeight[3].first;

		mesh->vertices[i].weights.x = tmpWeightList[mesh->indices[i]].boneWeight[0].second;
		mesh->vertices[i].weights.y = tmpWeightList[mesh->indices[i]].boneWeight[1].second;
		mesh->vertices[i].weights.z = tmpWeightList[mesh->indices[i]].boneWeight[2].second;
		mesh->vertices[i].weights.w = tmpWeightList[mesh->indices[i]].boneWeight[3].second;
	}
}