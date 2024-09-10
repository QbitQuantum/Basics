//FbxAMatrix ComputeTotalMatrix(FbxNode* node, FbxTime time = FBXSDK_TIME_INFINITE){
//
//}
SkinInfo::SkinInfo(FbxNode* meshNode) :
_node(meshNode), _mesh(meshNode->GetMesh()), _skin(nullptr)
{
	int deformerCount = _mesh->GetDeformerCount();
	for (auto ix = 0; ix < deformerCount; ++ix){
		auto skin = reinterpret_cast<FbxSkin*>(_mesh->GetDeformer(ix, FbxDeformer::eSkin));
		if (skin){
			_skin = skin;
			break;
		}
	}
	if (!_skin){
		return;
	}

	std::vector<FbxPose*> bindPoses;
	auto poseCount = _node->GetScene()->GetPoseCount();
	for (auto ix = 0; ix < poseCount; ++ix){
		auto pose = _node->GetScene()->GetPose(ix);
		if (pose->IsBindPose()){
			bindPoses.push_back(pose);
		}
	}

	std::vector<FbxNode*> unsortedFlatListOfNodes;
	std::vector<FbxCluster*> unsortedFlatListOfClusters;
	auto clusterCount = _skin->GetClusterCount();
	for (auto ix = 0; ix < clusterCount; ++ix){
		auto cluster = _skin->GetCluster(ix);
		if (!cluster)
		{
			std::cout << "Invalid skin" << std::endl;
			_skin = nullptr;
			return;
		}
		auto linkNode = cluster->GetLink();
		if (!linkNode){
			std::cout << "Invalid skin" << std::endl;
			_skin = nullptr;
			return;
		}
		unsortedFlatListOfClusters.push_back(cluster);
		unsortedFlatListOfNodes.push_back(linkNode);
	}

	ComputeBoneHierarchy(unsortedFlatListOfNodes, unsortedFlatListOfClusters, _bones, _fbxClusterIndexToBoneIndex, _controlPointToBoneIndicesAndWeights);
	auto deformType = _skin->GetDeformerType();

	auto geometryTransform = GetGeometryTransformation(meshNode);
	// compute all bones global inverse and global matrix
	for (auto& bone : _bones){
		FbxAMatrix transformMatrix;
		FbxAMatrix transformLinkMatrix;
		FbxMatrix globalBindposeInverseMatrix;

		bone.cluster->GetTransformMatrix(transformMatrix);	// The transformation of the mesh at binding time
		bone.cluster->GetTransformLinkMatrix(transformLinkMatrix);	// The transformation of the cluster(joint) at binding time from joint space to world space
		/*for (auto pose : bindPoses){
			auto inPoseIndex = pose->Find(bone.linkNode);
			if (inPoseIndex >= 0){
				auto tempMat = pose->GetMatrix(inPoseIndex);
				transformLinkMatrix = *(FbxAMatrix*) (double*) &tempMat;
				break;
			}
		}*/
		globalBindposeInverseMatrix = FbxMatrix(transformLinkMatrix.Inverse()) * FbxMatrix(transformMatrix) * geometryTransform;


		bone.matrixGlobalBindPose = ConvertToBabylonCoordinateSystem(globalBindposeInverseMatrix.Inverse());
	

		if (bone.parentBoneIndex == -1){
			bone.matrixLocalBindPose = bone.matrixGlobalBindPose;
		}
		else{
			bone.matrixLocalBindPose =
				_bones[bone.parentBoneIndex].matrixGlobalBindPose.Inverse()* bone.matrixGlobalBindPose;
			
		}
	}


	// compute anim
	auto animStack = _node->GetScene()->GetCurrentAnimationStack();
	FbxString animStackName = animStack->GetName();
	//FbxTakeInfo* takeInfo = node->GetScene()->GetTakeInfo(animStackName);
	auto animTimeMode = GlobalSettings::Current().AnimationsTimeMode;
	auto animFrameRate = GlobalSettings::Current().AnimationsFrameRate();
	auto startFrame = animStack->GetLocalTimeSpan().GetStart().GetFrameCount(animTimeMode);
	auto endFrame = animStack->GetLocalTimeSpan().GetStop().GetFrameCount(animTimeMode);
	auto animLengthInFrame = endFrame - startFrame + 1;


	for (auto ix = 0; ix < animLengthInFrame; ix++){
		FbxTime currTime;
		currTime.SetFrame(startFrame + ix, animTimeMode);


		auto currTransformOffset = FbxMatrix(meshNode->EvaluateGlobalTransform(currTime)) * geometryTransform;
		auto currTransformOffsetInverse = currTransformOffset.Inverse();

		// compute global transform and local
		for (auto& bone : _bones){
			BoneAnimKeyFrame kf;
			kf.frame = ix;
			kf.matrixGlobal = ConvertToBabylonCoordinateSystem(currTransformOffsetInverse*bone.linkNode->EvaluateGlobalTransform(currTime));
			


			if (bone.parentBoneIndex == -1){
				kf.matrixLocal = kf.matrixGlobal;
			}
			else{
				auto& parentBone = _bones[bone.parentBoneIndex];
				
				kf.matrixLocal = //bone.matrixLocalBindPose;
					parentBone.keyFrames[parentBone.keyFrames.size() - 1].matrixGlobal.Inverse()* kf.matrixGlobal;

			}


			bone.keyFrames.push_back(kf);
		}

	}
}