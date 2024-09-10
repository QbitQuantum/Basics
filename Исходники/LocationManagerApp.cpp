void LocationApp::draw()
{
    // Clear the screen
    gl::enableDepthRead();
    gl::enableDepthWrite();
    gl::clear( Color::gray( 0.843f ) );

    CameraPersp camera;
    camera.setPerspective( 60.0f, getWindowAspectRatio(), 0.01f, 10.0f );
    camera.lookAt( Vec3f( 0.0f, 0.0f, 3.0f ), Vec3f::zero() );
    gl::setMatrices( camera );
    mLight->update( camera );

    // Rotate the globe
    gl::multModelView( Quatf(Vec3f::yAxis(), mRotationAngle ).normalized() );

    // Draw the globe with shading. Rotate it 90 degrees on
    // its Y axis to line up the texture with the location
    gl::color( ColorAf::white() );
    gl::enable( GL_LIGHTING );
    mTexture.bind( 0 );
    gl::pushMatrices();
    gl::rotate( Vec3f( 0.0f, 90.0f, 0.0f ) );
    gl::drawSphere( Vec3f::zero(), 1.0f, 32 );
    gl::popMatrices();
    mTexture.unbind();
    gl::disable( GL_LIGHTING );

    // Draw location
    gl::color( ColorAf( 1.0f, 0.2f, 0.18f, 0.667f ) );
    gl::drawSphere( mLocation, mDotRadius, 32 );

    ////////////////////////////////////////////////////
#if defined( CINDER_COCOA_TOUCH )
    gl::setMatricesWindow( getWindowSize() );
    gl::enableDepthRead( false );
    gl::enableDepthWrite( false );

    // Plot arrow position
    float radius = 256.0f;
    float rotation = toRadians( mHeading ) - (float)M_PI * 0.5f;
    float x = math<float>::cos( rotation );
    float y = math<float>::sin( rotation );
    Vec2f position = getWindowCenter() + Vec2f( x, y ) * radius;

    gl::translate( position );
    gl::rotate( Vec3f( 0.0f, 0.0f, -mHeading ) );
    gl::translate( position * -1.0f );
    gl::translate( position );

    gl::color( Colorf( 0, 0, 1 ) );
    gl::drawSolid( mArrow );
#endif
}