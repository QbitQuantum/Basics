void SingleLightShadowMap::_render( RenderPassManager* renderPass,
                                    const SceneRenderState *diffuseState )
{
   PROFILE_SCOPE(SingleLightShadowMap_render);

   const LightMapParams *lmParams = mLight->getExtended<LightMapParams>();
   const bool bUseLightmappedGeometry = lmParams ? !lmParams->representedInLightmap || lmParams->includeLightmappedGeometryInShadow : true;

   const U32 texSize = getBestTexSize();

   if (  mShadowMapTex.isNull() ||
         mTexSize != texSize )
   {
      mTexSize = texSize;

      mShadowMapTex.set(   mTexSize, mTexSize, 
                           ShadowMapFormat, &ShadowMapProfile, 
                           "SingleLightShadowMap" );
   }

   GFXFrustumSaver frustSaver;
   GFXTransformSaver saver;

   MatrixF lightMatrix;
   calcLightMatrices( lightMatrix, diffuseState->getCameraFrustum() );
   lightMatrix.inverse();
   GFX->setWorldMatrix(lightMatrix);

   const MatrixF& lightProj = GFX->getProjectionMatrix();
   mWorldToLightProj = lightProj * lightMatrix;

   // Render the shadowmap!
   GFX->pushActiveRenderTarget();
   mTarget->attachTexture( GFXTextureTarget::Color0, mShadowMapTex );
   mTarget->attachTexture( GFXTextureTarget::DepthStencil, 
      _getDepthTarget( mShadowMapTex->getWidth(), mShadowMapTex->getHeight() ) );
   GFX->setActiveRenderTarget(mTarget);
   GFX->clear(GFXClearStencil | GFXClearZBuffer | GFXClearTarget, ColorI(255,255,255), 1.0f, 0);

   SceneManager* sceneManager = diffuseState->getSceneManager();
   
   SceneRenderState shadowRenderState
   (
      sceneManager,
      SPT_Shadow,
      SceneCameraState::fromGFXWithViewport( diffuseState->getViewport() ),
      renderPass
   );

   shadowRenderState.getMaterialDelegate().bind( this, &LightShadowMap::getShadowMaterial );
   shadowRenderState.renderNonLightmappedMeshes( true );
   shadowRenderState.renderLightmappedMeshes( bUseLightmappedGeometry );
   shadowRenderState.setDiffuseCameraTransform( diffuseState->getCameraTransform() );
   shadowRenderState.setWorldToScreenScale( diffuseState->getWorldToScreenScale() );

   sceneManager->renderSceneNoLights( &shadowRenderState, SHADOW_TYPEMASK );

   _debugRender( &shadowRenderState );

   mTarget->resolve();
   GFX->popActiveRenderTarget();
}