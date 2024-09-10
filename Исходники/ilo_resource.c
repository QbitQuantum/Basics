static void
tex_layout_validate(struct tex_layout *layout)
{
   /*
    * From the Sandy Bridge PRM, volume 1 part 1, page 118:
    *
    *     "To determine the necessary padding on the bottom and right side of
    *      the surface, refer to the table in Section 7.18.3.4 for the i and j
    *      parameters for the surface format in use. The surface must then be
    *      extended to the next multiple of the alignment unit size in each
    *      dimension, and all texels contained in this extended surface must
    *      have valid GTT entries."
    *
    *     "For cube surfaces, an additional two rows of padding are required
    *      at the bottom of the surface. This must be ensured regardless of
    *      whether the surface is stored tiled or linear.  This is due to the
    *      potential rotation of cache line orientation from memory to cache."
    *
    *     "For compressed textures (BC* and FXT1 surface formats), padding at
    *      the bottom of the surface is to an even compressed row, which is
    *      equal to a multiple of 8 uncompressed texel rows. Thus, for padding
    *      purposes, these surfaces behave as if j = 8 only for surface
    *      padding purposes. The value of 4 for j still applies for mip level
    *      alignment and QPitch calculation."
    */
   if (layout->templ->bind & PIPE_BIND_SAMPLER_VIEW) {
      layout->width = align(layout->width, layout->align_i);
      layout->height = align(layout->height, layout->align_j);

      if (layout->templ->target == PIPE_TEXTURE_CUBE)
         layout->height += 2;

      if (layout->compressed)
         layout->height = align(layout->height, layout->align_j * 2);
   }

   /*
    * From the Sandy Bridge PRM, volume 1 part 1, page 118:
    *
    *     "If the surface contains an odd number of rows of data, a final row
    *      below the surface must be allocated."
    */
   if (layout->templ->bind & PIPE_BIND_RENDER_TARGET)
      layout->height = align(layout->height, 2);

   /*
    * From the Sandy Bridge PRM, volume 1 part 2, page 22:
    *
    *     "A 4KB tile is subdivided into 8-high by 8-wide array of Blocks for
    *      W-Major Tiles (W Tiles). Each Block is 8 rows by 8 bytes."
    *
    * Since we ask for INTEL_TILING_NONE instead of the non-existent
    * INTEL_TILING_W, we need to manually align the width and height to the
    * tile boundaries.
    */
   if (layout->templ->format == PIPE_FORMAT_S8_UINT) {
      layout->width = align(layout->width, 64);
      layout->height = align(layout->height, 64);
   }

   /*
    * Depth Buffer Clear/Resolve works in 8x4 sample blocks.  In
    * ilo_texture_can_enable_hiz(), we always return true for the first slice.
    * To avoid out-of-bound access, we have to pad.
    */
   if (layout->hiz) {
      layout->width = align(layout->width, 8);
      layout->height = align(layout->height, 4);
   }

   assert(layout->width % layout->block_width == 0);
   assert(layout->height % layout->block_height == 0);
   assert(layout->qpitch % layout->block_height == 0);
}