static void
surface_destructor( FusionObject *object, bool zombie, void *ctx )
{
     int          i;
     CoreSurface *surface = (CoreSurface*) object;

     D_MAGIC_ASSERT( surface, CoreSurface );

     D_DEBUG_AT( Core_Surface, "destroying %p (%dx%d%s)\n", surface,
                 surface->config.size.w, surface->config.size.h, zombie ? " ZOMBIE" : "");

     Core_Resource_RemoveSurface( surface );

     CoreSurface_Deinit_Dispatch( &surface->call );

     dfb_surface_lock( surface );

     surface->state |= CSSF_DESTROYED;

     /* announce surface destruction */
     dfb_surface_notify( surface, CSNF_DESTROY );

     /* unlink palette */
     if (surface->palette) {
          dfb_palette_detach_global( surface->palette, &surface->palette_reaction );
          dfb_palette_unlink( &surface->palette );
     }

     /* destroy buffers */
     for (i=0; i<MAX_SURFACE_BUFFERS; i++) {
          if (surface->buffers[i])
               dfb_surface_buffer_decouple( surface->buffers[i] );
     }

     dfb_system_surface_data_destroy( surface, surface->data );

     /* release the system driver specific surface data */
     if (surface->data) {
          SHFREE( surface->shmpool, surface->data );
          surface->data = NULL;
     }

     direct_serial_deinit( &surface->serial );

     dfb_surface_unlock( surface );

     fusion_skirmish_destroy( &surface->lock );

     D_MAGIC_CLEAR( surface );

     fusion_object_destroy( object );
}