gammaScreenPtr gammaCreateScreen( __DRIscreenPrivate *sPriv )
{
   gammaScreenPtr gammaScreen;
   GLINTDRIPtr gDRIPriv = (GLINTDRIPtr)sPriv->pDevPriv;
   int i;

#if 0
   /* Check the DRI version */
   {
      int major, minor, patch;
      if ( XF86DRIQueryVersion( sPriv->display, &major, &minor, &patch ) ) {
         if ( major != 3 || minor != 1 || patch < 0 ) {
	    __driUtilMessage( "r128 DRI driver expected DRI version 3.1.x but got version %d.%d.%d", major, minor, patch );
            return GL_FALSE;
         }
      }
   }

   /* Check that the DDX driver version is compatible */
   if ( sPriv->ddxMajor != 4 ||
	sPriv->ddxMinor != 0 ||
	sPriv->ddxPatch < 0 ) {
      __driUtilMessage( "r128 DRI driver expected DDX driver version 4.0.x but got version %d.%d.%d", sPriv->ddxMajor, sPriv->ddxMinor, sPriv->ddxPatch );
      return GL_FALSE;
   }

   /* Check that the DRM driver version is compatible */
   if ( sPriv->drmMajor != 2 ||
	sPriv->drmMinor != 1 ||
	sPriv->drmPatch < 0 ) {
      __driUtilMessage( "r128 DRI driver expected DRM driver version 2.1.x but got version %d.%d.%d", sPriv->drmMajor, sPriv->drmMinor, sPriv->drmPatch );
      return GL_FALSE;
   }
#endif

    /* Allocate the private area */
    gammaScreen = (gammaScreenPtr) CALLOC( sizeof(*gammaScreen) );
    if ( !gammaScreen ) return NULL;

    gammaScreen->regionCount  = 4;	/* Magic number.  Can we fix this? */
    
    gammaScreen->regions = Xmalloc(gammaScreen->regionCount * 
							sizeof(gammaRegion));

    gammaScreen->regions[0].handle = gDRIPriv->registers0.handle;
    gammaScreen->regions[0].size   = gDRIPriv->registers0.size;
    gammaScreen->regions[1].handle = gDRIPriv->registers1.handle;
    gammaScreen->regions[1].size   = gDRIPriv->registers1.size;
    gammaScreen->regions[2].handle = gDRIPriv->registers2.handle;
    gammaScreen->regions[2].size   = gDRIPriv->registers2.size;
    gammaScreen->regions[3].handle = gDRIPriv->registers3.handle;
    gammaScreen->regions[3].size   = gDRIPriv->registers3.size;
    
    /* Next, map all the regions */
    for (i = 0; i < gammaScreen->regionCount; i++) {
	if (drmMap(sPriv->fd,
		   gammaScreen->regions[i].handle,
		   gammaScreen->regions[i].size,
		   &gammaScreen->regions[i].map)) {
	    while (--i > 0) {
		(void)drmUnmap(gammaScreen->regions[i].map, 
			       gammaScreen->regions[i].size);
	    }
	    return GL_FALSE;
	}
    }

    /* Get the list of dma buffers */
    gammaScreen->bufs = drmMapBufs(sPriv->fd);

    if (!gammaScreen->bufs) {
	while (gammaScreen->regionCount > 0) {
	    (void)drmUnmap(gammaScreen->regions[gammaScreen->regionCount].map,
			   gammaScreen->regions[gammaScreen->regionCount].size);
	    gammaScreen->regionCount--;
	}
	return GL_FALSE;
    }

   gammaScreen->textureSize	= gDRIPriv->textureSize;
   gammaScreen->logTextureGranularity = gDRIPriv->logTextureGranularity;
   gammaScreen->cpp = gDRIPriv->cpp;
   gammaScreen->frontOffset	= gDRIPriv->frontOffset;
   gammaScreen->frontPitch	= gDRIPriv->frontPitch;
   gammaScreen->backOffset	= gDRIPriv->backOffset;
   gammaScreen->backPitch	= gDRIPriv->backPitch;
   gammaScreen->backX		= gDRIPriv->backX;
   gammaScreen->backY		= gDRIPriv->backY;
   gammaScreen->depthOffset	= gDRIPriv->depthOffset;
   gammaScreen->depthPitch	= gDRIPriv->depthPitch;

   gammaScreen->driScreen = sPriv;

   return gammaScreen;
}