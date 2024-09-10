DFBResult
GetConfigAttribs::eglGetConfigAttribs( EGL::Display        &display,
                                       EGLNativePixmapType  native,
                                       EGLint              *attribs,
                                       EGLint               max )
{
     D_DEBUG_AT( DFBEGL_GetConfigAttribs, "%s( display %p, native %p, attribs %p, max %d )\n", __FUNCTION__, &display, native, attribs, max );

     if (!attribs)
          return DFB_INVARG;

     DFB_EGL_ATTRIB_LIST_DEBUG_AT( DFBEGL_GetConfigAttribs, attribs );

     IDirectFBSurface *surface = (IDirectFBSurface *) native;

     for (EGLint *v=attribs; *v != EGL_NONE; v+=2) {
          if (max > 0 && v-attribs >= max) {
               D_DEBUG_AT( DFBEGL_GetConfigAttribs, "  -> max (%d) reached (%ld)\n", max, v-attribs );
               break;
          }

          EGLint                attribute = v[0];
          EGLint                value     = v[1];
          DFBSurfacePixelFormat format;
          DFBDimension          size;

          D_DEBUG_AT( DFBEGL_GetConfigAttribs, "  -> [%ld] 0x%04x '%s'  <- %d (0x%08x)\n", v-attribs, attribute, **EGLInt(attribute), value, value );

          switch (attribute) {
          case EGL_BUFFER_SIZE:
               surface->GetPixelFormat( surface, &format );
               value = DFB_COLOR_BITS_PER_PIXEL( format );
               break;

          case EGL_ALPHA_SIZE:
               surface->GetPixelFormat( surface, &format );
               value = DFB_ALPHA_BITS_PER_PIXEL( format );
               break;

          case EGL_BLUE_SIZE:
          case EGL_GREEN_SIZE:
          case EGL_RED_SIZE:
               surface->GetPixelFormat( surface, &format );
               value = DFB_COLOR_BITS_PER_PIXEL( format ) / 3;//FIXME
               break;

          //case EGL_DEPTH_SIZE:
          //case EGL_STENCIL_SIZE:
          //case EGL_RENDERABLE_TYPE:

          case EGL_SURFACE_TYPE:
               value = EGL_WINDOW_BIT;  // FIXME
               break;

          case EGL_WIDTH:     // keep? not a config attribute actually
               surface->GetSize( surface, &size.w, &size.h );
               value = size.w;
               break;

          case EGL_HEIGHT:    // keep? not a config attribute actually
               surface->GetSize( surface, &size.w, &size.h );
               value = size.h;
               break;

          default:
               D_DEBUG_AT( DFBEGL_GetConfigAttribs, "  -> UNRECOGNIZED!!!\n" );
               continue;
          }

          D_DEBUG_AT( DFBEGL_GetConfigAttribs, "            => %d (0x%08x)\n", value, value );

          v[1] = value;
     }

     D_DEBUG_AT( DFBEGL_GetConfigAttribs, " --> DONE -------------\n" );

     DFB_EGL_ATTRIB_LIST_DEBUG_AT( DFBEGL_GetConfigAttribs, attribs );

     return DFB_OK;
}