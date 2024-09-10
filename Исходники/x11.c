static DFBResult
system_shutdown( bool emergency )
{
     DFBX11       *x11    = dfb_system_data();
     DFBX11Shared *shared = x11->shared;

     int i;

     D_DEBUG_AT( X11_Core, "%s()\n", __FUNCTION__ );

     //dfb_x11_eglimpl_unregister();

     /*
      * Master deinit
      */
     if (shared->x11_pool_bridge)
          dfb_surface_pool_bridge_destroy( shared->x11_pool_bridge );

     if (shared->vpsmem_pool)
          dfb_surface_pool_destroy( shared->vpsmem_pool );

     if (shared->glx_pool)
          dfb_surface_pool_destroy( shared->glx_pool );

     if (shared->x11window_pool)
          dfb_surface_pool_destroy( shared->x11window_pool );

     if (shared->x11image_pool)
          dfb_surface_pool_destroy( shared->x11image_pool );


     /*
      * Shared deinit (master only)
      */
     fusion_call_destroy( &shared->call );

     /* close remaining windows */
     for( i=0; i<shared->outputs; i++ ) {
          dfb_x11_close_window( x11, shared->output[i].xw );
     }


     SHFREE( dfb_core_shmpool( x11->core ), shared );


     /*
      * Local deinit (master and slave)
      */
     if (x11->display)
         XCloseDisplay( x11->display );

     D_FREE( x11 );

     return DFB_OK;
}