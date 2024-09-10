static int
dfb_core_arena_initialize( FusionArena *arena,
                           void        *ctx )
{
     DFBResult            ret;
     CoreDFB             *core = ctx;
     CoreDFBShared       *shared;
     FusionSHMPoolShared *pool;

     D_MAGIC_ASSERT( core, CoreDFB );

     D_DEBUG_AT( DirectFB_Core, "Initializing...\n" );

     /* Create the shared memory pool first! */
     ret = fusion_shm_pool_create( core->world, "DirectFB Main Pool", 0x400000,
                                   fusion_config->debugshm, &pool );
     if (ret)
          return ret;

     /* Allocate shared structure in the new pool. */
     shared = SHCALLOC( pool, 1, sizeof(CoreDFBShared) );
     if (!shared) {
          fusion_shm_pool_destroy( core->world, pool );
          return D_OOSHM();
     }

     core->shared = shared;
     core->master = true;

     shared->shmpool = pool;

     D_MAGIC_SET( shared, CoreDFBShared );

     /* Initialize. */
     ret = dfb_core_initialize( core );
     if (ret) {
          D_MAGIC_CLEAR( shared );
          SHFREE( pool, shared );
          fusion_shm_pool_destroy( core->world, pool );
          return ret;
     }

     fusion_skirmish_init( &shared->lock, "DirectFB Core", core->world );

     CoreDFB_Init_Dispatch( core, core, &shared->call );

     fusion_call_add_permissions( &shared->call, 0, FUSION_CALL_PERMIT_EXECUTE );

     /* Register shared data. */
     fusion_arena_add_shared_field( arena, "Core/Shared", shared );

     return DFB_OK;
}