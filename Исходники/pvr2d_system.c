static DFBResult
system_initialize( CoreDFB *core, void **ret_data )
{
     DFBResult            ret;
     PVR2DData            *data;
     PVR2DDataShared      *shared;
     FusionSHMPoolShared *pool;

     D_ASSERT( m_data == NULL );

     data = D_CALLOC( 1, sizeof(PVR2DData) );
     if (!data)
          return D_OOM();

     data->core = core;

     pool = dfb_core_shmpool( core );

     shared = SHCALLOC( pool, 1, sizeof(PVR2DDataShared) );
     if (!shared) {
          D_FREE( data );
          return D_OOSHM();
     }

     shared->shmpool = pool;

     data->shared = shared;

     ret = InitPVR2D( data );
     if (ret) {
          SHFREE( pool, shared );
          D_FREE( data );
          return ret;
     }

     ret = InitEGL( data );
     if (ret) {
          SHFREE( pool, shared );
          D_FREE( data );
          return ret;
     }

     *ret_data = m_data = data;

     data->screen = dfb_screens_register( NULL, data, pvr2dPrimaryScreenFuncs );
     data->layer  = dfb_layers_register( data->screen, data, pvr2dPrimaryLayerFuncs );

     dfb_surface_pool_initialize( core, pvr2dSurfacePoolFuncs, &shared->pool );

     fusion_arena_add_shared_field( dfb_core_arena( core ), "pvr2d", shared );

     return DFB_OK;
}