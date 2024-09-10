void OGL2_Renderer::FreeImage( unsigned int index )
{
	if( CRenderer::currentTexture == index && index != 0 )
		BindImage( 0 );
	glDeleteTextures( 1, &index );
}