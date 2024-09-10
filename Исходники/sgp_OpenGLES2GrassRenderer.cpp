void COpenGLES2GrassRenderer::render(CSGPGrass* pGrass)
{	
	SGPVertex_GRASS_GLES2 tempData;
	if( m_GrassClusterInstanceArray.size() > 0 )
	{
		COpenGLES2GrassRenderer::Sorter CompareGrassInstance(m_pRenderDevice);
		m_GrassClusterInstanceArray.sort(CompareGrassInstance);
		
		uint32 nGrassClusterNum = jmin(m_GrassClusterInstanceArray.size(), INIT_GRASSCLUSTERINSTANCE_NUM);
		uint32 nSizeData = sizeof(SGPVertex_GRASS_GLES2) * nGrassClusterNum * (4*3);
		uint32 nVBOffset = (m_GrassClusterInstanceArray.size() <= INIT_GRASSCLUSTERINSTANCE_NUM) ? 0 : m_GrassClusterInstanceArray.size() - INIT_GRASSCLUSTERINSTANCE_NUM;
		SGPVertex_GRASS_Cluster* pGrassClusterSrc = m_GrassClusterInstanceArray.getRawDataPointer() + nVBOffset;
		
		// update Dynamic Grass Instance Buffer
		glBindBuffer(GL_ARRAY_BUFFER, m_nGrassClusterVBOID);
		glBufferData(GL_ARRAY_BUFFER, nSizeData, NULL, GL_STREAM_DRAW);
		SGPVertex_GRASS_GLES2* pGrassVertex = (SGPVertex_GRASS_GLES2*)m_pRenderDevice->extGlMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY_OES);

		for( uint32 i=0; i<nGrassClusterNum; i++ )
		{
			tempData.vNormal[0] = ( pGrassClusterSrc[i].vPackedNormal[0] / 255.0f - 0.5f ) * 2.0f;
			tempData.vNormal[1] = ( pGrassClusterSrc[i].vPackedNormal[1] / 255.0f - 0.5f ) * 2.0f;
			tempData.vNormal[2] = ( pGrassClusterSrc[i].vPackedNormal[2] / 255.0f - 0.5f ) * 2.0f;
			tempData.vNormal[3] = pGrassClusterSrc[i].vPackedNormal[3] / 255.0f;
			tempData.vColor[0] = pGrassClusterSrc[i].vColor[0];
			tempData.vColor[1] = pGrassClusterSrc[i].vColor[1];
			tempData.vColor[2] = pGrassClusterSrc[i].vColor[2];
			tempData.vColor[3] = pGrassClusterSrc[i].vColor[3];
			tempData.LMtu = pGrassClusterSrc[i].vPosition[0] / m_pRenderDevice->GetWorldSystemManager()->getTerrain()->GetTerrainWidth();
			tempData.LMtv = 1.0f - pGrassClusterSrc[i].vPosition[2] / m_pRenderDevice->GetWorldSystemManager()->getTerrain()->GetTerrainWidth();


			Matrix4x4 RotMatrix;
			RotMatrix.Identity();
			if( pGrassClusterSrc[i].vPackedNormal[1] < 250 )
			{
				Vector3D vTerrainNormal(tempData.vNormal[0], tempData.vNormal[1], tempData.vNormal[2]);
				vTerrainNormal.Normalize();

				float cost = tempData.vNormal[1];
				Vector3D v;
				v.Cross( Vector3D(0,1,0), vTerrainNormal );
				v.Normalize();
				float sint = std::sqrt(1-cost*cost);
				float one_sub_cost = 1 - cost;

				RotMatrix._11 = v.x * v.x * one_sub_cost + cost;
				RotMatrix._12 = v.x * v.y * one_sub_cost + v.z * sint;
				RotMatrix._13 = v.x * v.z * one_sub_cost - v.y * sint;
				RotMatrix._21 = v.x * v.y * one_sub_cost - v.z * sint;
				RotMatrix._22 = v.y * v.y * one_sub_cost + cost;
				RotMatrix._23 = v.y * v.z * one_sub_cost + v.x * sint;
				RotMatrix._31 = v.x * v.z * one_sub_cost + v.y * sint;
				RotMatrix._32 = v.y * v.z * one_sub_cost - v.x * sint;
				RotMatrix._33 = v.z * v.z * one_sub_cost + cost;
			}


			for( uint32 j=0; j<4*3; j++ )
			{
				tempData.tu = m_grassVertex[j].tu;
				tempData.tv = m_grassVertex[j].tv;

				Vector3D modelPos = Vector3D(m_grassVertex[j].x, m_grassVertex[j].y, m_grassVertex[j].z) * tempData.vNormal[3] * RotMatrix;
				modelPos += Vector3D(pGrassClusterSrc[i].vPosition[0], pGrassClusterSrc[i].vPosition[1], pGrassClusterSrc[i].vPosition[2]);

				float windAngle = m_vTimeParams.x * m_vTimeParams.y * Vector3D(pGrassClusterSrc[i].vPosition[0], pGrassClusterSrc[i].vPosition[1], pGrassClusterSrc[i].vPosition[2]).GetLength();
				Vector3D vCosSin = Vector3D( std::cos(windAngle), 0, std::sin(windAngle) );
				Vector3D vOffset(	pGrassClusterSrc[i].vWindParams[0] * m_vWindDirForce.x * m_vWindDirForce.w,
									pGrassClusterSrc[i].vWindParams[1] * m_vWindDirForce.y * m_vWindDirForce.w,
									pGrassClusterSrc[i].vWindParams[2] * m_vWindDirForce.z * m_vWindDirForce.w );

				vOffset.x += vCosSin.x * pGrassClusterSrc[i].vWindParams[0] * m_vWindDirForce.w;
				vOffset.y += vCosSin.y * pGrassClusterSrc[i].vWindParams[1] * m_vWindDirForce.w;
				vOffset.z += vCosSin.z * pGrassClusterSrc[i].vWindParams[2] * m_vWindDirForce.w;

				Vector3D vv = Vector3D(tempData.vNormal[0], tempData.vNormal[1], tempData.vNormal[2]) + vOffset;
				vv.Normalize();
				modelPos += vv * tempData.vNormal[3] * (1.0f - tempData.tv);	

				tempData.vPosition[0] = modelPos.x;
				tempData.vPosition[1] = modelPos.y;
				tempData.vPosition[2] = modelPos.z;
				tempData.vPosition[3] = pGrassClusterSrc[i].vPosition[3];

				(*pGrassVertex) = tempData;

				pGrassVertex++;
			}
		}

		m_pRenderDevice->extGlUnmapBuffer(GL_ARRAY_BUFFER);

	}
	
	m_vTextureAtlas.Set( pGrass->m_fTextureAtlasNbX, pGrass->m_fTextureAtlasNbY, pGrass->m_fTextureAtlasW, pGrass->m_fTextureAtlasH );
}