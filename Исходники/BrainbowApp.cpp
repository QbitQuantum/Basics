void BrainbowApp::setup()
{
    // LOAD AUDIO
    mAudio = AudioCont();
    mAudio.setUp();
    
    // START SCENE 1
    sceneOne = true;
    sceneTwo = false;
    
    // Set up OpenGL
    
	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
    
    gongTimer.start();
    ballTimer.start();
    
    // LIGHTING
    //here
    glPolygonOffset( 1.0f, 1.0f );
	glEnable( GL_LIGHTING );
	glEnable( GL_DEPTH_TEST );
    
    
    mLight = new gl::Light( gl::Light::POINT, 0 );
	mLight->lookAt( Vec3f( 1, 5, 1 ), Vec3f (getWindowWidth(), getWindowHeight() * 0.5f, 0.0f ));
    mLight->setAmbient( Color( 0.3f, 0.3f, 0.3f ) );
	mLight->setDiffuse( Color( 1.0f, 1.0f, 1.0f ) );
	mLight->setSpecular( Color( 1.0f, 1.0f, 1.0f ) );
	mLight->setShadowParams( 60.0f, 0.5f, 8.0f );
    //	mLight->update( *mCamera );
	mLight->enable();
    
    
    //LOAD SHAPES
    colorSat = 1.0f;
    
	sphereMaterial.setSpecular( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	sphereMaterial.setDiffuse( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	sphereMaterial.setAmbient( ColorA(colorSat-0.3f, colorSat, colorSat, .05f ) );
	sphereMaterial.setShininess( 1.0f );
    
    sphereMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    gl::Material cylMaterial;
    cylMaterial.setSpecular( ColorA(0, 1.0f, 1.0f, .2f ));
	cylMaterial.setDiffuse( ColorA(0, 1.0f, 1.0f, .2f ) );
	cylMaterial.setAmbient( ColorA(0, 1.0f, 1.0f, .2f ) );
	cylMaterial.setShininess( 600.0f );
    cylMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    gl::Material curMaterial;
    curMaterial.setSpecular( ColorA(1, .5, 0, .5f ));
	curMaterial.setDiffuse( ColorA(1, .5, 0, .5f ) );
	curMaterial.setAmbient( ColorA(1, 1.0f, 1.0f, .05f ) );
	curMaterial.setShininess( 600.0f );
    curMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    
	discMaterial.setSpecular( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	discMaterial.setDiffuse( ColorA(colorSat-0.3f, colorSat, colorSat, .4f ) );
	discMaterial.setAmbient( ColorA(colorSat-0.3f, colorSat, colorSat, .05f ) );
	discMaterial.setShininess( 600.0f );
    discMaterial.setEmission(ColorA(1, 1, 1, 1 ));
    
    initShadowMap();
    
    mCloud = SphereCloud(0, 70);
    
    mDiamond = gl::DisplayList( GL_COMPILE );
    mDiamond.newList();
    gl::drawSphere(Vec3f(0, 0, 0), 300, 4);
    mDiamond.endList();
    mDiamond.setMaterial( sphereMaterial );
    
    mCyl = gl::DisplayList( GL_COMPILE );
    mCyl.newList();
    //    gl::drawCylinder(200, 200, 200);
    gl::drawColorCube(Vec3f(0, 0, 0), Vec3f(300, 300, 300));
    mCyl.endList();
    mCyl.setMaterial(cylMaterial);
    
    mCur = gl::DisplayList( GL_COMPILE );
    mCur.newList();
    gl::drawSphere(Vec3f(0, 0, 0), 5);
    mCur.endList();
    mCur.setMaterial(curMaterial);
    
    mDisc = gl::DisplayList( GL_COMPILE );
    mDisc.newList();
    gl::drawSolidCircle(Vec2f(0, 0), 60, 6);
    mDisc.endList();
    mDisc.setMaterial( discMaterial );
	
	// START LEAP
	mLeap 		= LeapSdk::Device::create();
	mCallbackId = mLeap->addCallback( &BrainbowApp::onFrame, this );
    
    
    mShader = gl::GlslProg( loadResource( RES_SHADOWMAP_VERT ), loadResource( RES_SHADOWMAP_FRAG ) );
	mShader.bind();
	mShader.uniform( "depthTexture", 0 );
}