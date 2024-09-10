/* Create the device specific context.
 */
GLboolean r128CreateContext( const __GLcontextModes *glVisual,
			     __DRIcontextPrivate *driContextPriv,
                             void *sharedContextPrivate )
{
   GLcontext *ctx, *shareCtx;
   __DRIscreenPrivate *sPriv = driContextPriv->driScreenPriv;
   struct dd_function_table functions;
   r128ContextPtr rmesa;
   r128ScreenPtr r128scrn;
   int i;

   /* Allocate the r128 context */
   rmesa = (r128ContextPtr) CALLOC( sizeof(*rmesa) );
   if ( !rmesa )
      return GL_FALSE;

   /* Init default driver functions then plug in our Radeon-specific functions
    * (the texture functions are especially important)
    */
   _mesa_init_driver_functions( &functions );
   r128InitDriverFuncs( &functions );
   r128InitIoctlFuncs( &functions );
   r128InitTextureFuncs( &functions );

   /* Allocate the Mesa context */
   if (sharedContextPrivate)
      shareCtx = ((r128ContextPtr) sharedContextPrivate)->glCtx;
   else 
      shareCtx = NULL;
   rmesa->glCtx = _mesa_create_context(glVisual, shareCtx,
                                       &functions, (void *) rmesa);
   if (!rmesa->glCtx) {
      FREE(rmesa);
      return GL_FALSE;
   }
   driContextPriv->driverPrivate = rmesa;
   ctx = rmesa->glCtx;

   rmesa->driContext = driContextPriv;
   rmesa->driScreen = sPriv;
   rmesa->driDrawable = NULL;
   rmesa->hHWContext = driContextPriv->hHWContext;
   rmesa->driHwLock = &sPriv->pSAREA->lock;
   rmesa->driFd = sPriv->fd;

   r128scrn = rmesa->r128Screen = (r128ScreenPtr)(sPriv->private);

   /* Parse configuration files */
   driParseConfigFiles (&rmesa->optionCache, &r128scrn->optionCache,
                        r128scrn->driScreen->myNum, "r128");

   rmesa->sarea = (drm_r128_sarea_t *)((char *)sPriv->pSAREA +
				     r128scrn->sarea_priv_offset);

   rmesa->CurrentTexObj[0] = NULL;
   rmesa->CurrentTexObj[1] = NULL;

   (void) memset( rmesa->texture_heaps, 0, sizeof( rmesa->texture_heaps ) );
   make_empty_list( & rmesa->swapped );

   rmesa->nr_heaps = r128scrn->numTexHeaps;
   for ( i = 0 ; i < rmesa->nr_heaps ; i++ ) {
      rmesa->texture_heaps[i] = driCreateTextureHeap( i, rmesa,
	    r128scrn->texSize[i],
	    12,
	    R128_NR_TEX_REGIONS,
	    (drmTextureRegionPtr)rmesa->sarea->tex_list[i],
	    &rmesa->sarea->tex_age[i],
	    &rmesa->swapped,
	    sizeof( r128TexObj ),
	    (destroy_texture_object_t *) r128DestroyTexObj );

      driSetTextureSwapCounterLocation( rmesa->texture_heaps[i],
					& rmesa->c_textureSwaps );
   }
   rmesa->texture_depth = driQueryOptioni (&rmesa->optionCache,
					   "texture_depth");
   if (rmesa->texture_depth == DRI_CONF_TEXTURE_DEPTH_FB)
      rmesa->texture_depth = ( r128scrn->cpp == 4 ) ?
	 DRI_CONF_TEXTURE_DEPTH_32 : DRI_CONF_TEXTURE_DEPTH_16;


   rmesa->RenderIndex = -1;		/* Impossible value */
   rmesa->vert_buf = NULL;
   rmesa->num_verts = 0;
   RENDERINPUTS_ONES( rmesa->tnl_state_bitset );

   /* Set the maximum texture size small enough that we can guarentee that
    * all texture units can bind a maximal texture and have them both in
    * texturable memory at once.
    */

   ctx->Const.MaxTextureUnits = 2;
   ctx->Const.MaxTextureImageUnits = 2;
   ctx->Const.MaxTextureCoordUnits = 2;

   driCalculateMaxTextureLevels( rmesa->texture_heaps,
				 rmesa->nr_heaps,
				 & ctx->Const,
				 4,
				 10, /* max 2D texture size is 1024x1024 */
				 0,  /* 3D textures unsupported. */
				 0,  /* cube textures unsupported. */
				 0,  /* texture rectangles unsupported. */
				 11,
				 GL_FALSE,
				 0 );

   /* No wide points.
    */
   ctx->Const.MinPointSize = 1.0;
   ctx->Const.MinPointSizeAA = 1.0;
   ctx->Const.MaxPointSize = 1.0;
   ctx->Const.MaxPointSizeAA = 1.0;

   /* No wide lines.
    */
   ctx->Const.MinLineWidth = 1.0;
   ctx->Const.MinLineWidthAA = 1.0;
   ctx->Const.MaxLineWidth = 1.0;
   ctx->Const.MaxLineWidthAA = 1.0;
   ctx->Const.LineWidthGranularity = 1.0;

#if ENABLE_PERF_BOXES
   rmesa->boxes = driQueryOptionb(&rmesa->optionCache, "performance_boxes");
#endif

   /* Initialize the software rasterizer and helper modules.
    */
   _swrast_CreateContext( ctx );
   _vbo_CreateContext( ctx );
   _tnl_CreateContext( ctx );
   _swsetup_CreateContext( ctx );

   /* Install the customized pipeline:
    */
/*     _tnl_destroy_pipeline( ctx ); */
/*     _tnl_install_pipeline( ctx, r128_pipeline ); */

   /* Configure swrast and T&L to match hardware characteristics:
    */
   _swrast_allow_pixel_fog( ctx, GL_FALSE );
   _swrast_allow_vertex_fog( ctx, GL_TRUE );
   _tnl_allow_pixel_fog( ctx, GL_FALSE );
   _tnl_allow_vertex_fog( ctx, GL_TRUE );

   driInitExtensions( ctx, card_extensions, GL_TRUE );
   if (sPriv->drmMinor >= 4)
      _mesa_enable_extension( ctx, "GL_MESA_ycbcr_texture" );

   r128InitTriFuncs( ctx );
   r128DDInitStateFuncs( ctx );
   r128DDInitSpanFuncs( ctx );
   r128DDInitState( rmesa );

   rmesa->vblank_flags = (rmesa->r128Screen->irq != 0)
       ? driGetDefaultVBlankFlags(&rmesa->optionCache) : VBLANK_FLAG_NO_IRQ;

   driContextPriv->driverPrivate = (void *)rmesa;

#if DO_DEBUG
   R128_DEBUG = driParseDebugString( getenv( "R128_DEBUG" ),
				     debug_control );
#endif

   if (driQueryOptionb(&rmesa->optionCache, "no_rast")) {
      fprintf(stderr, "disabling 3D acceleration\n");
      FALLBACK(rmesa, R128_FALLBACK_DISABLE, 1);
   }

   return GL_TRUE;
}