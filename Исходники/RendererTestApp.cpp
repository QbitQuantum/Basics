void RendererTestApp::setup()
{
  mRenderFunctions = {
    { "Batch 2d", [=](){ mRenderer2dStrip.update(); mRenderer2dStrip.render(); } },
    { "VBO 2d", [=](){ mRenderer2dStripVbo.update(); mRenderer2dStripVbo.render(); } },
    { "Simple", [=](){ mSimpleRenderer.render(); } },
    { "Batch 2d (no updates)", [=](){ mRenderer2dStrip.render(); } },
    { "VBO 2d (no updates)", [=](){ mRenderer2dStripVbo.render(); } },
  };
  mRenderFn = mRenderFunctions.begin();
  gl::enableVerticalSync();

  Rand r;
  for( auto &box : mBoxes )
  {
    box.setColor( ColorA{ CM_HSV, r.nextFloat( 1.0f ), 0.9f, 0.9f, 1.0f } );
    box.setPos( Vec2f{ r.nextFloat(getWindowWidth()), r.nextFloat(getWindowHeight()) } );
    box.setRotation( r.nextFloat( M_PI * 2 ) );
    mRenderer2dStrip.add( &box );
    mSimpleRenderer.add( &box );
    mRenderer2dStripVbo.add( &box );
  }

  // We perform the cast since we know what type of things we stored in each renderer
  // A type-safe way could be to assign y to each objects layer and then sort by layer
  Vec2f center = getWindowCenter();
  auto vortex_simple = [center]( const SimpleRenderer::Renderable *lhs, const SimpleRenderer::Renderable *rhs )
  {
    return static_cast<const Box*>( lhs )->getPos().distance(center) <
    static_cast<const Box*>( rhs )->getPos().distance(center);
  };
  auto vortex_triangle = [center]( const BatchRenderer2d::Renderable *lhs, const BatchRenderer2d::Renderable *rhs )
  {
    return  static_cast<const Box*>( lhs )->getPos().distance(center) <
    static_cast<const Box*>( rhs )->getPos().distance(center);
  };
  mSimpleRenderer.sort( vortex_simple );
  mRenderer2dStrip.sort( vortex_triangle );
  mRenderer2dStripVbo.sort( vortex_triangle );

  getWindow()->getSignalKeyUp().connect( [this](KeyEvent &event){ if( event.getCode() == KeyEvent::KEY_SPACE ){ swapRenderer(); } } );
  getWindow()->getSignalTouchesEnded().connect( [this](TouchEvent &event){ swapRenderer(); } );
}