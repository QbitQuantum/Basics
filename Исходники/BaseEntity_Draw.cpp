void BaseEntity::RenderAsShadowReceiver(CCopyEntity* pCopyEnt)
{
	ONCE( LOG_PRINT_ERROR( " Not implemented yet." ) );

	PROFILE_FUNCTION();

	// set option to disable texture settings

	ShadowMapManager *pShadowMgr = m_pStage->GetEntitySet()->GetRenderManager()->GetShadowManager();
	if( !pShadowMgr )
		return;

	shared_ptr<BasicMesh> pMesh = pCopyEnt->m_MeshHandle.GetMesh();
	if( !pMesh )
		return;

	ShaderHandle shader = pShadowMgr->GetShader();
	ShaderManager *pShaderMgr = shader.GetShaderManager();
	if( !pShaderMgr )
		return;

	pShaderMgr->SetWorldTransform( pCopyEnt->GetWorldPose() );

	ShaderTechniqueHandle tech;
	const U32 entity_flags = pCopyEnt->GetEntityFlags();
	if( entity_flags & BETYPE_SHADOW_RECEIVER )
		tech = pShadowMgr->ShaderTechniqueForShadowReceiver( VertexBlendType::NONE );
	else // i.e. entity_flags & BETYPE_SHADOW_CASTER. See EntityNode::RenderShadowReceivers() for details.
		tech = pShadowMgr->ShaderTechniqueForNonShadowedCasters( VertexBlendType::NONE );

	pShaderMgr->SetTechnique( tech );

	pMesh->Render( *pShaderMgr );

/*	shared_ptr<MeshContainerRenderMethod> pMeshRenderMethod;
	const bool is_skeletal_mesh = (pMesh->GetMeshType() == MeshType::SKELETAL);
	if( is_skeletal_mesh )
	{
		pMeshRenderMethod = this->m_MeshProperty.m_pSkeletalShadowReceiverRenderMethod;

		shared_ptr<SkeletalMesh> pSkeletalMesh
			= dynamic_pointer_cast<SkeletalMesh,BasicMesh>(pMesh);

//		if( !this->m_MeshProperty.m_pBlendTransformsLoader )
//			InitShadowCasterReceiverSettings( pSkeletalMesh, this->m_MeshProperty );

		this->m_MeshProperty.m_pBlendTransformsLoader->SetSkeletalMesh( pSkeletalMesh );

//		pSkeletalMesh->SetLocalTransformToCache( 0, Matrix34Identity() );
//		pSkeletalMesh->SetLocalTransformsFromCache();
	}
	else
		pMeshRenderMethod = this->m_MeshProperty.m_pShadowReceiverRenderMethod;

	if( true )//render_all_subsets )
	{
//		pMeshRenderMethod->MeshRenderMethod().resize( 1 );
		SubsetRenderMethod& mesh_render_method = pMeshRenderMethod->MeshRenderMethod()[0];
		mesh_render_method.m_Shader    = pShadowMgr->GetShader();
//		const char *tech = is_skeletal_mesh ? "SceneShadowMap_VertexBlend" : "SceneShadowMap";
//		mesh_render_method.m_Technique.SetTechniqueName( tech );
		VertexBlendType::Name blend_type = is_skeletal_mesh ? VertexBlendType::QUATERNION_AND_VECTOR3 : VertexBlendType::NONE;
		mesh_render_method.m_Technique = pShadowMgr->ShaderTechniqueForShadowReceiver( blend_type );
//		render_method.SetMeshRenderMethod( mesh_render_method, 0 );
		pMeshRenderMethod->RenderMesh( pCopyEnt->m_MeshHandle, pCopyEnt->GetWorldPose() );
	}
	else
	{
		// how to render the mesh if each subset is rendered by different render methods
	}
*/
}