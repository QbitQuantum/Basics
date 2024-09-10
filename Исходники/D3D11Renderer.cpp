void D3D11Renderer::BuildProjectionMatrices( const DisplaySettings& ds )
{
	*_perspec_mx = XMMatrixPerspectiveFovLH(
		0.25f * XM_PI,
		static_cast< float >( ds._width ) / static_cast< float >( ds._height ),
		0.1f,
		100.0f );

	*_ortho_mx = XMMatrixOrthographicLH(
		static_cast< float >( ds._width ) / 16.0f,
		static_cast< float >( ds._height ) / 16.0f,
		1.0f,
		100.0f );
}