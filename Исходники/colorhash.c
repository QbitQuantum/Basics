void
dfb_colorhash_detach( DFBColorHashCore *core,
                      CorePalette      *palette )
{
     DFBColorHashCoreShared *shared;

     D_ASSUME( core != NULL );

     if (core) {
          D_MAGIC_ASSERT( core, DFBColorHashCore );
          D_MAGIC_ASSERT( core->shared, DFBColorHashCoreShared );
     }
     else
          core = core_colorhash;

     shared = core->shared;

     D_ASSERT( shared->hash_users > 0 );
     D_ASSERT( shared->hash != NULL );

     fusion_skirmish_prevail( &shared->hash_lock );

     shared->hash_users--;

     if (!shared->hash_users) {
          /* no more users, free allocated resources */
          SHFREE( shared->shmpool, shared->hash );
          shared->hash = NULL;
     }

     fusion_skirmish_dismiss( &shared->hash_lock );
}