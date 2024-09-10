DFBResult
dfb_palette_create( CoreDFB       *core,
                    unsigned int   size,
                    CorePalette  **ret_palette )
{
     CorePalette *palette;

     D_DEBUG_AT( Core_Palette, "%s( %d )\n", __FUNCTION__, size );

     D_ASSERT( ret_palette );

     palette = dfb_core_create_palette( core );
     if (!palette)
          return DFB_FUSION;

     palette->shmpool = dfb_core_shmpool( core );

     if (size) {
          palette->entries = SHCALLOC( palette->shmpool, size, sizeof(DFBColor) );
          if (!palette->entries) {
               fusion_object_destroy( &palette->object );
               return D_OOSHM();
          }

          palette->entries_yuv = SHCALLOC( palette->shmpool, size, sizeof(DFBColorYUV) );
          if (!palette->entries_yuv) {
               SHFREE( palette->shmpool, palette->entries );
               fusion_object_destroy( &palette->object );
               return D_OOSHM();
          }
     }

     palette->num_entries = size;

     /* reset cache */
     palette->search_cache.index = -1;

     D_MAGIC_SET( palette, CorePalette );

     /* activate object */
     fusion_object_activate( &palette->object );

     /* return the new palette */
     *ret_palette = palette;

     D_DEBUG_AT( Core_Palette, "  -> %p\n", palette );

     return DFB_OK;
}