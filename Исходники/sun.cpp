void Sun::_renderCorona( ObjectRenderInst *ri, SceneState *state, BaseMatInstance *overrideMat )
{   
   Point3F sunlightPosition = state->getCameraPosition() - mLight->getDirection() * state->getFarPlane() * 0.9f;

   // Calculate Billboard Radius (in world units) to be constant, independent of distance.
   // Takes into account distance, viewport size, and specified size in editor
   F32 BBRadius = (((sunlightPosition - state->getCameraPosition()).len()) / (GFX->getViewport().extent.x / 640.0)) / 2;  
   BBRadius *= mCoronaScale;

   GFXTransformSaver saver;

   if ( state->isReflectPass() )
      GFX->setProjectionMatrix( gClientSceneGraph->getNonClipProjection() );

   GFX->setStateBlock(mCoronaSB);

   // Initialize points with basic info
   Point3F points[4];
   points[0] = Point3F(-BBRadius, 0.0, -BBRadius);
   points[1] = Point3F( BBRadius, 0.0, -BBRadius);
   points[2] = Point3F( BBRadius, 0.0,  BBRadius);
   points[3] = Point3F(-BBRadius, 0.0,  BBRadius);

   // Get info we need to adjust points
   MatrixF camView = GFX->getWorldMatrix();
   camView.inverse();

   // Finalize points
   for(int i = 0; i < 4; i++)
   {
      // align with camera
      camView.mulV(points[i]);
      // offset
      points[i] += sunlightPosition;
   }

   // Draw it
   
   if ( mCoronaUseLightColor )
      PrimBuild::color(mLightColor);
   else
      PrimBuild::color(mCoronaTint);
   
   GFX->setTexture(0, mCoronaTexture);

   PrimBuild::begin( GFXTriangleFan, 4 );
   PrimBuild::texCoord2f(0, 0);
   PrimBuild::vertex3fv(points[0]);
   PrimBuild::texCoord2f(1, 0);
   PrimBuild::vertex3fv(points[1]);
   PrimBuild::texCoord2f(1, 1);
   PrimBuild::vertex3fv(points[2]);
   PrimBuild::texCoord2f(0, 1);
   PrimBuild::vertex3fv(points[3]);
   PrimBuild::end();
}