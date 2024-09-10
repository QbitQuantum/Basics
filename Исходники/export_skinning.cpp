void CExportNel::addSkeletonBindPos (INode& skinedNode, mapBoneBindPos& boneBindPos)
{
	// Return success
	uint ok=NoError;

	// Get the skin modifier
	Modifier* skin=getModifier (&skinedNode, SKIN_CLASS_ID);

	// Found it ?
	if (skin)
	{
		// Get a com_skin2 interface
		ISkin *comSkinInterface=(ISkin*)skin->GetInterface (SKIN_INTERFACE);

		// Should been controled with isSkin before.
		nlassert (comSkinInterface);

		// Found com_skin2 ?
		if (comSkinInterface)
		{
			// Get local data
			ISkinContextData *localData=comSkinInterface->GetContextInterface(&skinedNode);

			// Should been controled with isSkin before.
			nlassert (localData);

			// Found ?
			if (localData)
			{
				// Check same vertices count
				uint vertCount=localData->GetNumPoints();

				// For each vertex
				for (uint vert=0; vert<vertCount; vert++)
				{
					// Get bones count for this vertex
					uint boneCount=localData->GetNumAssignedBones (vert);

					// For each bones
					for (uint bone=0; bone<boneCount; bone++)
					{
						// Get the bone id
						int boneId=localData->GetAssignedBone(vert, bone);

						// Get bone INode*
						INode *boneNode=comSkinInterface->GetBone(boneId);

						// Get the bind matrix of the bone
						Matrix3 bindPos;
						comSkinInterface->GetBoneInitTM(boneNode, bindPos);

						// Add an entry inthe map
						boneBindPos.insert (mapBoneBindPos::value_type (boneNode, bindPos));
					}
				}
			}

			// Release the interface
			skin->ReleaseInterface (SKIN_INTERFACE, comSkinInterface);
		}
	}
	else
	{
		// Get the skin modifier
		Modifier* skin=getModifier (&skinedNode, PHYSIQUE_CLASS_ID);

		// Should been controled with isSkin before.
		nlassert (skin);

		// Found it ?
		if (skin)
		{
			// Get a com_skin2 interface
			IPhysiqueExport *physiqueInterface=(IPhysiqueExport *)skin->GetInterface (I_PHYINTERFACE);

			// Should been controled with isSkin before.
			nlassert (physiqueInterface);

			// Found com_skin2 ?
			if (physiqueInterface)
			{
				// Get local data
				IPhyContextExport *localData=physiqueInterface->GetContextInterface(&skinedNode);

				// Should been controled with isSkin before.
				nlassert (localData);

				// Found ?
				if (localData)
				{
					// Use rigid export
					localData->ConvertToRigid (TRUE);

					// Allow blending
					localData->AllowBlending (TRUE);

					// Check same vertices count
					uint vertCount=localData->GetNumberVertices();

					// For each vertex
					for (uint vert=0; vert<vertCount; vert++)
					{
						if (vert==111)
							int toto=0;
						// Get a vertex interface
						IPhyVertexExport *vertexInterface=localData->GetVertexInterface (vert);

						// Check if it is a rigid vertex or a blended vertex
						int type=vertexInterface->GetVertexType ();
						if (type==RIGID_TYPE)
						{
							// this is a rigid vertex
							IPhyRigidVertex			*rigidInterface=(IPhyRigidVertex*)vertexInterface;

							// Get bone INode*
							INode *bone=rigidInterface->GetNode();

							// Get the bind matrix of the bone
							Matrix3 bindPos;
							int res=physiqueInterface->GetInitNodeTM (bone, bindPos);
							nlassert (res==MATRIX_RETURNED);

							// Add an entry inthe map
							if (boneBindPos.insert (mapBoneBindPos::value_type (bone, bindPos)).second)
							{
#ifdef NL_DEBUG
								// *** Debug info

								// Bone name
								std::string boneName=getName (*bone);

								// Local matrix
								Matrix3 nodeTM;
								nodeTM=bone->GetNodeTM (0);

								// Offset matrix
								Matrix3 offsetScaleTM (TRUE);
								Matrix3 offsetRotTM (TRUE);
								Matrix3 offsetPosTM (TRUE);
								ApplyScaling (offsetScaleTM, bone->GetObjOffsetScale ());
								offsetRotTM.SetRotate (bone->GetObjOffsetRot ());
								offsetPosTM.SetTrans (bone->GetObjOffsetPos ());
								Matrix3 offsetTM = offsetScaleTM * offsetRotTM * offsetPosTM;

								// Local + offset matrix
								Matrix3 nodeOffsetTM = offsetTM * nodeTM;

								// Init TM
								Matrix3 initTM;
								int res=physiqueInterface->GetInitNodeTM (bone, initTM);
								nlassert (res==MATRIX_RETURNED);

								// invert
								initTM.Invert();
								Matrix3 compNode=nodeTM*initTM;
								Matrix3 compOffsetNode=nodeOffsetTM*initTM;
								Matrix3 compOffsetNode2=nodeOffsetTM*initTM;
#endif // NL_DEBUG
							}
						}
						else
						{
							// It must be a blendable vertex
							nlassert (type==RIGID_BLENDED_TYPE);
							IPhyBlendedRigidVertex	*blendedInterface=(IPhyBlendedRigidVertex*)vertexInterface;

							// For each bones
							uint boneIndex;
							uint count=(uint)blendedInterface->GetNumberNodes ();
							for (boneIndex=0; boneIndex<count; boneIndex++)
							{
								// Get the bone pointer
								INode *bone = blendedInterface->GetNode(boneIndex);

								if (bone == NULL)
								{
									nlwarning("bone == NULL; boneIndex = %i / %i", boneIndex, count);
								}
								else
								{
									// Get the bind matrix of the bone
									Matrix3 bindPos;
									int res = physiqueInterface->GetInitNodeTM (bone, bindPos);

									if (res != MATRIX_RETURNED)
									{
										nlwarning("res != MATRIX_RETURNED; res = %i; boneIndex = %i / %i", res, boneIndex, count);
										nlwarning("bone = %i", (uint32)(void *)bone);
										std::string boneName = getName (*bone);
										nlwarning("boneName = %s", boneName.c_str());
										nlassert(false);
									}

									// Add an entry inthe map
									if (boneBindPos.insert (mapBoneBindPos::value_type (bone, bindPos)).second)
									{
	#ifdef NL_DEBUG
										// *** Debug info

										// Bone name
										std::string boneName=getName (*bone);

										// Local matrix
										Matrix3 nodeTM;
										nodeTM=bone->GetNodeTM (0);

										// Offset matrix
										Matrix3 offsetScaleTM (TRUE);
										Matrix3 offsetRotTM (TRUE);
										Matrix3 offsetPosTM (TRUE);
										ApplyScaling (offsetScaleTM, bone->GetObjOffsetScale ());
										offsetRotTM.SetRotate (bone->GetObjOffsetRot ());
										offsetPosTM.SetTrans (bone->GetObjOffsetPos ());
										Matrix3 offsetTM = offsetScaleTM * offsetRotTM * offsetPosTM;

										// Local + offset matrix
										Matrix3 nodeOffsetTM = offsetTM * nodeTM;

										// Init TM
										Matrix3 initTM;
										int res=physiqueInterface->GetInitNodeTM (bone, initTM);
										nlassert (res==MATRIX_RETURNED);

										// invert
										initTM.Invert();
										Matrix3 compNode=nodeTM*initTM;
										Matrix3 compOffsetNode=nodeOffsetTM*initTM;
										Matrix3 compOffsetNode2=nodeOffsetTM*initTM;
#endif // NL_DEBUG
									}
								}
							}
						}
					
						// Release vertex interfaces
						localData->ReleaseVertexInterface (vertexInterface);
					}

					// Release locaData interface
					physiqueInterface->ReleaseContextInterface (localData);
				}

				// Release the interface
				skin->ReleaseInterface (SKIN_INTERFACE, physiqueInterface);
			}
		}
	}
}