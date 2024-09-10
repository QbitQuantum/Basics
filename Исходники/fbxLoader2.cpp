void fbxLoader2::setBindPoseCluster(FbxNode *node)
{
	if( node->GetNodeAttribute())
	{
		switch(node->GetNodeAttribute()->GetAttributeType())
		{
		case FbxNodeAttribute::eMesh: 
			FbxMesh *mesh = node->GetMesh();

			for (int j = 0; j<mesh->GetDeformerCount(); j++)
			{
				FbxSkin *skin = (FbxSkin*) mesh->GetDeformer(j,FbxDeformer::eSkin);
				int clusters = skin->GetClusterCount();
				for(int k = 0; k<clusters; k++)
				{
					FbxCluster* cluster = skin->GetCluster(k);
					FbxNode* boneLink = cluster->GetLink();

					if(boneLink)
					{
						std::string nameLink = boneLink->GetName();
						FbxAMatrix translationM;
						FbxAMatrix invert;
						cluster->GetTransformLinkMatrix(translationM);
						cluster->GetTransformMatrix(invert);

						translationM = translationM * invert.Inverse();

						D3DXMATRIX mat = D3DXMATRIX((float)translationM.mData[0].mData[0], (float)translationM.mData[0].mData[1], (float)translationM.mData[0].mData[2], (float)translationM.mData[3].mData[0],
													(float)translationM.mData[1].mData[0], (float)translationM.mData[1].mData[1], (float)translationM.mData[1].mData[2], (float)translationM.mData[3].mData[1],
													(float)translationM.mData[2].mData[0], (float)translationM.mData[2].mData[1], (float)translationM.mData[2].mData[2], (float)translationM.mData[3].mData[2],
													0,0,0,1);

						skeleton->GetBone(skeleton->GetBoneByName(nameLink))->SetTransformation(mat);
					}
				}
			}
			break;
		}
	}
	for (int i = 0; i<node->GetChildCount(); i++)
	{
		FbxNode* child = node->GetChild(i);
		setBindPoseCluster(child);
	}
}