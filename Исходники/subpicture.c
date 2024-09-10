PUBLIC
Status XvMCCreateSubpicture(Display *dpy, XvMCContext *context, XvMCSubpicture *subpicture,
                            unsigned short width, unsigned short height, int xvimage_id)
{
   XvMCContextPrivate *context_priv;
   XvMCSubpicturePrivate *subpicture_priv;
   struct pipe_context *pipe;
   struct pipe_resource tex_templ, *tex;
   struct pipe_sampler_view sampler_templ;
   Status ret;

   XVMC_MSG(XVMC_TRACE, "[XvMC] Creating subpicture %p.\n", subpicture);

   assert(dpy);

   if (!context)
      return XvMCBadContext;

   context_priv = context->privData;
   pipe = context_priv->pipe;

   if (!subpicture)
      return XvMCBadSubpicture;

   if (width > context_priv->subpicture_max_width ||
       height > context_priv->subpicture_max_height)
      return BadValue;

   ret = Validate(dpy, context->port, context->surface_type_id, xvimage_id);
   if (ret != Success)
      return ret;

   subpicture_priv = CALLOC(1, sizeof(XvMCSubpicturePrivate));
   if (!subpicture_priv)
      return BadAlloc;

   memset(&tex_templ, 0, sizeof(tex_templ));
   tex_templ.target = PIPE_TEXTURE_2D;
   tex_templ.format = XvIDToPipe(xvimage_id);
   tex_templ.last_level = 0;
   if (pipe->screen->get_video_param(pipe->screen,
                                     PIPE_VIDEO_PROFILE_UNKNOWN,
                                     PIPE_VIDEO_CAP_NPOT_TEXTURES)) {
      tex_templ.width0 = width;
      tex_templ.height0 = height;
   }
   else {
      tex_templ.width0 = util_next_power_of_two(width);
      tex_templ.height0 = util_next_power_of_two(height);
   }
   tex_templ.depth0 = 1;
   tex_templ.array_size = 1;
   tex_templ.usage = PIPE_USAGE_DYNAMIC;
   tex_templ.bind = PIPE_BIND_SAMPLER_VIEW;
   tex_templ.flags = 0;

   tex = pipe->screen->resource_create(pipe->screen, &tex_templ);

   memset(&sampler_templ, 0, sizeof(sampler_templ));
   u_sampler_view_default_template(&sampler_templ, tex, tex->format);

   subpicture_priv->sampler = pipe->create_sampler_view(pipe, tex, &sampler_templ);
   pipe_resource_reference(&tex, NULL);
   if (!subpicture_priv->sampler) {
      FREE(subpicture_priv);
      return BadAlloc;
   }

   subpicture_priv->context = context;
   subpicture->subpicture_id = XAllocID(dpy);
   subpicture->context_id = context->context_id;
   subpicture->xvimage_id = xvimage_id;
   subpicture->width = width;
   subpicture->height = height;
   subpicture->num_palette_entries = NumPaletteEntries4XvID(xvimage_id);
   subpicture->entry_bytes = PipeToComponentOrder(tex_templ.format, subpicture->component_order);
   subpicture->privData = subpicture_priv;

   if (subpicture->num_palette_entries > 0) {
      tex_templ.target = PIPE_TEXTURE_1D;
      tex_templ.format = PIPE_FORMAT_R8G8B8X8_UNORM;
      tex_templ.width0 = subpicture->num_palette_entries;
      tex_templ.height0 = 1;
      tex_templ.usage = PIPE_USAGE_STATIC;

      tex = pipe->screen->resource_create(pipe->screen, &tex_templ);

      memset(&sampler_templ, 0, sizeof(sampler_templ));
      u_sampler_view_default_template(&sampler_templ, tex, tex->format);
      sampler_templ.swizzle_a = PIPE_SWIZZLE_ONE;
      subpicture_priv->palette = pipe->create_sampler_view(pipe, tex, &sampler_templ);
      pipe_resource_reference(&tex, NULL);
      if (!subpicture_priv->sampler) {
         FREE(subpicture_priv);
         return BadAlloc;
      }
   }

   SyncHandle();

   XVMC_MSG(XVMC_TRACE, "[XvMC] Subpicture %p created.\n", subpicture);

   return Success;
}