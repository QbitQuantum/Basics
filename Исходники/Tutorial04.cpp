//--------------------------------------------------------------------------------------
// Render a frame
//--------------------------------------------------------------------------------------
void Render()
{
    // Update our time
    static float t = 0.0f;
    if( g_driverType == D3D_DRIVER_TYPE_REFERENCE )
    {
        t += ( float )XM_PI * 0.0125f;
    }
    else
    {
        static DWORD dwTimeStart = 0;
        DWORD dwTimeCur = GetTickCount();
        if( dwTimeStart == 0 )
            dwTimeStart = dwTimeCur;
        t = ( dwTimeCur - dwTimeStart ) / 1000.0f;
    }

    //
    // Apply transforms to the meshes
    //
	g_meshesTransforms[0] = XMMatrixRotationY( t );
	g_meshesTransforms[1] = XMMatrixTranslation(
				  0.3f*t,
				  0.05f*t,
				  0.05f*t
				);

    //
    // Clear the back buffer
    //
    float ClearColor[4] = { 0.0f, 0.125f, 0.3f, 1.0f }; // red,green,blue,alpha
    g_pImmediateContext->ClearRenderTargetView( g_pRenderTargetView, ClearColor );

	//
    // Clear the depth buffer to 1.0 (max depth)
    //
    g_pImmediateContext->ClearDepthStencilView( g_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0 );

	int meshesNumber = 2;
	int meshesVertex[2][2] = {{36,0},{36,36}};
	for (int i=meshesNumber-1; i>=0; i--)
	{
		//
		// Update variables
		//
		ConstantBuffer cb;
		cb.mWorld = XMMatrixTranspose( g_meshesTransforms[i] );
		cb.mView = XMMatrixTranspose( g_View );
		cb.mProjection = XMMatrixTranspose( g_Projection );
		g_pImmediateContext->UpdateSubresource( g_pConstantBuffer, 0, NULL, &cb, 0, 0 );

		//
		// Renders a triangle
		//
		g_pImmediateContext->VSSetShader( g_pVertexShader, NULL, 0 );
		g_pImmediateContext->VSSetConstantBuffers( 0, 1, &g_pConstantBuffer );
		g_pImmediateContext->PSSetShader( g_pPixelShader, NULL, 0 );
		g_pImmediateContext->DrawIndexed( meshesVertex[i][0], meshesVertex[i][1], 0 );        // 36 vertices needed for 12 triangles in a triangle list
	}
    //
    // Present our back buffer to our front buffer
    //
    g_pSwapChain->Present( 0, 0 );
}