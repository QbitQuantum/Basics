void GuiTSCtrl::onRender(Point2I offset, const RectI &updateRect)
{
	// Save the current transforms so we can restore
   // it for child control rendering below.
   GFXTransformSaver saver;
   bool renderingToTarget = false;

   if(!processCameraQuery(&mLastCameraQuery))
   {
      // We have no camera, but render the GUI children 
      // anyway.  This makes editing GuiTSCtrl derived
      // controls easier in the GuiEditor.
      renderChildControls( offset, updateRect );
      return;
   }

   GFXTargetRef origTarget = GFX->getActiveRenderTarget();

   // Set up the appropriate render style
   U32 prevRenderStyle = GFX->getCurrentRenderStyle();
   Point2F prevProjectionOffset = GFX->getCurrentProjectionOffset();
   Point2I renderSize = getExtent();

   if(mRenderStyle == RenderStyleStereoSideBySide)
   {
      GFX->setCurrentRenderStyle(GFXDevice::RS_StereoSideBySide);
      GFX->setCurrentProjectionOffset(mLastCameraQuery.projectionOffset);
      GFX->setStereoEyeOffsets(mLastCameraQuery.eyeOffset);

      if (!mLastCameraQuery.hasStereoTargets)
      {
         // Need to calculate our current viewport here
         mLastCameraQuery.stereoViewports[0] = updateRect;
         mLastCameraQuery.stereoViewports[0].extent.x /= 2;
         mLastCameraQuery.stereoViewports[1] = mLastCameraQuery.stereoViewports[0];
         mLastCameraQuery.stereoViewports[1].point.x += mLastCameraQuery.stereoViewports[1].extent.x;
      }

      if (!mLastCameraQuery.hasFovPort)
      {
         // Need to make our own fovPort
         mLastCameraQuery.fovPort[0] = CalculateFovPortForCanvas(mLastCameraQuery.stereoViewports[0], mLastCameraQuery);
         mLastCameraQuery.fovPort[1] = CalculateFovPortForCanvas(mLastCameraQuery.stereoViewports[1], mLastCameraQuery);
      }
         
      GFX->setStereoFovPort(mLastCameraQuery.fovPort); // NOTE: this specifies fov for BOTH eyes

      GFX->setSteroViewports(mLastCameraQuery.stereoViewports);
      GFX->setStereoTargets(mLastCameraQuery.stereoTargets);

      MatrixF myTransforms[2];

      if (smUseLatestDisplayTransform)
      {
         // Use the view matrix determined from the display device
         myTransforms[0] = mLastCameraQuery.eyeTransforms[0];
         myTransforms[1] = mLastCameraQuery.eyeTransforms[1];
      }
      else
      {
         // Use the view matrix determined from the control object
         myTransforms[0] = mLastCameraQuery.cameraMatrix;
         myTransforms[1] = mLastCameraQuery.cameraMatrix;

         QuatF qrot = mLastCameraQuery.cameraMatrix;
         Point3F pos = mLastCameraQuery.cameraMatrix.getPosition();
         Point3F rotEyePos;

         myTransforms[0].setPosition(pos + qrot.mulP(mLastCameraQuery.eyeOffset[0], &rotEyePos));
         myTransforms[1].setPosition(pos + qrot.mulP(mLastCameraQuery.eyeOffset[1], &rotEyePos));
      }

      GFX->setStereoEyeTransforms(myTransforms);

      // Allow render size to originate from the render target
      if (mLastCameraQuery.stereoTargets[0])
      {
         renderSize = mLastCameraQuery.stereoViewports[0].extent;
         renderingToTarget = true;
      }
   }
   else
   {
      GFX->setCurrentRenderStyle(GFXDevice::RS_Standard);
   }

   if ( mReflectPriority > 0 )
   {
      // Get the total reflection priority.
      F32 totalPriority = 0;
      for ( U32 i=0; i < smAwakeTSCtrls.size(); i++ )
         if ( smAwakeTSCtrls[i]->isVisible() )
            totalPriority += smAwakeTSCtrls[i]->mReflectPriority;

      REFLECTMGR->update(  mReflectPriority / totalPriority,
                           getExtent(),
                           mLastCameraQuery );
   }

   if(mForceFOV != 0)
      mLastCameraQuery.fov = mDegToRad(mForceFOV);

   if(mCameraZRot)
   {
      MatrixF rotMat(EulerF(0, 0, mDegToRad(mCameraZRot)));
      mLastCameraQuery.cameraMatrix.mul(rotMat);
   }

   Frustum frustum;
   if(mRenderStyle == RenderStyleStereoSideBySide)
   {
      // NOTE: these calculations are essentially overridden later by the fov port settings when rendering each eye.
      MathUtils::makeFovPortFrustum(&frustum, mLastCameraQuery.ortho,  mLastCameraQuery.nearPlane, mLastCameraQuery.farPlane, mLastCameraQuery.fovPort[0]);
   }
   else
   {
      // set up the camera and viewport stuff:
      F32 wwidth;
      F32 wheight;
      F32 renderWidth = F32(renderSize.x);
      F32 renderHeight = F32(renderSize.y);
      F32 aspectRatio = renderWidth / renderHeight;
   
      // Use the FOV to calculate the viewport height scale
      // then generate the width scale from the aspect ratio.
      if(!mLastCameraQuery.ortho)
      {
         wheight = mLastCameraQuery.nearPlane * mTan(mLastCameraQuery.fov / 2.0f);
         wwidth = aspectRatio * wheight;
      }
      else
      {
         wheight = mLastCameraQuery.fov;
         wwidth = aspectRatio * wheight;
      }

      F32 hscale = wwidth * 2.0f / renderWidth;
      F32 vscale = wheight * 2.0f / renderHeight;

      F32 left = (updateRect.point.x - offset.x) * hscale - wwidth;
      F32 right = (updateRect.point.x + updateRect.extent.x - offset.x) * hscale - wwidth;
      F32 top = wheight - vscale * (updateRect.point.y - offset.y);
      F32 bottom = wheight - vscale * (updateRect.point.y + updateRect.extent.y - offset.y);

      frustum.set( mLastCameraQuery.ortho, left, right, top, bottom, mLastCameraQuery.nearPlane, mLastCameraQuery.farPlane );
   }

	// Manipulate the frustum for tiled screenshots
	const bool screenShotMode = gScreenShot && gScreenShot->isPending();
   if ( screenShotMode )
   {
      gScreenShot->tileFrustum( frustum );      
      GFX->setViewMatrix(MatrixF::Identity);
   }
      
   RectI tempRect = updateRect;
   
   if (!renderingToTarget)
   {
   #ifdef TORQUE_OS_MAC
      Point2I screensize = getRoot()->getWindowSize();
      tempRect.point.y = screensize.y - (tempRect.point.y + tempRect.extent.y);
   #endif

      GFX->setViewport( tempRect );
   }
   else
   {
      // Activate stereo RT
      GFX->activateStereoTarget(-1);
   }

   // Clear the zBuffer so GUI doesn't hose object rendering accidentally
   GFX->clear( GFXClearZBuffer , ColorI(20,20,20), 1.0f, 0 );
   //GFX->clear( GFXClearTarget, ColorI(255,0,0), 1.0f, 0);

   GFX->setFrustum( frustum );
   if(mLastCameraQuery.ortho)
   {
      mOrthoWidth = frustum.getWidth();
      mOrthoHeight = frustum.getHeight();
   }

   // We're going to be displaying this render at size of this control in
   // pixels - let the scene know so that it can calculate e.g. reflections
   // correctly for that final display result.
   gClientSceneGraph->setDisplayTargetResolution(renderSize);

   // Set the GFX world matrix to the world-to-camera transform, but don't 
   // change the cameraMatrix in mLastCameraQuery. This is because 
   // mLastCameraQuery.cameraMatrix is supposed to contain the camera-to-world
   // transform. In-place invert would save a copy but mess up any GUIs that
   // depend on that value.
   MatrixF worldToCamera = mLastCameraQuery.cameraMatrix;
   worldToCamera.inverse();
   GFX->setWorldMatrix( worldToCamera );

   mSaveProjection = GFX->getProjectionMatrix();
   mSaveModelview = GFX->getWorldMatrix();
   mSaveViewport = updateRect;
   mSaveWorldToScreenScale = GFX->getWorldToScreenScale();
   mSaveFrustum = GFX->getFrustum();
   mSaveFrustum.setTransform( mLastCameraQuery.cameraMatrix );

   // Set the default non-clip projection as some 
   // objects depend on this even in non-reflect cases.
   gClientSceneGraph->setNonClipProjection( mSaveProjection );

   // Give the post effect manager the worldToCamera, and cameraToScreen matrices
   PFXMGR->setFrameMatrices( mSaveModelview, mSaveProjection );

   renderWorld(updateRect);
   DebugDrawer::get()->render();

   // Render the canvas overlay if its available
   if (mRenderStyle == RenderStyleStereoSideBySide && mStereoGuiTarget.getPointer())
   {
      GFXDEBUGEVENT_SCOPE( StereoGui_Render, ColorI( 255, 0, 0 ) );
      MatrixF proj(1);
      
      Frustum originalFrustum = GFX->getFrustum();
      GFXTextureObject *texObject = mStereoGuiTarget->getTexture(0);
      const FovPort *currentFovPort = GFX->getStereoFovPort();
      const MatrixF *eyeTransforms = GFX->getStereoEyeTransforms();
      const Point3F *eyeOffset = GFX->getStereoEyeOffsets();
      Frustum gfxFrustum = originalFrustum;

      for (U32 i=0; i<2; i++)
      {
         GFX->activateStereoTarget(i);
         MathUtils::makeFovPortFrustum(&gfxFrustum, true, gfxFrustum.getNearDist(), gfxFrustum.getFarDist(), currentFovPort[i], eyeTransforms[i]);
         GFX->setFrustum(gfxFrustum);

         MatrixF eyeWorldTrans(1);
         eyeWorldTrans.setPosition(Point3F(eyeOffset[i].x,eyeOffset[i].y,eyeOffset[i].z));
         MatrixF eyeWorld(1);
         eyeWorld.mul(eyeWorldTrans);
         eyeWorld.inverse();
         
         GFX->setWorldMatrix(eyeWorld);
         GFX->setViewMatrix(MatrixF::Identity);

         if (!mStereoOverlayVB.getPointer())
         {
            mStereoOverlayVB.set(GFX, 4, GFXBufferTypeStatic);
            GFXVertexPCT *verts = mStereoOverlayVB.lock(0, 4);

            F32 texLeft   = 0.0f;
            F32 texRight  = 1.0f;
            F32 texTop    = 1.0f;
            F32 texBottom = 0.0f;

            F32 rectRatio = gfxFrustum.getWidth() / gfxFrustum.getHeight();
            F32 rectWidth = gfxFrustum.getWidth() * TS_OVERLAY_SCREEN_WIDTH;
            F32 rectHeight = rectWidth * rectRatio;

            F32 screenLeft   = -rectWidth * 0.5;
            F32 screenRight  = rectWidth * 0.5;
            F32 screenTop    = -rectHeight * 0.5;
            F32 screenBottom = rectHeight * 0.5;

            const F32 fillConv = 0.0f;
            const F32 frustumDepthAdjusted = gfxFrustum.getNearDist() + 0.012;
            verts[0].point.set( screenLeft  - fillConv, frustumDepthAdjusted, screenTop    - fillConv );
            verts[1].point.set( screenRight - fillConv, frustumDepthAdjusted, screenTop    - fillConv );
            verts[2].point.set( screenLeft  - fillConv, frustumDepthAdjusted, screenBottom - fillConv );
            verts[3].point.set( screenRight - fillConv, frustumDepthAdjusted, screenBottom - fillConv );

            verts[0].color = verts[1].color = verts[2].color = verts[3].color = ColorI(255,255,255,255);

            verts[0].texCoord.set( texLeft,  texTop );
            verts[1].texCoord.set( texRight, texTop );
            verts[2].texCoord.set( texLeft,  texBottom );
            verts[3].texCoord.set( texRight, texBottom );

            mStereoOverlayVB.unlock();
         }

         if (!mStereoGuiSB.getPointer())
         {
            // DrawBitmapStretchSR
            GFXStateBlockDesc bitmapStretchSR;
            bitmapStretchSR.setCullMode(GFXCullNone);
            bitmapStretchSR.setZReadWrite(false, false);
            bitmapStretchSR.setBlend(true, GFXBlendSrcAlpha, GFXBlendInvSrcAlpha);
            bitmapStretchSR.samplersDefined = true;

            bitmapStretchSR.samplers[0] = GFXSamplerStateDesc::getClampLinear();
            bitmapStretchSR.samplers[0].minFilter = GFXTextureFilterPoint;
            bitmapStretchSR.samplers[0].mipFilter = GFXTextureFilterPoint;
            bitmapStretchSR.samplers[0].magFilter = GFXTextureFilterPoint;

            mStereoGuiSB = GFX->createStateBlock(bitmapStretchSR);
         }

         GFX->setVertexBuffer(mStereoOverlayVB);
         GFX->setStateBlock(mStereoGuiSB);
         GFX->setTexture( 0, texObject );
         GFX->setupGenericShaders( GFXDevice::GSModColorTexture );
         GFX->drawPrimitive( GFXTriangleStrip, 0, 2 );
      }
   }

	// Restore the previous matrix state before
   // we begin rendering the child controls.
   saver.restore();

   // Restore the render style and any stereo parameters
   GFX->setActiveRenderTarget(origTarget);
   GFX->setCurrentRenderStyle(prevRenderStyle);
   GFX->setCurrentProjectionOffset(prevProjectionOffset);

   
   if(mRenderStyle == RenderStyleStereoSideBySide && gLastStereoTexture)
   {
      GFX->setClipRect(updateRect);
      GFX->getDrawUtil()->drawBitmapStretch(gLastStereoTexture, updateRect);
   }

   // Allow subclasses to render 2D elements.
   GFX->setClipRect(updateRect);
   renderGui( offset, updateRect );

   if (shouldRenderChildControls())
   {
      renderChildControls(offset, updateRect);
   }
   smFrameCount++;
}