void DualParaboloidLightShadowMap::_render(  RenderPassManager* renderPass,
                                             const SceneRenderState *diffuseState )
{
   PROFILE_SCOPE(DualParaboloidLightShadowMap_render);

   const ShadowMapParams *p = mLight->getExtended<ShadowMapParams>();
   const LightMapParams *lmParams = mLight->getExtended<LightMapParams>();
   const bool bUseLightmappedGeometry = lmParams ? !lmParams->representedInLightmap || lmParams->includeLightmappedGeometryInShadow : true;

   const U32 texSize = getBestTexSize( 2 );

   if (  mShadowMapTex.isNull() || 
         mTexSize != texSize )
   {
      mTexSize = texSize;

      mShadowMapTex.set(   mTexSize * 2, mTexSize, 
                           ShadowMapFormat, &ShadowMapProfile, 
                           "DualParaboloidLightShadowMap" );
      mShadowMapDepth = _getDepthTarget( mShadowMapTex->getWidth(), mShadowMapTex->getHeight() );
   }

   GFXFrustumSaver frustSaver;
   GFXTransformSaver saver;   

   // Set and Clear target
   GFX->pushActiveRenderTarget();

   mTarget->attachTexture(GFXTextureTarget::Color0, mShadowMapTex);
   mTarget->attachTexture( GFXTextureTarget::DepthStencil, mShadowMapDepth );
   GFX->setActiveRenderTarget(mTarget);
   GFX->clear(GFXClearTarget | GFXClearStencil | GFXClearZBuffer, ColorI::WHITE, 1.0f, 0);

   const bool bUseSinglePassDPM = (p->shadowType == ShadowType_DualParaboloidSinglePass);

   // Set up matrix and visible distance
   mWorldToLightProj = mLight->getTransform();
   mWorldToLightProj.inverse();

   const F32 &lightRadius = mLight->getRange().x;
   const F32 paraboloidNearPlane = 0.01f;
   const F32 renderPosOffset = 0.01f;
   
   // Alter for creation of scene state if this is a single pass map
   if(bUseSinglePassDPM)
   {
      VectorF camDir;
      MatrixF temp = mLight->getTransform();
      temp.getColumn(1, &camDir);
      temp.setPosition(mLight->getPosition() - camDir * (lightRadius + renderPosOffset));
      temp.inverse();
      GFX->setWorldMatrix(temp);
      GFX->setOrtho(-lightRadius, lightRadius, -lightRadius, lightRadius, paraboloidNearPlane, 2.0f * lightRadius, true);
   }
   else
   {
      VectorF camDir;
      MatrixF temp = mLight->getTransform();
      temp.getColumn(1, &camDir);
      temp.setPosition(mLight->getPosition() - camDir * renderPosOffset);
      temp.inverse();
      GFX->setWorldMatrix(temp);

      GFX->setOrtho(-lightRadius, lightRadius, -lightRadius, lightRadius, paraboloidNearPlane, lightRadius, true);
   }

   SceneManager* sceneManager = diffuseState->getSceneManager();
   
   // Front map render
   {
      SceneRenderState frontMapRenderState
      (
         sceneManager,
         SPT_Shadow,
         SceneCameraState::fromGFXWithViewport( diffuseState->getViewport() ),
         renderPass
      );

      frontMapRenderState.getMaterialDelegate().bind( this, &LightShadowMap::getShadowMaterial );
      frontMapRenderState.renderNonLightmappedMeshes( true );
      frontMapRenderState.renderLightmappedMeshes( bUseLightmappedGeometry );
      frontMapRenderState.setDiffuseCameraTransform( diffuseState->getCameraTransform() );
      frontMapRenderState.setWorldToScreenScale( diffuseState->getWorldToScreenScale() );

      if(bUseSinglePassDPM)
      {
         GFX->setWorldMatrix(mWorldToLightProj);
         frontMapRenderState.getRenderPass()->getMatrixSet().setSceneView(mWorldToLightProj);
         GFX->setOrtho(-lightRadius, lightRadius, -lightRadius, lightRadius, paraboloidNearPlane, lightRadius, true);
      }

      GFXDEBUGEVENT_SCOPE( DualParaboloidLightShadowMap_Render_FrontFacingParaboloid, ColorI::RED );
      mShadowMapScale.set(0.5f, 1.0f);
      mShadowMapOffset.set(-0.5f, 0.0f);
      sceneManager->renderSceneNoLights( &frontMapRenderState, SHADOW_TYPEMASK );
      _debugRender( &frontMapRenderState );
   }
   
   // Back map render 
   if(!bUseSinglePassDPM)
   {
      GFXDEBUGEVENT_SCOPE( DualParaboloidLightShadowMap_Render_BackFacingParaboloid, ColorI::RED );

      mShadowMapScale.set(0.5f, 1.0f);
      mShadowMapOffset.set(0.5f, 0.0f);

      // Invert direction on camera matrix
      VectorF right, forward;
      MatrixF temp = mLight->getTransform();
      temp.getColumn( 1, &forward );
      temp.getColumn( 0, &right );
      forward *= -1.0f;      
      right *= -1.0f;
      temp.setColumn( 1, forward );
      temp.setColumn( 0, right );
      temp.setPosition(mLight->getPosition() - forward * -renderPosOffset);
      temp.inverse();
      GFX->setWorldMatrix(temp);

      // Create an inverted scene state for the back-map

      SceneRenderState backMapRenderState
      (
         sceneManager,
         SPT_Shadow,
         SceneCameraState::fromGFXWithViewport( diffuseState->getViewport() ),
         renderPass
      );

      backMapRenderState.getMaterialDelegate().bind( this, &LightShadowMap::getShadowMaterial );
      backMapRenderState.renderNonLightmappedMeshes( true );
      backMapRenderState.renderLightmappedMeshes( bUseLightmappedGeometry );
      backMapRenderState.setDiffuseCameraTransform( diffuseState->getCameraTransform() );
      backMapRenderState.setWorldToScreenScale( diffuseState->getWorldToScreenScale() );

      backMapRenderState.getRenderPass()->getMatrixSet().setSceneView(temp);

      // Draw scene
      sceneManager->renderSceneNoLights( &backMapRenderState );
      _debugRender( &backMapRenderState );
   }

   mTarget->resolve();
   GFX->popActiveRenderTarget();
}