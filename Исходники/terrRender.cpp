void TerrainBlock::_updateBaseTexture(bool writeToCache)
{
   if ( !mBaseShader && !_initBaseShader() )
      return;

   // This can sometimes occur outside a begin/end scene.
   const bool sceneBegun = GFX->canCurrentlyRender();
   if ( !sceneBegun )
      GFX->beginScene();

   GFXDEBUGEVENT_SCOPE( TerrainBlock_UpdateBaseTexture, ColorI::GREEN );

   PROFILE_SCOPE( TerrainBlock_UpdateBaseTexture );

   GFXTransformSaver saver;

   const U32 maxTextureSize = GFX->getCardProfiler()->queryProfile( "maxTextureSize", 1024 );

   U32 baseTexSize = getNextPow2( mBaseTexSize );
   baseTexSize = getMin( maxTextureSize, baseTexSize );
   Point2I destSize( baseTexSize, baseTexSize );

   // Setup geometry
   GFXVertexBufferHandle<GFXVertexPT> vb;
   {
      F32 copyOffsetX = 2.0f * GFX->getFillConventionOffset() / (F32)destSize.x;
      F32 copyOffsetY = 2.0f * GFX->getFillConventionOffset() / (F32)destSize.y;

      GFXVertexPT points[4];
      points[0].point = Point3F(1.0 - copyOffsetX, -1.0 + copyOffsetY, 0.0);
      points[0].texCoord = Point2F(1.0, 1.0f);
      points[1].point = Point3F(1.0 - copyOffsetX, 1.0 + copyOffsetY, 0.0);
      points[1].texCoord = Point2F(1.0, 0.0f);
      points[2].point = Point3F(-1.0 - copyOffsetX, -1.0 + copyOffsetY, 0.0);
      points[2].texCoord = Point2F(0.0, 1.0f);
      points[3].point = Point3F(-1.0 - copyOffsetX, 1.0 + copyOffsetY, 0.0);
      points[3].texCoord = Point2F(0.0, 0.0f);

      vb.set( GFX, 4, GFXBufferTypeVolatile );
      GFXVertexPT *ptr = vb.lock();
      if(ptr)
      {
         dMemcpy( ptr, points, sizeof(GFXVertexPT) * 4 );
         vb.unlock();
      }
   }

   GFXTexHandle blendTex;

   // If the base texture is already a valid render target then 
   // use it to render to else we create one.
   if (  mBaseTex.isValid() && 
         mBaseTex->isRenderTarget() &&
         mBaseTex->getFormat() == GFXFormatR8G8B8A8 &&
         mBaseTex->getWidth() == destSize.x &&
         mBaseTex->getHeight() == destSize.y )
      blendTex = mBaseTex;
   else
      blendTex.set( destSize.x, destSize.y, GFXFormatR8G8B8A8, &GFXDefaultRenderTargetProfile, "" );

   GFX->pushActiveRenderTarget();   

   // Set our shader stuff
   GFX->setShader( mBaseShader );
   GFX->setShaderConstBuffer( mBaseShaderConsts );
   GFX->setStateBlock( mBaseShaderSB );
   GFX->setVertexBuffer( vb );

   mBaseTarget->attachTexture( GFXTextureTarget::Color0, blendTex );
   GFX->setActiveRenderTarget( mBaseTarget );

   GFX->clear( GFXClearTarget, ColorI(0,0,0,255), 1.0f, 0 );

   GFX->setTexture( 0, mLayerTex );
   mBaseShaderConsts->setSafe( mBaseLayerSizeConst, (F32)mLayerTex->getWidth() );      

   for ( U32 i=0; i < mBaseTextures.size(); i++ )
   {
      GFXTextureObject *tex = mBaseTextures[i];
      if ( !tex )
         continue;

      GFX->setTexture( 1, tex );

      F32 baseSize = mFile->mMaterials[i]->getDiffuseSize();
      F32 scale = 1.0f;
      if ( !mIsZero( baseSize ) )
         scale = getWorldBlockSize() / baseSize;
      
      // A mistake early in development means that texture
      // coords are not flipped correctly.  To compensate
      // we flip the y scale here.
      mBaseShaderConsts->setSafe( mBaseTexScaleConst, Point2F( scale, -scale ) );
      mBaseShaderConsts->setSafe( mBaseTexIdConst, (F32)i );

      GFX->drawPrimitive( GFXTriangleStrip, 0, 2 );
   }

   mBaseTarget->resolve();
   
   GFX->setShader( NULL );
   //GFX->setStateBlock( NULL ); // WHY NOT?
   GFX->setShaderConstBuffer( NULL );
   GFX->setVertexBuffer( NULL );

   GFX->popActiveRenderTarget();

   // End it if we begun it... Yeehaw!
   if ( !sceneBegun )
      GFX->endScene();

   /// Do we cache this sucker?
   if (mBaseTexFormat == NONE || !writeToCache)
   {
      // We didn't cache the result, so set the base texture
      // to the render target we updated.  This should be good
      // for realtime painting cases.
      mBaseTex = blendTex;
   }
   else if (mBaseTexFormat == DDS)
   {
      String cachePath = _getBaseTexCacheFileName();

      FileStream fs;
      if ( fs.open( _getBaseTexCacheFileName(), Torque::FS::File::Write ) )
      {
         // Read back the render target, dxt compress it, and write it to disk.
         GBitmap blendBmp( destSize.x, destSize.y, false, GFXFormatR8G8B8A8 );
         blendTex.copyToBmp( &blendBmp );

         /*
         // Test code for dumping uncompressed bitmap to disk.
         {
         FileStream fs;
         if ( fs.open( "./basetex.png", Torque::FS::File::Write ) )
         {
         blendBmp.writeBitmap( "png", fs );
         fs.close();
         }         
         }
         */

         blendBmp.extrudeMipLevels();

         DDSFile *blendDDS = DDSFile::createDDSFileFromGBitmap( &blendBmp );
         DDSUtil::squishDDS( blendDDS, GFXFormatDXT1 );

         // Write result to file stream
         blendDDS->write( fs );
         
         delete blendDDS;
      }
      fs.close();
   }
   else
   {
      FileStream stream;
      if (!stream.open(_getBaseTexCacheFileName(), Torque::FS::File::Write))
      {
         mBaseTex = blendTex;
         return;
      }

      GBitmap bitmap(blendTex->getWidth(), blendTex->getHeight(), false, GFXFormatR8G8B8);
      blendTex->copyToBmp(&bitmap);
      bitmap.writeBitmap(formatToExtension(mBaseTexFormat), stream);
   }
}