// - Set the world transform 'world_transform' to shader
// - Update shader params
// - Set technique
void MeshContainerRenderMethod::RenderMesh( BasicMesh &mesh, const Matrix34& world_transform )
{
	if( !m_RenderMethodsAndSubsetIndices.empty() )
	{
		if( m_RenderMethodsAndSubsetIndices.size() == 1
		 && m_RenderMethodsAndSubsetIndices[0].second.empty() )
		{
			// render all the subsets at once
			RenderMeshOrMeshSubsets( mesh, m_RenderMethodsAndSubsetIndices[0].second, m_RenderMethodsAndSubsetIndices[0].first, world_transform );
		}
		else
		{
			for( int i=0; i<(int)m_RenderMethodsAndSubsetIndices.size(); i++ )
			{
				SubsetRenderMethod& render_method = m_RenderMethodsAndSubsetIndices[i].first;
				const vector<int>& subset_indices  = m_RenderMethodsAndSubsetIndices[i].second;

				for( int j=0; j<(int)subset_indices.size(); j++ )
				{
					RenderMeshOrMeshSubsets( mesh, subset_indices, render_method, world_transform );
				}
			}
		}
	}
	else if( 0 < m_vecSubsetNameToRenderMethod.size() )
	{
		// render subsets one by one

		// set different shaders / techniques for each subset
		const int num_subsets = mesh.GetNumMaterials();
		std::vector<int> *pvecIndicesOfSubsetsToRender = NULL;
		if( m_vecIndicesOfSubsetsToRender.size() == 0 )
		{
			// render all the subsets
			// - create the full indices list
			// - For the same mesh, this is done only once.
			for( int j=(int)m_vecFullIndicesOfSubsets.size(); j<num_subsets; j++ )
				m_vecFullIndicesOfSubsets.push_back( j );
			pvecIndicesOfSubsetsToRender = &m_vecFullIndicesOfSubsets;
		}
		else
		{
			pvecIndicesOfSubsetsToRender = &m_vecIndicesOfSubsetsToRender;
		}

		int lod_index = 0;
//		for( i=0; i<num_subsets; i++ )
		for( size_t i=0; i<pvecIndicesOfSubsetsToRender->size(); i++ )
		{
			int index = (*pvecIndicesOfSubsetsToRender)[i];

			map< string, SubsetRenderMethod >::iterator itr
				= m_vecSubsetNameToRenderMethod[lod_index].find( mesh.GetMaterial(index).Name );

			if( itr == m_vecSubsetNameToRenderMethod[lod_index].end() )
				continue;

			SubsetRenderMethod& subset_render_method = (*itr).second;

			ShaderManager *pShaderMgr = subset_render_method.m_Shader.GetShaderManager();
			if( !pShaderMgr )
				continue;

			pShaderMgr->SetWorldTransform( world_transform );

			pShaderMgr->SetTechnique( subset_render_method.m_Technique );

			for( size_t j=0; j<subset_render_method.m_vecpShaderParamsLoader.size(); j++ )
			{
				subset_render_method.m_vecpShaderParamsLoader[j]->UpdateShaderParams( *pShaderMgr );
			}

			mesh.RenderSubset( *pShaderMgr, index );

			for( size_t j=0; j<subset_render_method.m_vecpShaderParamsLoader.size(); j++ )
			{
				subset_render_method.m_vecpShaderParamsLoader[j]->ResetShaderParams( *pShaderMgr );
			}
		}
	}
}