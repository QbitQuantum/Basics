/*
 * Create a new X/Mesa visual.
 * Input:  display - X11 display
 *         visinfo - an XVisualInfo pointer
 *         rgb_flag - GL_TRUE = RGB mode,
 *                    GL_FALSE = color index mode
 *         alpha_flag - alpha buffer requested?
 *         db_flag - GL_TRUE = double-buffered,
 *                   GL_FALSE = single buffered
 *         stereo_flag - stereo visual?
 *         ximage_flag - GL_TRUE = use an XImage for back buffer,
 *                       GL_FALSE = use an off-screen pixmap for back buffer
 *         depth_size - requested bits/depth values, or zero
 *         stencil_size - requested bits/stencil values, or zero
 *         accum_red_size - requested bits/red accum values, or zero
 *         accum_green_size - requested bits/green accum values, or zero
 *         accum_blue_size - requested bits/blue accum values, or zero
 *         accum_alpha_size - requested bits/alpha accum values, or zero
 *         num_samples - number of samples/pixel if multisampling, or zero
 *         level - visual level, usually 0
 *         visualCaveat - ala the GLX extension, usually GLX_NONE
 * Return;  a new XMesaVisual or 0 if error.
 */
PUBLIC
XMesaVisual XMesaCreateVisual( XMesaDisplay *display,
                               XMesaVisualInfo visinfo,
                               GLboolean rgb_flag,
                               GLboolean alpha_flag,
                               GLboolean db_flag,
                               GLboolean stereo_flag,
                               GLboolean ximage_flag,
                               GLint depth_size,
                               GLint stencil_size,
                               GLint accum_red_size,
                               GLint accum_green_size,
                               GLint accum_blue_size,
                               GLint accum_alpha_size,
                               GLint num_samples,
                               GLint level,
                               GLint visualCaveat )
{
   char *gamma;
   XMesaVisual v;
   GLint red_bits, green_bits, blue_bits, alpha_bits;

   /* For debugging only */
   if (_mesa_getenv("MESA_XSYNC")) {
      /* This makes debugging X easier.
       * In your debugger, set a breakpoint on _XError to stop when an
       * X protocol error is generated.
       */
      XSynchronize( display, 1 );
   }

   /* Color-index rendering not supported. */
   if (!rgb_flag)
      return NULL;

   v = (XMesaVisual) CALLOC_STRUCT(xmesa_visual);
   if (!v) {
      return NULL;
   }

   v->display = display;

   /* Save a copy of the XVisualInfo struct because the user may Xfree()
    * the struct but we may need some of the information contained in it
    * at a later time.
    */
   v->visinfo = (XVisualInfo *) MALLOC(sizeof(*visinfo));
   if(!v->visinfo) {
      free(v);
      return NULL;
   }
   memcpy(v->visinfo, visinfo, sizeof(*visinfo));

   /* check for MESA_GAMMA environment variable */
   gamma = _mesa_getenv("MESA_GAMMA");
   if (gamma) {
      v->RedGamma = v->GreenGamma = v->BlueGamma = 0.0;
      sscanf( gamma, "%f %f %f", &v->RedGamma, &v->GreenGamma, &v->BlueGamma );
      if (v->RedGamma<=0.0)    v->RedGamma = 1.0;
      if (v->GreenGamma<=0.0)  v->GreenGamma = v->RedGamma;
      if (v->BlueGamma<=0.0)   v->BlueGamma = v->RedGamma;
   }
   else {
      v->RedGamma = v->GreenGamma = v->BlueGamma = 1.0;
   }

   v->ximage_flag = ximage_flag;

   v->mesa_visual.redMask = visinfo->red_mask;
   v->mesa_visual.greenMask = visinfo->green_mask;
   v->mesa_visual.blueMask = visinfo->blue_mask;
   v->visualID = visinfo->visualid;
   v->screen = visinfo->screen;

#if !(defined(__cplusplus) || defined(c_plusplus))
   v->visualType = xmesa_convert_from_x_visual_type(visinfo->class);
#else
   v->visualType = xmesa_convert_from_x_visual_type(visinfo->c_class);
#endif

   v->mesa_visual.visualRating = visualCaveat;

   if (alpha_flag)
      v->mesa_visual.alphaBits = 8;

   (void) initialize_visual_and_buffer( v, NULL, 0, 0 );

   {
      const int xclass = v->visualType;
      if (xclass == GLX_TRUE_COLOR || xclass == GLX_DIRECT_COLOR) {
         red_bits   = _mesa_bitcount(GET_REDMASK(v));
         green_bits = _mesa_bitcount(GET_GREENMASK(v));
         blue_bits  = _mesa_bitcount(GET_BLUEMASK(v));
      }
      else {
         /* this is an approximation */
         int depth;
         depth = GET_VISUAL_DEPTH(v);
         red_bits = depth / 3;
         depth -= red_bits;
         green_bits = depth / 2;
         depth -= green_bits;
         blue_bits = depth;
         alpha_bits = 0;
         assert( red_bits + green_bits + blue_bits == GET_VISUAL_DEPTH(v) );
      }
      alpha_bits = v->mesa_visual.alphaBits;
   }

   if (!_mesa_initialize_visual(&v->mesa_visual,
                                db_flag, stereo_flag,
                                red_bits, green_bits,
                                blue_bits, alpha_bits,
                                depth_size,
                                stencil_size,
                                accum_red_size, accum_green_size,
                                accum_blue_size, accum_alpha_size,
                                0)) {
      FREE(v);
      return NULL;
   }

   /* XXX minor hack */
   v->mesa_visual.level = level;
   return v;
}