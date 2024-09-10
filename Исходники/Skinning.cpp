void Skinning::setup() {
	
	mShaderPhong = gl::GlslProg(	loadResource( RES_PHONG_VERT_GLSL ),	loadResource( RES_PHONG_FRAG_GLSL ) );
			
	// Set params
	mParams = params::InterfaceGl( "Parameters", Vec2i( 200, 400 ) );
	mParams.addParam( "Scene Rotation", &gConfigScene.orientation );
	
	gConfigScene.eye = Vec3f(0,0,10);
	
	mParams.addParam( "Bone Rotation", &mTestBoneRot );
	mParams.addParam( "BoneID", &mBoneID);
	mParams.addParam( "Zoom ", &gConfigScene.eye.z, "min=5.0 max=100.0 step=1.0");
	mParams.addParam( "Scale ", &gConfigScene.scale, "min=0.001 max=10.0 step=0.001");
	
	gConfigScene.scale = 0.04;
	
	mShowParams = false;
	mBoneID = mPrevBoneID = -1;
	mDrawFilled = true;
	mDrawNormals = false;
	// OpenGL Constants
	
	gl::enableDepthRead();
	gl::enableDepthWrite();
	
	glEnable(GL_TEXTURE_2D);
	
	cout << getAppPath() + "/../skinning_config.xml" << endl;
	
	XmlTree doc( loadFile(getAppPath() + "/../skinning_config.xml"));
	string fbxpath = doc.getChild("/skinning/fbx").getValue();
		
	pDrawable = mFBXLoader.load(getAppPath() + "/../" + fbxpath.c_str());
	
}