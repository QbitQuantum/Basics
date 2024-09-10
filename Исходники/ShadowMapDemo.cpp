void ShadowMapDemo::RenderScene( ShaderManager& shader_mgr )
{
//	m_pShadowMapManager->ShaderTechniqueForShadowCaster();

	GraphicsDevice().SetRenderState( RenderStateType::ALPHA_BLEND, false );
	GraphicsDevice().SetRenderState( RenderStateType::LIGHTING,    m_Lighting );

	shared_ptr<ShaderLightManager> pLightMgr = shader_mgr.GetShaderLightManager();
	if( pLightMgr )
		pLightMgr->CommitChanges();

	int num_mesh_rows = 5;
	for( int i=0; i<num_mesh_rows; i++ )
	{
		Matrix34 pose( Matrix34Identity() );
		pose.vPosition = Vector3( 0.0f, (float)i * 1.25f, (float)i * 5.0f + 2.0f );

		shader_mgr.SetWorldTransform( pose );

		shared_ptr<BasicMesh> pMesh = m_Mesh.GetMesh();
		if( pMesh )
			pMesh->Render( shader_mgr );
	}

	shader_mgr.SetWorldTransform( Matrix44Identity() );
	shared_ptr<BasicMesh> pFloor = m_FloorMesh.GetMesh();
	if( pFloor )
		pFloor->Render( shader_mgr );

//	PrimitiveShapeRenderer renderer;
//	renderer.SetShader(  );
//	renderer.RenderBox( Vector3( 100.0f, 0.1f, 100.0f ), Matrix34( Vector3(0.0f,-0.05f,0.0f), Matrix33Identity() ) );
}