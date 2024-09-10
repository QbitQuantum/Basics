VOID Render( )
{
	RECT rt1, rt2;
	D3DXMATRIX matWorld, matScale, matRotateZ, matTrans;

	g_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB( 0, 0, 255 ), 1.0f, 0 );

	if ( SUCCEEDED( g_pD3DDevice->BeginScene( ) ) )
	{

		SetupMatrices( );
		SetRect( &rt1, 10, 10, 0, 0 );
		if (!g_Method)
		{
			g_pFont->DrawTextW( NULL, L"AABB 충돌(left click으로 방법 변경)", -1, &rt1, DT_NOCLIP, D3DXCOLOR( 1.f, 1.f, 0.f, 1.f ) );
		}
		else
		{
			g_pFont->DrawTextW( NULL, L"OBB 충돌(left click으로 방법 변경)", -1, &rt1, DT_NOCLIP, D3DXCOLOR( 1.f, 1.f, 0.f, 1.f ) );
		}
		


		g_pD3DDevice->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );


		for ( DWORD i = 0; i < sizeof( g_Box ) / sizeof( g_Box[1] ); ++i )
		{
			D3DXMatrixTranslation( &matTrans, g_Box[i].CenterPos.x, g_Box[i].CenterPos.y, g_Box[i].CenterPos.z );
			D3DXMatrixScaling( &matScale, g_Box[i].BoxScaling, g_Box[i].BoxScaling, g_Box[i].BoxScaling );
			D3DXMatrixRotationZ( &matRotateZ, g_Box[i].BoxRotateZ );
			matWorld = matRotateZ * matScale * matTrans;

			g_pD3DDevice->SetTransform( D3DTS_WORLD, &matWorld );

			g_pMesh->DrawSubset( 0 );
		}
		SetRect( &rt2, 10, 30, 0, 0 );

		if ( g_CheckFlag )
		{
			g_pFont->DrawTextW( NULL, L"박았음!!", -1, &rt2, DT_NOCLIP, D3DXCOLOR( 1.f, 1.f, 0.f, 1.f ) );
		}
		else
		{
			g_pFont->DrawTextW( NULL, L"아직 멀었음!!", -1, &rt2, DT_NOCLIP, D3DXCOLOR( 1.f, 1.f, 0.f, 1.f ) );
		}

		g_pD3DDevice->EndScene( );
	}

	g_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}