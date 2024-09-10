	// Load blend shape poses
	bool BlendShape::loadPoses(ParamList &params, std::vector<vertex> &vertices,long numVertices,long offset,long targetIndex)
	{
		if (params.useSharedGeom)
		{
			assert(targetIndex == 0);
			m_target = T_MESH;
		}
		else
		{
			assert(offset == 0);
			poseGroup new_pg;
			m_target = T_SUBMESH;
			new_pg.targetIndex = targetIndex;
			m_poseGroups.insert(std::pair<int,poseGroup>(targetIndex,new_pg));
		}
		poseGroup& pg = m_poseGroups.find(targetIndex)->second;

		if(m_pGameNode && m_pMorphR3)
		{
            // Disable all skin Modifiers.
            std::vector<Modifier*> disabledSkinModifiers;
            IGameObject* pGameObject = m_pGameNode->GetIGameObject();
            if( pGameObject )
            {
                int numModifiers = pGameObject->GetNumModifiers();
                for( int i = 0; i < numModifiers; ++i )
                {
                    IGameModifier* pGameModifier = pGameObject->GetIGameModifier(i);
                    if( pGameModifier )
                    {
                        if( pGameModifier->IsSkin() )
                        {
                            Modifier* pModifier = pGameModifier->GetMaxModifier();
                            if( pModifier )
                            {
                                if( pModifier->IsEnabled() )
                                {
                                    disabledSkinModifiers.push_back(pModifier);
                                    pModifier->DisableMod();
                                }
                            }
                        }
                    }
                }
            }

			// Get the original mesh from the IGameNode.  Not using IGame here
			// since MorphR3 doesn't allow for it.  Also we don't know if our vertices
			// are in object or world space, so we'll just calculate diffs directly from 
			// the Max meshes and modify the coordinate system manually.  
			// Obtained method of getting mesh from 3D Studio Max SDK Training session by
			// David Lanier.
 			bool DeleteObjectWhenDone;
			const ObjectState& objectState = m_pGameNode->GetMaxNode()->EvalWorldState(GetCOREInterface()->GetTime());
			Object *origMeshObj = objectState.obj;
			if (!origMeshObj->CanConvertToType(Class_ID(TRIOBJ_CLASS_ID, 0)))
			{
				FxOgreMaxExporterLog( "Could not access original mesh for morph target comparison.");
				return false;
			}

			// Calculate the DiffTM matrix.  This is the difference between the INode's world transform
			// which is used to calculate the morph verticies, and the IGameNode's world transform, which is used
			// to calculate the Ogre mesh's verticies.
			Matrix3 DiffTM = m_pGameNode->GetObjectTM(GetCOREInterface()->GetTime()).ExtractMatrix3();

			// The below code is not well tested as FaceFX needs content in the native coordinates.
			// I've seen the direction of the morph movement flipped on some content when in Y-up mode 
			// which sets the coordinate system to IGAME_OGL.
			// I can't get this to work on all the morph examples I have however.
			IGameConversionManager* pConversionManager = GetConversionManager();
			if(IGameConversionManager::IGAME_OGL == pConversionManager->GetCoordSystem())
			{			
				Matrix3 conv = Matrix3(Point3(1,0,0), Point3(0,0,1), Point3(0,-1,0), Point3(0,0,0));
				DiffTM = DiffTM * conv;
			}

			TriObject *origMeshTriObj = (TriObject *) origMeshObj->ConvertToType(GetCOREInterface()->GetTime(), Class_ID(TRIOBJ_CLASS_ID, 0));
			if (origMeshObj != origMeshTriObj) DeleteObjectWhenDone = true;
			Mesh& origMesh = origMeshTriObj->GetMesh();
			const int NumVerts = origMesh.getNumVerts();
 

			for( int i = 0; i < m_pMorphR3->chanBank.size() && i < MR3_NUM_CHANNELS; ++i )
			{
				if( m_pMorphR3->chanBank[i].mActive )
				{
					morphChannel* pMorphChannel = &m_pMorphR3->chanBank[i];	
					if( pMorphChannel )
					{
						pMorphChannel->rebuildChannel();

						std::string posename = string_tools::string_cast<ogre_string_type>(pMorphChannel->mName.data());
						int numMorphVertices = pMorphChannel->mNumPoints;
						
						if( numMorphVertices != origMesh.getNumVerts() )
						{
							MessageBox(GetCOREInterface()->GetMAXHWnd(), _T("Morph targets have failed to export becuase the morph vertex count did not match the base mesh.  Collapse the modifier stack prior to export, as smoothing is not supported with morph target export."), _T("Morph Target Export Failed."), MB_OK);
							return false;
						}
						else
						{
							FxOgreMaxExporterLog( "Exporting Morph target: %s with %d vertices.\n", posename.c_str(), numMorphVertices);
							FxOgreMaxExporterLog( "Mesh has %d vertices.\n", numVertices);
							FxOgreMaxExporterLog( "%d total vertices.\n", vertices.size());
							assert(offset+numVertices <= vertices.size());
							// create a new pose
							pose p;
							p.poseTarget = m_target;
							p.index = targetIndex;
							p.blendShapeIndex = i;
							p.name = posename;
							p.pMChannel = pMorphChannel;

							size_t numPoints = pMorphChannel->mPoints.size();
							std::vector<Point3> vmPoints;
							vmPoints.reserve(numPoints);
							for( size_t k = 0; k < numPoints; ++k )
							{
								vmPoints.push_back(pMorphChannel->mPoints[k]);
							}

							Box3 morphBoundingBox;
							// calculate vertex offsets
							for (int k=0; k<numVertices; k++)
							{
								vertexOffset vo;
								assert ((offset+k)<vertices.size());

								vertex v = vertices[offset+k];
								assert(v.index < numMorphVertices);
								assert(v.index < origMesh.getNumVerts());

								Point3 meshVert = origMesh.getVert(v.index);
								Point3 morphVert = vmPoints[v.index];

								Point3 diff = morphVert - meshVert;

								// Transform our morph vertex movements by whatever
								// scaling/rotation is being done by IGame..
								Point3 ogreSpacediff = DiffTM.VectorTransform(diff);


								// Add this point to the bounding box
								morphBoundingBox += morphVert;

								vo.x = ogreSpacediff.x * params.lum;
								vo.y = ogreSpacediff.y * params.lum;
								vo.z = ogreSpacediff.z * params.lum;	

								vo.index = offset+k;
								if (fabs(vo.x) < PRECISION)
									vo.x = 0;
								if (fabs(vo.y) < PRECISION)
									vo.y = 0;
								if (fabs(vo.z) < PRECISION)
									vo.z = 0;
								if ((vo.x!=0) || (vo.y!=0) || (vo.z!=0))
									p.offsets.push_back(vo);
							}
							// add pose to pose list
							if (p.offsets.size() > 0)
							{
								pg.poses.push_back(p);
							}
							if (params.bsBB)
							{
								// update bounding boxes of loaded submeshes
								for (int j=0; j<params.loadedSubmeshes.size(); j++)
								{
									Point3 min = morphBoundingBox.Min() * params.lum;
									Point3 max = morphBoundingBox.Max() * params.lum;
									// Update coordinate system here.
									Point3 newMin, newMax;
									newMin.x = min.x;
									newMin.y = min.z;
									newMin.z = min.y;
									Box3 newBox(newMin, newMax);
									if (params.exportWorldCoords)
										newBox = newBox * m_pGameNode->GetWorldTM(GetCOREInterface()->GetTime()).ExtractMatrix3();
									params.loadedSubmeshes[j]->m_boundingBox += newBox;
								}
							}
						}

					}
				}
			}
            // Re-enable skin modifiers.
            for( int i = 0; i < disabledSkinModifiers.size(); ++i )
            {
                disabledSkinModifiers[i]->EnableMod();
            }
			// According to David Lanier, this should be deleted, but I get crashes when exporting blendShapes
			// without shared geometry when I use the object for the second time.  Perhaps it
			// can only be used/deleted once.  Even without shared geometry, I'll get a strange crash
			// a few seconds after successful export with this here.
//			if (DeleteObjectWhenDone)
//				origMeshTriObj->DeleteMe();
		}
		return true;
	}