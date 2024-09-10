static DFBResult
IDirectFBImageProvider_ANDROID_RenderTo( IDirectFBImageProvider *thiz,
                                         IDirectFBSurface       *destination,
                                         const DFBRectangle     *dest_rect )
{
     DFBResult              ret;
     bool                   direct = false;
     DFBRegion              clip;
     DFBRectangle           rect;
     DFBSurfacePixelFormat  format;
     IDirectFBSurface_data *dst_data;
     CoreSurface           *dst_surface;
     CoreSurfaceBufferLock  lock;
     DIRenderCallbackResult cb_result = DIRCR_OK;

     DIRECT_INTERFACE_GET_DATA(IDirectFBImageProvider_ANDROID)

     dst_data = (IDirectFBSurface_data*) destination->priv;
     if (!dst_data)
          return DFB_DEAD;

     dst_surface = dst_data->surface;
     if (!dst_surface)
          return DFB_DESTROYED;

     ret = decodeImage( data );
     if (ret)
          return ret;

     ret = destination->GetPixelFormat( destination, &format );
     if (ret)
          return ret;

     dfb_region_from_rectangle( &clip, &dst_data->area.current );

     if (dest_rect) {
          if (dest_rect->w < 1 || dest_rect->h < 1)
               return DFB_INVARG;

          rect = *dest_rect;
          rect.x += dst_data->area.wanted.x;
          rect.y += dst_data->area.wanted.y;

          if (!dfb_rectangle_region_intersects( &rect, &clip ))
               return DFB_OK;
     }
     else {
          rect = dst_data->area.wanted;
     }

     ret = dfb_surface_lock_buffer( dst_surface, CSBR_BACK, CSAID_CPU, CSAF_WRITE, &lock );
     if (ret)
          return ret;

     dfb_scale_linear_32( (u32 *)data->image, data->width, data->height, lock.addr, lock.pitch, &rect, dst_surface, &clip );
     if (data->base.render_callback) {
          DFBRectangle r = { 0, 0, data->width, data->height };
          data->base.render_callback( &r, data->base.render_callback_context );
     }

     dfb_surface_unlock_buffer( dst_surface, &lock );

     return DFB_OK;
}