static DFBResult
system_initialize( CoreDFB *core, void **ret_data )
{
     DFBResult            ret;
     DevMemData          *data;
     DevMemDataShared    *shared;
     FusionSHMPoolShared *pool;

     D_ASSERT( m_data == NULL );

     if (!dfb_config->video_phys || !dfb_config->video_length) {
          D_ERROR( "System/DevMem: Please supply 'video-phys = 0xXXXXXXXX' and 'video-length = XXXX' options!\n" );
          return DFB_INVARG;
     }

     if (dfb_config->mmio_phys && !dfb_config->mmio_length) {
          D_ERROR( "System/DevMem: Please supply both 'mmio-phys = 0xXXXXXXXX' and 'mmio-length = XXXX' options or none!\n" );
          return DFB_INVARG;
     }

     data = D_CALLOC( 1, sizeof(DevMemData) );
     if (!data)
          return D_OOM();

     pool = dfb_core_shmpool( core );

     shared = SHCALLOC( pool, 1, sizeof(DevMemDataShared) );
     if (!shared) {
          D_FREE( data );
          return D_OOSHM();
     }

     shared->shmpool = pool;

     data->shared = shared;

     ret = MapMemAndReg( data,
                         dfb_config->video_phys, dfb_config->video_length,
                         dfb_config->mmio_phys,  dfb_config->mmio_length );
     if (ret) {
          SHFREE( pool, shared );
          D_FREE( data );
          return ret;
     }


     *ret_data = m_data = data;

     dfb_surface_pool_initialize( core, &devmemSurfacePoolFuncs, &shared->pool );

     fusion_arena_add_shared_field( dfb_core_arena( core ), "devmem", shared );

     return DFB_OK;
}