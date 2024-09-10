void Mesh3D::draw(SceneGraph *scene,  Sprite3D *sprite, int min, int max)
{
	
	scene->m_ppEffect[m_shader]->Activate();
	
	if(m_blendEnable)
	{
		glEnable (GL_BLEND);
		glBlendFunc (m_blend1, m_blend2);
	} else 
	{
		glDisable (GL_BLEND);
	}
	
	//glEnable(GL_SAMPLE_COVERAGE);
	//glSampleCoverage(1.0, GL_FALSE);
	
	for(unsigned int j = 0; j < scene->m_pnUniformCnt[m_shader]; ++j)
	{
		//unsigned int location = scene->m_ppsUniforms[m_shader][j].nLocation;
		EUniformSemantic semantic = (EUniformSemantic)scene->m_ppsUniforms[m_shader][j].nSemantic; 
		switch(semantic)
		{
			case eUsMVPMATRIX:
			{
				PVRTMat4 mMVP;
				
				/* Passes the model-view-projection matrix (MVP) to the shader to transform the vertices */
				
				if(useSceneModel)
				{
					mMVP = scene->m_mProjection * scene->m_mModelView * sprite->modelView;
				}
				else 
				{
					mMVP = scene->m_mProjection * sprite->modelView;
				}
				glUniformMatrix4fv(scene->m_ppsUniforms[m_shader][j].nLocation, 1, GL_FALSE, mMVP.f);
			}
				break;
			case eUsMODELVIEW:
			{
				PVRTMat4 MV = useSceneModel ? scene->m_mModelView * sprite->modelView : sprite->modelView  ;
				glUniformMatrix4fv(scene->m_ppsUniforms[m_shader][j].nLocation, 1, GL_FALSE, MV.f);
			}
				break;
			case eUsMODELVIEWIT:
			{
				PVRTMat4 mModelViewI, mModelViewIT;
				PVRTMat4 MV = useSceneModel ?  scene->m_mModelView * sprite->modelView : sprite->modelView ;
				/* Passes the inverse transpose of the model-view matrix to the shader to transform the normals */
				mModelViewI = MV.inverse();
				mModelViewIT= mModelViewI.transpose();
				PVRTMat3 ModelViewIT = PVRTMat3(mModelViewIT);
				
				glUniformMatrix3fv(scene->m_ppsUniforms[m_shader][j].nLocation, 1, GL_FALSE, ModelViewIT.f);
			}
				break;
			case eUsVIEWIT:
			{
				PVRTMat4 mViewI, mViewIT;
				
				/* Passes the inverse transpose of the model-view matrix to the shader to transform the normals */
				mViewI = scene->m_mView.inverse();
				mViewIT= mViewI.transpose();
				
				PVRTMat3 ViewIT = PVRTMat3(mViewIT);
				
				glUniformMatrix3fv(scene->m_ppsUniforms[m_shader][j].nLocation, 1, GL_FALSE, ViewIT.f);
			}
				break;	
                
            default:
                break;

		}
	}
	
	
	for(int i32MeshIndex  =min; i32MeshIndex < max; i32MeshIndex++)
	{
		//int i32MeshIndex = i;
		//int i32MeshIndex = m_ModelPOD.pNode[i].nIdx;
		//SPODMesh* submesh = &m_ModelPOD.pMesh[i32MeshIndex];
		//int materialIndex = m_ModelPOD.pNode[i].nIdxMaterial;
		//SPODMaterial* pMaterial = &m_ModelPOD.pMaterial[materialIndex];
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_puiIndexVbo[i32MeshIndex]);
		int materialIndex = meshInfo[i32MeshIndex].materialIndex;
		
		for(unsigned int j = 0; j < scene->m_pnUniformCnt[m_shader]; ++j)
		{
			unsigned int location = scene->m_ppsUniforms[m_shader][j].nLocation;
			EUniformSemantic semantic = (EUniformSemantic)scene->m_ppsUniforms[m_shader][j].nSemantic; 
			switch(semantic)
			{
				case eUsMATERIALCOLORAMBIENT:
				{
					PVRTVec3 vColour = materialInfo[materialIndex].ambientColor;
					glUniform3f(location, vColour.x, vColour.y, vColour.z);
				}
					break;
				case eUsMATERIALCOLORDIFFUSE:
				{
					PVRTVec3 vColour =  materialInfo[materialIndex].diffuseColor;
					glUniform3f(location, vColour.x, vColour.y, vColour.z);
				}
					break;
					
				case eUsPOSITION:
				{
					glBindBuffer(GL_ARRAY_BUFFER, iVertexVBO[ i32MeshIndex] );
					//glVertexAttribPointer(m_ppsUniforms[m_nCurrentShader][j].nLocation, 3, GL_FLOAT, GL_FALSE, 0, (const void*) NULL);
					glVertexAttribPointer(scene->m_ppsUniforms[m_shader][j].nLocation, 3, GL_FLOAT, GL_FALSE, meshInfo[i32MeshIndex].vertexStride, (const void*) NULL);
					
					glEnableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
				}
					break;
				case eUsNORMAL:
				{
					glBindBuffer(GL_ARRAY_BUFFER, iVertexVBO[ i32MeshIndex]);
					glVertexAttribPointer(scene->m_ppsUniforms[m_shader][j].nLocation, 3, GL_FLOAT, GL_FALSE, 
										  meshInfo[i32MeshIndex].normalStride, (const void*)  meshInfo[i32MeshIndex].normalOffset);
					
					glEnableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
				}
					break;
				case eUsTANGENT:
				{
					glBindBuffer(GL_ARRAY_BUFFER, iVertexVBO[ i32MeshIndex]);
					glVertexAttribPointer(scene->m_ppsUniforms[m_shader][j].nLocation, 3, GL_FLOAT, GL_FALSE, 
										  meshInfo[i32MeshIndex].tangentStride, (const void*)  meshInfo[i32MeshIndex].tangentOffset);
					
					glEnableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
					
				}
					break;
				case eUsUV:
				{
					
					//glVertexAttribPointer(m_ppsUniforms[m_nCurrentShader][j].nLocation, 2, GL_FLOAT, GL_FALSE, 0, (const void*) NULL);
					if( meshInfo[i32MeshIndex].uvOffset != 0)
					{
						glBindBuffer(GL_ARRAY_BUFFER, iVertexVBO[i32MeshIndex]);
						glVertexAttribPointer(scene->m_ppsUniforms[m_shader][j].nLocation, 2, GL_FLOAT, GL_FALSE, 
											  meshInfo[i32MeshIndex].uvStride, (const void*)  meshInfo[i32MeshIndex].uvOffset);
						glEnableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
					}
				}
					break;

				case eUsTEXTURE:
				{
					// Set the sampler variable to the texture unit					
					int index = scene->m_ppsUniforms[m_shader][j].nIdx;
					
					switch(index)
					{
						case 0:
						{
							GLuint tex = m_uiTexture[materialIndex];
							glActiveTexture(GL_TEXTURE0);
							glBindTexture(GL_TEXTURE_2D, tex);
							
							//NSLog(@"Normal map %d %d", index, tex);
							glUniform1i(scene->m_ppsUniforms[m_shader][j].nLocation, index);
						}
							break;
						case 1:
						{
							//NSLog(@"Normal map %d %d", index, m_normalMap);
							glActiveTexture(GL_TEXTURE1);
							glBindTexture(GL_TEXTURE_2D, m_normalMap);
						
							glUniform1i(scene->m_ppsUniforms[m_shader][j].nLocation, index);
						}
							break;
						case 2:
						{
							glActiveTexture(GL_TEXTURE2);
							glBindTexture(GL_TEXTURE_CUBE_MAP, m_cubeMap);

							glUniform1i(scene->m_ppsUniforms[m_shader][j].nLocation, index);
						}
							break;
					}
					
				}				
					break;
					
				case eUsTEXTURE_ENABLED:
				{
					int texture_enabled = 0;
					int texture = (signed int)m_uiTexture[materialIndex];
					if(texture != INT_MAX)
						texture_enabled = 1;
						
					//printf("Texture %d %d\n", m_uiTexture[materialIndex], texture_enabled);
					if(m_normalMap > 0)
					{
						texture_enabled |= 2;
					}
					if(m_cubeMap > 0)
					{
						texture_enabled |= 4;
					}
					
					glUniform1i(scene->m_ppsUniforms[m_shader][j].nLocation, texture_enabled);
				}
					break;
				case eUsANIMATION:
				{
					// Float in the range 0..1: contains this objects distance through its animation.
					float fAnimation = 0.5f * scene->m_fViewAngle / PVRT_PI;
					glUniform1f(scene->m_ppsUniforms[m_shader][j].nLocation, fAnimation);
				}
					break;
				case eUsMATERIALSHININESS:
				{
					float shiness =  materialInfo[materialIndex].shiness;
					glUniform1f(location, shiness);
				}
					break;
				case eUsMATERIALCOLORSPECULAR:
				{
					PVRTVec3 vColour =  materialInfo[materialIndex].specularColor;
					glUniform3f(location, vColour.x, vColour.y, vColour.z);
				}
					break;
				case eUsLIGHTPOSWORLD:
				{
					PVRTVec3 position(45, 72, 52);
					glUniform3f(location, position.x , position.y, position.z);
				}
					break;
                default:
                    break;
			}
		}
		// Load the correct texture using our texture lookup table
		
		
		//glBindBuffer(GL_ARRAY_BUFFER, 0);	// Unbind the last buffer used.
		drawMesh(i32MeshIndex, materialIndex);
	}
	
	/*
	 Disable attributes
	 */
	for(unsigned int j = 0; j < scene->m_pnUniformCnt[m_shader]; ++j)
	{
		switch(scene->m_ppsUniforms[m_shader][j].nSemantic)
		{
			case eUsPOSITION:
			{
				glDisableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
			}
				break;
			case eUsNORMAL:
			{
				glDisableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
			}
				break;
			case eUsUV:
			{
				glDisableVertexAttribArray(scene->m_ppsUniforms[m_shader][j].nLocation);
			}
				break;
		
		}
	}

	glDisable(GL_BLEND);

}