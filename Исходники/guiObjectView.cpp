void GuiObjectView::renderWorld( const RectI& updateRect )
{
   if( !mModel )
      return;
      
   GFXTransformSaver _saveTransforms;

   // Determine the camera position, and store off render state.
   
   MatrixF modelview;
   MatrixF mv;
   Point3F cp;

   modelview = GFX->getWorldMatrix();

   mv = modelview;
   mv.inverse();
   mv.getColumn( 3, &cp );

   RenderPassManager* renderPass = gClientSceneGraph->getDefaultRenderPass();

   S32 time = Platform::getVirtualMilliseconds();
   S32 dt = time - mLastRenderTime;
   mLastRenderTime = time;

   LIGHTMGR->unregisterAllLights();
   LIGHTMGR->setSpecialLight( LightManager::slSunLightType, mLight );
  
   GFX->setStateBlock( mDefaultGuiSB );

   F32 left, right, top, bottom, nearPlane, farPlane;
   bool isOrtho;
   GFX->getFrustum( &left, &right, &bottom, &top, &nearPlane, &farPlane, &isOrtho );

   Frustum frust( false, left, right, top, bottom, nearPlane, farPlane, MatrixF::Identity );

   SceneRenderState state
   (
      gClientSceneGraph,
      SPT_Diffuse,
      SceneCameraState( GFX->getViewport(), frust, GFX->getWorldMatrix(), GFX->getProjectionMatrix() ),
      renderPass,
      false
   );

   // Set up our TS render state here.   
   TSRenderState rdata;
   rdata.setSceneState( &state );

   // We might have some forward lit materials
   // so pass down a query to gather lights.
   LightQuery query;
   query.init( SphereF( Point3F::Zero, 1.0f ) );
   rdata.setLightQuery( &query );

   // Render primary model.

   if( mModel )
   {
      if( mRunThread )
      {
         mModel->advanceTime( dt / 1000.f, mRunThread );
         mModel->animate();
      }
      
      mModel->render( rdata );
   }
   
   // Render mounted model.

   if( mMountedModel && mMountNode != -1 )
   {
      GFX->pushWorldMatrix();
      GFX->multWorld( mModel->mNodeTransforms[ mMountNode ] );
      GFX->multWorld( mMountTransform );
      
      mMountedModel->render( rdata );

      GFX->popWorldMatrix();
   }

   renderPass->renderPass( &state );

   // Make sure to remove our fake sun.
   LIGHTMGR->unregisterAllLights();
}