void ObjLoaderApp::setup()
{
	ObjLoader loader( loadResource( RES_CUBE_OBJ )->createStream() );
	loader.load( &mMesh );
	mVBO = gl::VboMesh( mMesh );
	
	mTexture = gl::Texture( loadImage( loadResource( RES_IMAGE ) ) );
	mShader = gl::GlslProg( loadResource( RES_SHADER_VERT ), loadResource( RES_SHADER_FRAG ) );

	CameraPersp initialCam;
	initialCam.setPerspective( 45.0f, getWindowAspectRatio(), 0.1, 10000 );
	mMayaCam.setCurrentCam( initialCam );

	mTexture.bind();
	mShader.bind();
	mShader.uniform( "tex0", 0 );
}