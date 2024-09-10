static DFBResult
x11DeallocateBuffer( CoreSurfacePool       *pool,
                     void                  *pool_data,
                     void                  *pool_local,
                     CoreSurfaceBuffer     *buffer,
                     CoreSurfaceAllocation *allocation,
                     void                  *alloc_data )
{
     x11AllocationData *alloc  = alloc_data;
     x11PoolLocalData  *local  = pool_local;
     DFBX11            *x11    = local->x11;
     DFBX11Shared      *shared = x11->shared;
     void              *addr;

     D_DEBUG_AT( X11_Surfaces, "%s()\n", __FUNCTION__ );

     D_MAGIC_ASSERT( pool, CoreSurfacePool );

     CORE_SURFACE_ALLOCATION_ASSERT( allocation );

     switch (alloc->type) {
          case X11_ALLOC_PIXMAP:
          case X11_ALLOC_WINDOW:
               if (allocation->type & CSTF_PREALLOCATED) {
                    // don't delete
               }
               else
                    XFreePixmap( x11->display, alloc->xid );
               break;

          case X11_ALLOC_IMAGE:
               x11ImageDestroy( x11, &alloc->image );

               // FIXME: also detach in other processes! (e.g. via reactor)
               addr = direct_hash_lookup( local->hash, alloc->image.seginfo.shmid );
               if (addr) {
                    x11ImageDetach( &alloc->image, addr );

                    direct_hash_remove( local->hash, alloc->image.seginfo.shmid );
               }
               break;

          case X11_ALLOC_SHM:
               if (alloc->ptr)
                    SHFREE( shared->data_shmpool, alloc->ptr );
               break;

          default:
               D_BUG( "unexpected allocation type %d\n", alloc->type );
               return DFB_BUG;
     }

     return DFB_OK;
}