void CBE_Skybox::Draw(CCopyEntity* pCopyEnt)
{
	BasicMesh* pMeshObject = m_MeshProperty.m_MeshObjectHandle.GetMesh().get();
	if( !pMeshObject )
	{
		ONCE( LOG_PRINT_WARNING( " An invlid mesh object: base entity '%s'", m_strName.c_str() ) );
		return;
	}

	// set the world transform
	Matrix44 world( Matrix44Scaling( 10.0f, 10.0f, 10.0f ) );

	Vector3 vPos;
	Camera* pCamera = m_pStage->GetCurrentCamera();
	if( pCamera )
		vPos = pCamera->GetPosition();
	else
		vPos = Vector3(0,0,0);

	world(0,3) = vPos.x;
	world(1,3) = vPos.y;
	world(2,3) = vPos.z;
	world(3,3) = 1;

	FixedFunctionPipelineManager().SetWorldTransform( world );


	pMeshObject->SetVertexDeclaration();

	int num_materials = pMeshObject->GetNumMaterials();

	bool shift_camera_height = true;

//	ShaderParameter<float> cam_height_param( "g_CameraHeight" );

	// Disable depth-test and writing to depth buffer.
	// These 2 settings and restored after rendering skybox because they are changed only when necessary.
	// This is not required if you are using HLSL effect of Direct3D, and the technique to render
	// the skybox defines the same render states.
	// If you are using OpenGL, you have to do this whether you are using GLSL or not?
	GraphicsDevice().Disable( RenderStateType::DEPTH_TEST );
	GraphicsDevice().Disable( RenderStateType::WRITING_INTO_DEPTH_BUFFER );

	GraphicsDevice().Disable( RenderStateType::LIGHTING );

	// save the original texture and temporarily overwrite it with the sky texture
	TextureHandle orig_tex;
	if( 0 < num_materials )
	{
		if( pMeshObject->Material(0).Texture.empty() )
			pMeshObject->Material(0).Texture.resize( 1 );

		orig_tex = pMeshObject->Material(0).Texture[0];
		pMeshObject->Material(0).Texture[0] = m_SkyboxTexture;
	}

	ShaderManager *pShaderManager = m_MeshProperty.m_ShaderHandle.GetShaderManager();
	if( pShaderManager )
//	 && pShaderManager->IsValid() ) // check if pEffect is present?
	{
		if( shift_camera_height )
		{
			Camera *pCam = m_pStage->GetCurrentCamera();
			float fCamHeight;
			if( pCam )
				fCamHeight = pCam->GetPosition().y;
			else
				fCamHeight = 5.0f;

			pShaderManager->GetEffect()->SetFloat( "g_CameraHeight", fCamHeight );
//			pShaderManager->SetParam( "g_CameraHeight", fCamHeight );

//			pEffect->SetFloat( "g_TexVShiftFactor", 0.000005f );
//			pShaderManager->SetParam( "g_TexVShiftFactor", 0.000005f );

//			cam_height_param.Parameter() = fCamHeight;
//			pShaderManager->SetParam( cam_height_param );
		}

		// render the skybox mesh with an HLSL shader

		pShaderManager->SetWorldTransform( world );

		Result::Name res = pShaderManager->SetTechnique( m_MeshProperty.m_ShaderTechnique(0,0) );

		// Meshes are divided into subsets by materials. Render each subset in a loop
		pMeshObject->Render( *pShaderManager );
	}
	else
	{
//		RenderAsSkybox( m_MeshProperty.m_MeshObjectHandle, vPos );
		pMeshObject->Render();
	}

	if( 0 < num_materials
	 && 0 < pMeshObject->Material(0).Texture.size() )
	{
		// restore the original texture
		pMeshObject->Material(0).Texture[0] = orig_tex;
	}

	GraphicsDevice().Enable( RenderStateType::DEPTH_TEST );
	GraphicsDevice().Enable( RenderStateType::WRITING_INTO_DEPTH_BUFFER );
}