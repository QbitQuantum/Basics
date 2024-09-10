void SuperSolarSystemApp::DrawIceCube( )
{
	float blendFactor[] ={ 0.0f, 0.0f, 0.0f, 0.0f };
	ID3DX11EffectTechnique *activeTech;
	D3DX11_TECHNIQUE_DESC techDesc;

	//
	// 画冰立方, 仅将其渲染到模板缓冲
	//

	mD3dImmediateContext->IASetInputLayout( InputLayouts::NormalObjLayout );
	mD3dImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	activeTech = Effects::NormalObjFX->NormalObjTech;
	activeTech->GetDesc( &techDesc );

	UINT stride = sizeof( Vertex::NormalObjVertex );
	UINT offset = 0;
	mD3dImmediateContext->IASetVertexBuffers( 0, 1, &mLightTexVB, &stride, &offset );
	mD3dImmediateContext->IASetIndexBuffer( mLightTexIB, DXGI_FORMAT_R32_UINT, 0 );

	for ( UINT p = 0; p < techDesc.Passes; p++ )
	{
		XMMATRIX world             = XMLoadFloat4x4( &mWorld[ICECUBE] );
		XMMATRIX worldViewProj     = XMMatrixMultiply( world, mCamera.GetViewProj( ) );
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose( world );

		// 设置effect中的常量缓冲
		Effects::NormalObjFX->SetWorldViewProj( worldViewProj );
		Effects::NormalObjFX->SetWorld( world );
		Effects::NormalObjFX->SetWorldInvTranspose( worldInvTranspose );
		Effects::NormalObjFX->SetTexTransform( XMLoadFloat4x4( &mTexTransform[ICECUBE] ) );

		// 设置纹理和材质
		Effects::NormalObjFX->SetDiffuseMap( mDiffuseMapSRV[ICECUBE] );
		Effects::NormalObjFX->SetMaterial( mMat[ICECUBE] );

		// 禁止对缓冲目标写操作
		mD3dImmediateContext->OMSetBlendState( RenderStates::NoRenderTargetWritesBS,
			blendFactor, 0xffffffff );

		// 将镜子的可见像素渲染到模板缓冲
		// 但是不能将镜子的深度信息写到深度缓存, 否则将阻塞镜像

		// 这里将镜子可见像素的 stencil value 设置为1, 当做标记了镜子像素
		mD3dImmediateContext->OMSetDepthStencilState( RenderStates::MirrorDSS, 1 );

		activeTech->GetPassByIndex( p )->Apply( 0, mD3dImmediateContext );
		mD3dImmediateContext->DrawIndexed(
			mLTIndexCount[LTVT_ICECUBE],
			mLTIndexOffset[LTVT_ICECUBE],
			mLTVertexOffset[LTVT_ICECUBE]
			);

		//
		// 恢复措施
		//

		mD3dImmediateContext->OMSetDepthStencilState( 0, 0 );
		mD3dImmediateContext->OMSetBlendState( 0, blendFactor, 0xffffffff );
	}

	//
	// 画天体的镜像
	//

	stride = sizeof( Vertex::NormalObjVertex );
	offset = 0;
	mD3dImmediateContext->IASetVertexBuffers( 0, 1, &mLightTexVB, &stride, &offset );
	mD3dImmediateContext->IASetIndexBuffer( mLightTexIB, DXGI_FORMAT_R32_UINT, 0 );

	activeTech = Effects::NormalObjFX->NormalObjTech;
	activeTech->GetDesc( &techDesc );

	for ( UINT p = 0; p < techDesc.Passes; ++p )
	{
		// 对每一个冰面镜面确定成像内容
		for ( int planeID = 0; planeID < 6; planeID++ )
		{
			// 未经过世界坐标变换的镜面
			XMVECTOR mirrorPlane = XMVectorSet(
				mIceCubeNormals[planeID].x,
				mIceCubeNormals[planeID].y,
				mIceCubeNormals[planeID].z,
				1.0f
				);

			// 将平面依据世界矩阵做变换
			mirrorPlane = XMPlaneNormalize( mirrorPlane );
			mirrorPlane = XMPlaneTransform( mirrorPlane, MathHelper::InverseTranspose( XMLoadFloat4x4( &mWorld[ICECUBE] ) ) );

			XMMATRIX R = XMMatrixReflect( mirrorPlane );

			for ( int starID = SUN; starID < STARNUMBER; starID++ )
			{
				if ( ICECUBE == starID )
				{
					continue;
				}

				XMVECTOR target = XMVectorSet( mWorld[starID]._41, mWorld[starID]._42, mWorld[starID]._43, 1.0f );

				// 在镜子后面的物体不做镜像
				if ( MathHelper::PointPlanePosRelation( target, mirrorPlane ) == MathHelper::BEHIND_THE_PLANE )
				{
					continue;
				}

				// 设置转换矩阵
				XMMATRIX world             = XMLoadFloat4x4( &mWorld[starID] ) * R;
				XMMATRIX worldViewProj     = XMMatrixMultiply( world, mCamera.GetViewProj( ) );
				XMMATRIX worldInvTranspose = MathHelper::InverseTranspose( world );

				// 设置effect中的常量缓冲
				Effects::NormalObjFX->SetWorldViewProj( worldViewProj );
				Effects::NormalObjFX->SetWorld( world );
				Effects::NormalObjFX->SetWorldInvTranspose( worldInvTranspose );
				Effects::NormalObjFX->SetTexTransform( XMLoadFloat4x4( &mTexTransform[starID] ) );

				// 设置纹理和材质
				Effects::NormalObjFX->SetDiffuseMap( mDiffuseMapSRV[starID] );
				Effects::NormalObjFX->SetMaterial( mMat[starID] );

				// 设置RenderStates
				if ( WIREFENCE == starID )
				{
					mD3dImmediateContext->RSSetState( RenderStates::NoCullRS );
				}

				// 处理镜面反射的光线方向, 待解决

				// 改变正面的判定方式
				mD3dImmediateContext->RSSetState( RenderStates::CullClockwiseRS );

				// 只在模板缓冲中标记为可见的镜面像素中写入镜像信息
				mD3dImmediateContext->OMSetDepthStencilState( RenderStates::DrawReflectionDSS, 1 );

				activeTech->GetPassByIndex( p )->Apply( 0, mD3dImmediateContext );
				mD3dImmediateContext->DrawIndexed(
					mLTIndexCount[LTVT_STAR],
					mLTIndexOffset[LTVT_STAR],
					mLTVertexOffset[LTVT_STAR]
					);

				//
				// 恢复措施
				//

				mD3dImmediateContext->RSSetState( 0 );
				mD3dImmediateContext->OMSetDepthStencilState( 0, 0 );
			}
		}
	}

	//
	// 最后将冰立方渲染至背面缓存, 但是要经过 blending 透明化处理
	//

	mD3dImmediateContext->IASetInputLayout( InputLayouts::NormalObjLayout );
	mD3dImmediateContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	activeTech = Effects::NormalObjFX->NormalObjTech;
	activeTech->GetDesc( &techDesc );

	stride = sizeof( Vertex::NormalObjVertex );
	offset = 0;
	mD3dImmediateContext->IASetVertexBuffers( 0, 1, &mLightTexVB, &stride, &offset );
	mD3dImmediateContext->IASetIndexBuffer( mLightTexIB, DXGI_FORMAT_R32_UINT, 0 );

	for ( UINT p = 0; p < techDesc.Passes; p++ )
	{
		XMMATRIX world            = XMLoadFloat4x4( &mWorld[ICECUBE] );
		XMMATRIX worldViewProj    = XMMatrixMultiply( world, mCamera.GetViewProj( ) );
		XMMATRIX worldInvTranspose = MathHelper::InverseTranspose( world );

		// 设置effect中的常量缓冲
		Effects::NormalObjFX->SetWorldViewProj( worldViewProj );
		Effects::NormalObjFX->SetWorld( world );
		Effects::NormalObjFX->SetWorldInvTranspose( worldInvTranspose );
		Effects::NormalObjFX->SetTexTransform( XMLoadFloat4x4( &mTexTransform[ICECUBE] ) );

		// 设置纹理和材质
		Effects::NormalObjFX->SetDiffuseMap( mDiffuseMapSRV[ICECUBE] );
		Effects::NormalObjFX->SetMaterial( mMat[ICECUBE] );

		mD3dImmediateContext->OMSetBlendState( RenderStates::TransparentBS, blendFactor, 0xffffffff );

		activeTech->GetPassByIndex( p )->Apply( 0, mD3dImmediateContext );
		mD3dImmediateContext->DrawIndexed(
			mLTIndexCount[LTVT_ICECUBE],
			mLTIndexOffset[LTVT_ICECUBE],
			mLTVertexOffset[LTVT_ICECUBE]
			);

		//恢复设置
		mD3dImmediateContext->OMSetDepthStencilState( 0, 0 );
		mD3dImmediateContext->OMSetBlendState( 0, blendFactor, 0xffffffff );
	}
}