DHGLRC APIENTRY
DrvCreateLayerContext(
   HDC hdc,
   INT iLayerPlane )
{
   int iPixelFormat;
   const struct stw_pixelformat_info *pfi;
   struct st_context_attribs attribs;
   struct stw_context *ctx = NULL;
   
   if(!stw_dev)
      return 0;
   
   if (iLayerPlane != 0)
      return 0;

   iPixelFormat = GetPixelFormat(hdc);
   if(!iPixelFormat)
      return 0;
   
   pfi = stw_pixelformat_get_info( iPixelFormat - 1 );
   
   ctx = CALLOC_STRUCT( stw_context );
   if (ctx == NULL)
      goto no_ctx;

   ctx->hdc = hdc;
   ctx->iPixelFormat = iPixelFormat;

   memset(&attribs, 0, sizeof(attribs));
   attribs.profile = ST_PROFILE_DEFAULT;
   attribs.visual = pfi->stvis;

   ctx->st = stw_dev->stapi->create_context(stw_dev->stapi,
         stw_dev->smapi, &attribs, NULL);
   if (ctx->st == NULL) 
      goto no_st_ctx;

   ctx->st->st_manager_private = (void *) ctx;

   pipe_mutex_lock( stw_dev->ctx_mutex );
   ctx->dhglrc = handle_table_add(stw_dev->ctx_table, ctx);
   pipe_mutex_unlock( stw_dev->ctx_mutex );
   if (!ctx->dhglrc)
      goto no_hglrc;

   return ctx->dhglrc;

no_hglrc:
   ctx->st->destroy(ctx->st);
no_st_ctx:
   FREE(ctx);
no_ctx:
   return 0;
}