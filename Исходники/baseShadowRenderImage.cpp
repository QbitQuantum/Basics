void BaseShadowRenderImage::preRenderShadow(TSRenderContext & rc, float curTime)
{
   if (!castShadow)
      return;
      
	// do visibility check for shadow
   Point3F center;
   m_mul(shape->getShape().fCenter,transform,&center);
	SphereF shadowSphere = SphereF(center,shape->getShape().fRadius);
	int shadowVis = rc.getCamera()->testVisibility(shadowSphere);
	if ( shadowVis==TS::ClipNoneVis )
   {
      shadowSettings.shadowDetail = -1;
      return;
   }

   // shape detail to use for shadows
   if (!shadowOwnDetail)
   {
      projSize = rc.getCamera()->transformProjectRadius( center, shape->getShape().fRadius );
      float adjustedSize = shadowDetailScale * projSize;
                           
      shadowSettings.shadowDetail = shape->getShape().selectDetail( adjustedSize );

      if (shadowSettings.shadowDetail==-1)
         return;
   }

   // first pass at shadow details
   setShadowDetailsA(rc);

   // set shadow details may veto shadow
   if (shadowSettings.shadowDetail==-1)
      return;

   // set light direction, but only if different than before
   Point3F * pLight = &lightDirection;
   Point3F tempDirection;
   if (swingDown != 0.0f)
   {
      tempDirection = (lightDirection * (1.0f - swingDown)) + (Point3F(0, 0, -1) * swingDown);
      tempDirection.normalize();
      pLight = &tempDirection;
   }
   if (m_dot(*pLight,lastLight) < 0.999)
   {
      shadow.setLight( *pLight, shape);
      lastLight = *pLight;
      nextShadowUpdateTime = -1;
   }

   // set position of shadow
   shadow.setPosition(transform.p);

   if (shadowSettings.cacheProjection)
   {
      if (shadowSettings.recacheProjection)
      {
         shadow.calcSourceWindow(shape,transform);
         getPolys();
         shadow.cachePolys();
         shadowSettings.recacheProjection = false;
      }
   }
   else
   {
      shadow.calcSourceWindow(shape,transform);
      getPolys();
      Point3F cc = rc.getCamera()->getTCW().p;
      Point3F camY = transform.p-cc;
      camY.normalize();
      shadow.getPlanes(cc,camY);
   }
   
   setShadowDetails(rc);
   
   // set shadow details may veto shadow
   if (shadowSettings.shadowDetail==-1)
      return;

   if (shadowSettings.shadowDetail < shadowSettings.hiShadowDetail)
      shadowSettings.shadowDetail = shadowSettings.hiShadowDetail;

   // adjust next update time...
   nextShadowUpdateTime += shadowSettings.updateDelta - prevShadowUpdateDelta;
   prevShadowUpdateDelta = shadowSettings.updateDelta;

   // adjust bmp dim...
   int newBmpDim = shadowSettings.bmpDim;
   if (newBmpDim != prevBmpDim)
   {
      prevBmpDim = newBmpDim;
      shadow.setBitmapSize(deviceManager.getGFXDeviceManager(),newBmpDim,rc.getSurface());
      nextShadowUpdateTime = -1;
   }

   shadow.setAlphaLevel(alphaLevel);

   // create the shadow bitmap if needed
   if (curTime > nextShadowUpdateTime)
   {
      if (shadowSettings.useFloor)
      {
         SimContainerQuery query;
         Box3F & box = query.box;
         box.fMin    = box.fMax = center;
         box.fMin.z += shape->getShape().fRadius;
         box.fMax.z -= shape->getShape().fRadius * 1.5f;
         query.id = -1;
         query.type = -1;
         query.mask = shadowSettings.projectTerrainOnly ? SimTerrainObjectType : projectionMask;
         SimCollisionInfo collision;
         if (root->findLOS(query,&collision))
         {
            Point3F n,p;
            m_mul(collision.surfaces[0].position,collision.surfaces.tWorld,&p);
            m_mul(collision.surfaces[0].normal,(RMat3F&)collision.surfaces.tWorld,&n);
            p -= transform.p;
            Point3F lift = n;
            lift *= shadowSettings.liftFloor;
            p += lift;
            shadow.setFloor(p,n);
         }
         else
            shadow.clearFloor();
      }
      else
         shadow.clearFloor();

      shape->setDetailLevel(shadowSettings.shadowDetail);
      shape->animate();
      GFXPalette * pal = SimGame::get()->getWorld(SimGame::CLIENT)->getPalette();
      AssertFatal(pal, "invalid palette");
      // getShadowBitmap assumes calcSourceWindow already called...
      // ...but that's ok because we called it above
      shadow.getShadowBitmap(shape,pal,transform,shadowSettings.blurMethod);
      nextShadowUpdateTime = curTime + shadowSettings.updateDelta;
   }

	AssertFatal(root,
		"shadowRenderImage::preRenderShadow:  cannot cast shadow before \'root\' container set");

   // this'll keep track of how many shadows are out there
   if (shadowNum < 0)
      shadowNum=1; // first preRender this render cycle
   else
      shadowNum++;
}