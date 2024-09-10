void PSSMLightShadowMap::_render(   RenderPassManager* renderPass,
                                    const SceneRenderState *diffuseState )
{
   PROFILE_SCOPE(PSSMLightShadowMap_render);

   const ShadowMapParams *params = mLight->getExtended<ShadowMapParams>();
   const LightMapParams *lmParams = mLight->getExtended<LightMapParams>();
   const bool bUseLightmappedGeometry = lmParams ? !lmParams->representedInLightmap || lmParams->includeLightmappedGeometryInShadow : true;

   const U32 texSize = getBestTexSize( params->numSplits < 4 ? params->numSplits : 2 );

   if (  mShadowMapTex.isNull() || 
         mNumSplits != params->numSplits || 
         mTexSize != texSize )
   {
      _setNumSplits( params->numSplits, texSize );
      mShadowMapDepth = _getDepthTarget( mShadowMapTex->getWidth(), mShadowMapTex->getHeight() );   
   }
   mLogWeight = params->logWeight;

   Frustum fullFrustum( diffuseState->getCameraFrustum() );
   fullFrustum.cropNearFar(fullFrustum.getNearDist(), params->shadowDistance);

   GFXFrustumSaver frustSaver;
   GFXTransformSaver saver;

   // Set our render target
   GFX->pushActiveRenderTarget();
   mTarget->attachTexture( GFXTextureTarget::Color0, mShadowMapTex );
   mTarget->attachTexture( GFXTextureTarget::DepthStencil, mShadowMapDepth );
   GFX->setActiveRenderTarget( mTarget );
   GFX->clear( GFXClearStencil | GFXClearZBuffer | GFXClearTarget, ColorI(255,255,255), 1.0f, 0 );

   // Calculate our standard light matrices
   MatrixF lightMatrix;
   calcLightMatrices( lightMatrix, diffuseState->getCameraFrustum() );
   lightMatrix.inverse();
   MatrixF lightViewProj = GFX->getProjectionMatrix() * lightMatrix;

   // TODO: This is just retrieving the near and far calculated
   // in calcLightMatrices... we should make that clear.
   F32 pnear, pfar;
   GFX->getFrustum( NULL, NULL, NULL, NULL, &pnear, &pfar, NULL );

   // Set our view up
   GFX->setWorldMatrix(lightMatrix);
   MatrixF toLightSpace = lightMatrix; // * invCurrentView;

   _calcSplitPos(fullFrustum);
   
   mWorldToLightProj = GFX->getProjectionMatrix() * toLightSpace;

   // Apply the PSSM 
   const F32 savedSmallestVisible = TSShapeInstance::smSmallestVisiblePixelSize;
   const F32 savedDetailAdjust = TSShapeInstance::smDetailAdjust;
   TSShapeInstance::smDetailAdjust *= smDetailAdjustScale;
   TSShapeInstance::smSmallestVisiblePixelSize = smSmallestVisiblePixelSize;

   for (U32 i = 0; i < mNumSplits; i++)
   {
      GFXTransformSaver saver;

      // Calculate a sub-frustum
      Frustum subFrustum(fullFrustum);
      subFrustum.cropNearFar(mSplitDist[i], mSplitDist[i+1]);

      // Calculate our AABB in the light's clip space.
      Box3F clipAABB = _calcClipSpaceAABB(subFrustum, lightViewProj, fullFrustum.getFarDist());
 
      // Calculate our crop matrix
      Point3F scale(2.0f / (clipAABB.maxExtents.x - clipAABB.minExtents.x),
         2.0f / (clipAABB.maxExtents.y - clipAABB.minExtents.y),
         1.0f);

      // TODO: This seems to produce less "pops" of the
      // shadow resolution as the camera spins around and
      // it should produce pixels that are closer to being
      // square.
      //
      // Still is it the right thing to do?
      //
      scale.y = scale.x = ( getMin( scale.x, scale.y ) ); 
      //scale.x = mFloor(scale.x); 
      //scale.y = mFloor(scale.y); 

      Point3F offset(   -0.5f * (clipAABB.maxExtents.x + clipAABB.minExtents.x) * scale.x,
                        -0.5f * (clipAABB.maxExtents.y + clipAABB.minExtents.y) * scale.y,
                        0.0f );

      MatrixF cropMatrix(true);
      cropMatrix.scale(scale);
      cropMatrix.setPosition(offset);

      _roundProjection(lightMatrix, cropMatrix, offset, i);

      cropMatrix.setPosition(offset);      

      // Save scale/offset for shader computations
      mScaleProj[i].set(scale);
      mOffsetProj[i].set(offset);

      // Adjust the far plane to the max z we got (maybe add a little to deal with split overlap)
      bool isOrtho;
      {
         F32 left, right, bottom, top, nearDist, farDist;
         GFX->getFrustum(&left, &right, &bottom, &top, &nearDist, &farDist,&isOrtho);
         // BTRTODO: Fix me!
         farDist = clipAABB.maxExtents.z;
         if (!isOrtho)
            GFX->setFrustum(left, right, bottom, top, nearDist, farDist);
         else
         {
            // Calculate a new far plane, add a fudge factor to avoid bringing
            // the far plane in too close.
            F32 newFar = pfar * clipAABB.maxExtents.z + 1.0f;
            mFarPlaneScalePSSM[i] = (pfar - pnear) / (newFar - pnear);
            GFX->setOrtho(left, right, bottom, top, pnear, newFar, true);
         }
      }

      // Crop matrix multiply needs to be post-projection.
      MatrixF alightProj = GFX->getProjectionMatrix();
      alightProj = cropMatrix * alightProj;

      // Set our new projection
      GFX->setProjectionMatrix(alightProj);

      // Render into the quad of the shadow map we are using.
      GFX->setViewport(mViewports[i]);

      SceneManager* sceneManager = diffuseState->getSceneManager();

      // The frustum is currently the  full size and has not had
      // cropping applied.
      //
      // We make that adjustment here.

      const Frustum& uncroppedFrustum = GFX->getFrustum();
      Frustum croppedFrustum;
      scale *= 0.5f;
      croppedFrustum.set(
         isOrtho,
         uncroppedFrustum.getNearLeft() / scale.x,
         uncroppedFrustum.getNearRight() / scale.x,
         uncroppedFrustum.getNearTop() / scale.y,
         uncroppedFrustum.getNearBottom() / scale.y,
         uncroppedFrustum.getNearDist(),
         uncroppedFrustum.getFarDist(),
         uncroppedFrustum.getTransform()
      );

      MatrixF camera = GFX->getWorldMatrix();
      camera.inverse();
      croppedFrustum.setTransform( camera );

      // Setup the scene state and use the diffuse state
      // camera position and screen metrics values so that
      // lod is done the same as in the diffuse pass.

      SceneRenderState shadowRenderState
      (
         sceneManager,
         SPT_Shadow,
         SceneCameraState( diffuseState->getViewport(), croppedFrustum,
                           GFX->getWorldMatrix(), GFX->getProjectionMatrix() ),
         renderPass
      );

      shadowRenderState.getMaterialDelegate().bind( this, &LightShadowMap::getShadowMaterial );
      shadowRenderState.renderNonLightmappedMeshes( true );
      shadowRenderState.renderLightmappedMeshes( bUseLightmappedGeometry );

      shadowRenderState.setDiffuseCameraTransform( diffuseState->getCameraTransform() );
      shadowRenderState.setWorldToScreenScale( diffuseState->getWorldToScreenScale() );

      U32 objectMask = SHADOW_TYPEMASK;
      if ( i == mNumSplits-1 && params->lastSplitTerrainOnly )
         objectMask = TerrainObjectType;

      sceneManager->renderSceneNoLights( &shadowRenderState, objectMask );

      _debugRender( &shadowRenderState );
   }

   // Restore the original TS lod settings.
   TSShapeInstance::smSmallestVisiblePixelSize = savedSmallestVisible;
   TSShapeInstance::smDetailAdjust = savedDetailAdjust;

   // Release our render target
   mTarget->resolve();
   GFX->popActiveRenderTarget();
}