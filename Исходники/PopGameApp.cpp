void PopGameApp::setup()
{
    
   
    
    speed2 =3.5;
    setWindowSize(1920,1080);
    //setWindowSize(1080/2,1920/2);
    setWindowPos(0, 0);
	mCamera = new CameraPersp( getWindowWidth(), getWindowHeight(), 45.0f );
	mCamera->lookAt( Vec3f( 0, -300, -400 ), Vec3f( 0, 0, 50 ) );
	mCamera->setPerspective( 80.0f, getWindowAspectRatio(),200.0f, 4000.0f );

    
    mLight = new gl::Light( gl::Light::POINT, 0 );
  
	mLight->lookAt( Vec3f(1000,-1000, -2000 ), Vec3f( 0, 1000, 0 ) );
    mLight->setShadowParams(60.0f,2000.f, 3500.0f );
	mLight->update( *mCamera );
	mLight->enable();
    

    
  
    mShader = gl::GlslProg( loadAsset("shadowMap_vert.glsl"),loadAsset("shadowMap_frag.glsl") );
    
	mShader.bind();
	mShader.uniform( "depthTexture", 1 );
    mShader.uniform( "difTexture", 0 );
    mShader.unbind();
    
     initShadowMap();
    
   
   
    groundHolder.setup();
    stage.addChild(&groundHolder);
    
    enemyHandler.setup();
    stage.addChild(&enemyHandler);
    BulletHandler::getInstance()->enemyHandler =&enemyHandler;
   
    
    
    
    plane =new Hero();
    plane->load("plane.png","planeh.png");
    plane->setAlign(neuro::ALIGN_CENTER);
    
    plane->z = 0;
   
   
    
 
    
     stage.addChild(plane);
    prevTime = cinder::app::getElapsedSeconds();
    
    BulletHandler::getInstance()->stage =&stage;
    
    
    logo =new Image();
    logo->load("logo.png");
  // logo->rotationX =-3.1415;
    logo->setAlign(neuro::ALIGN_BOTTOM_LEFT);
    logo->x =0;
    logo->y =1080*2;
    //logo->scaleX =logo->scaleY =logo->scaleZ =4;
    stage2D.scaleX=stage2D.scaleY =0.5;
    stage2D.addChild(logo);
    
}