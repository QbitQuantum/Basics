void FBXSceneEncoder::loadSkin(FbxMesh* fbxMesh, Model* model)
{
    const int deformerCount = fbxMesh->GetDeformerCount();
    for (int i = 0; i < deformerCount; ++i)
    {
        FbxDeformer* deformer = fbxMesh->GetDeformer(i);
        if (deformer->GetDeformerType() == FbxDeformer::eSkin)
        {
            FbxSkin* fbxSkin = FbxCast<FbxSkin>(deformer);

            MeshSkin* skin = new MeshSkin();

            vector<string> jointNames;
            vector<Node*> joints;
            vector<Matrix> bindPoses;

            const int clusterCount = fbxSkin->GetClusterCount();
            for (int j = 0; j < clusterCount; ++j)
            {
                FbxCluster* cluster = fbxSkin->GetCluster(j);
                assert(cluster);
                FbxNode* linkedNode = cluster->GetLink();
                if (linkedNode && linkedNode->GetSkeleton())
                {
                    const char* jointName = linkedNode->GetName();
                    assert(jointName);
                    jointNames.push_back(jointName);
                    Node* joint = loadNode(linkedNode);
                    assert(joint);
                    joints.push_back(joint);

                    FbxAMatrix matrix;
                    cluster->GetTransformLinkMatrix(matrix);
                    Matrix m;
                    copyMatrix(matrix.Inverse(), m);
                    bindPoses.push_back(m);
                }
            }
            skin->setJointNames(jointNames);
            skin->setJoints(joints);
            skin->setBindPoses(bindPoses);
            model->setSkin(skin);
            break;
        }
    }
}