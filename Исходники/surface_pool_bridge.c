static void
deallocate_transfer( CoreSurfacePoolTransfer *transfer )
{
     CoreSurfacePoolBridge *bridge;

     D_MAGIC_ASSERT( transfer, CoreSurfacePoolTransfer );

     bridge = transfer->bridge;
     D_MAGIC_ASSERT( bridge, CoreSurfacePoolBridge );

     D_MAGIC_CLEAR( transfer );

     SHFREE( bridge->shmpool, transfer );
}