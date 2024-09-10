	//---------------------------------------------------------------
	void ControllerExporter::exportSkinController( ExportNode* exportNode, SkinController* skinController, const String& controllerId, const String& skinSource )
	{
		INode* iNode = exportNode->getINode();

		if ( !skinController )
			return;

		// We cannot use skin->GetContextInterface to get ISkinContextData if we are exporting an XRef, since we cannot access
		// the INode the object belongs to in the referenced file. To solve this problem, we temporarily create an INode, that references
		// the object and delete it immediately. 
		ISkinInterface* skinInterface = getISkinInterface( exportNode, skinController );

		if ( !skinInterface )
			return;

		openSkin(controllerId, skinSource);
	
		Matrix3 bindShapeTransformationMatrix;
		skinInterface->getSkinInitTM(bindShapeTransformationMatrix, true);	
		double  bindShapeTransformationArray[4][4];
		VisualSceneExporter::matrix3ToDouble4x4(bindShapeTransformationArray, bindShapeTransformationMatrix);

		addBindShapeTransform(bindShapeTransformationArray);

		int jointCount = skinInterface->getNumBones();
		INodeList boneINodes;


		// Export joints source
		String jointsId = controllerId + JOINTS_SOURCE_ID_SUFFIX;
		COLLADASW::NameSource jointSource(mSW);
		jointSource.setId(jointsId);
		jointSource.setArrayId(jointsId + ARRAY_ID_SUFFIX);
		jointSource.setAccessorStride(1);
		jointSource.getParameterNameList().push_back("JOINT");
		jointSource.setAccessorCount(jointCount);
		jointSource.prepareToAppendValues();

		for (int i = 0; i <  jointCount; ++i)
		{
			// there should not be any null bone.
			// the ISkin::GetBone, not GetBoneFlat, function is called here.
			INode* boneNode = skinInterface->getBone(i);
			assert(boneNode);
			boneINodes.push_back(boneNode);

			ExportNode* jointExportNode = mExportSceneGraph->getExportNode(boneNode);
			assert(jointExportNode);

			if ( !jointExportNode->hasSid() )
				jointExportNode->setSid(mExportSceneGraph->createJointSid());

			jointExportNode->setIsJoint();

			jointSource.appendValues(jointExportNode->getSid());
		}
		jointSource.finish();

		determineReferencedJoints(exportNode, skinController);

		//export inverse bind matrix source
		String inverseBindMatrixId = controllerId + BIND_POSES_SOURCE_ID_SUFFIX;
		COLLADASW::Float4x4Source inverseBindMatrixSource(mSW);
		inverseBindMatrixSource.setId(inverseBindMatrixId);
		inverseBindMatrixSource.setArrayId(inverseBindMatrixId + ARRAY_ID_SUFFIX);
		inverseBindMatrixSource.setAccessorStride(16);
		inverseBindMatrixSource.getParameterNameList().push_back("TRANSFORM");
		inverseBindMatrixSource.setAccessorCount(jointCount);
		inverseBindMatrixSource.prepareToAppendValues();

		for (int i = 0; i <  jointCount; ++i)
		{
			INode* boneNode = boneINodes[i];

			Matrix3 bindPose;
			if ( !skinInterface->getBoneInitTM(boneNode, bindPose) )
			{
				bindPose = VisualSceneExporter::getWorldTransform( boneNode, mDocumentExporter->getOptions().getAnimationStart() );
			}
			bindPose.Invert();

			double bindPoseArray[4][4];
			VisualSceneExporter::matrix3ToDouble4x4(bindPoseArray, bindPose);
			inverseBindMatrixSource.appendValues(bindPoseArray);
		}
		inverseBindMatrixSource.finish();

		int vertexCount = skinInterface->getNumVertices();
		
		//count weights, excluding the ones equals one
		int weightsCount = 1;
		for (int i = 0; i < vertexCount; ++i)
		{
			int jointCount = skinInterface->getNumAssignedBones(i);
			for (int p = 0; p < jointCount; ++p)
			{
				float weight = skinInterface->getBoneWeight(i, p);
				if ( !COLLADASW::MathUtils::equals(weight, 1.0f) )
					weightsCount++;
			}
		}

		//export weights source
		String weightsId = controllerId + WEIGHTS_SOURCE_ID_SUFFIX;
		COLLADASW::FloatSource weightsSource(mSW);
		weightsSource.setId(weightsId);
		weightsSource.setArrayId(weightsId + ARRAY_ID_SUFFIX);
		weightsSource.setAccessorStride(1);
		weightsSource.getParameterNameList().push_back("WEIGHT");
		weightsSource.setAccessorCount(weightsCount);
		weightsSource.prepareToAppendValues();

		weightsSource.appendValues(1.0);
		for (int i = 0; i < vertexCount; ++i)
		{
			int jointCount = skinInterface->getNumAssignedBones(i);
			for (int p = 0; p < jointCount; ++p)
			{
				float weight = skinInterface->getBoneWeight(i, p);
				if ( !COLLADASW::MathUtils::equals(weight, 1.0f) )
					weightsSource.appendValues(weight);
			}
		}
		weightsSource.finish();

		COLLADASW::JointsElement joints(mSW);
		joints.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::JOINT, "#" + jointsId));
		joints.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::BINDMATRIX, "#" + inverseBindMatrixId));
		joints.add();

		COLLADASW::VertexWeightsElement vertexWeights(mSW);
		COLLADASW::Input weightInput(COLLADASW::InputSemantic::WEIGHT, "#" + weightsId);
		vertexWeights.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::JOINT, "#" + jointsId, 0));
		vertexWeights.getInputList().push_back(COLLADASW::Input(COLLADASW::InputSemantic::WEIGHT, "#" + weightsId, 1));
		vertexWeights.setCount(vertexCount);

		vertexWeights.prepareToAppendVCountValues();

		for (int i = 0; i < vertexCount; ++i)
			vertexWeights.appendValues(skinInterface->getNumAssignedBones(i));

		vertexWeights.CloseVCountAndOpenVElement();

		int currentIndex = 1;
		for (int i = 0; i < vertexCount; ++i)
		{
			int jointCount = skinInterface->getNumAssignedBones(i);
			for (int p = 0; p < jointCount; ++p)
			{
				vertexWeights.appendValues(skinInterface->getAssignedBone(i, p));
				float weight = skinInterface->getBoneWeight(i, p);
				if ( !COLLADASW::MathUtils::equals(weight, 1.0f) )
				{
					vertexWeights.appendValues(currentIndex++);
				}
				else
				{
					vertexWeights.appendValues(0);
				}
			}
		}
		vertexWeights.finish();
		closeSkin();
		skinInterface->releaseMe();
	}