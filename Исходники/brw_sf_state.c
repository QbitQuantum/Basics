static enum pipe_error
sf_unit_create_from_key(struct brw_context *brw,
                        struct brw_sf_unit_key *key,
                        struct brw_winsys_reloc *reloc,
                        struct brw_winsys_buffer **bo_out)
{
   struct brw_sf_unit_state sf;
   enum pipe_error ret;
   int chipset_max_threads;
   memset(&sf, 0, sizeof(sf));

   sf.thread0.grf_reg_count = align(key->total_grf, 16) / 16 - 1;
   /* reloc */
   sf.thread0.kernel_start_pointer = 0;

   sf.thread1.floating_point_mode = BRW_FLOATING_POINT_NON_IEEE_754;

   sf.thread3.dispatch_grf_start_reg = 3;

   if (brw->gen == 5)
       sf.thread3.urb_entry_read_offset = 3;
   else
       sf.thread3.urb_entry_read_offset = 1;

   sf.thread3.urb_entry_read_length = key->urb_entry_read_length;

   sf.thread4.nr_urb_entries = key->nr_urb_entries;
   sf.thread4.urb_entry_allocation_size = key->sfsize - 1;

   /* Each SF thread produces 1 PUE, and there can be up to 24(Pre-IGDNG) or 
    * 48(IGDNG) threads 
    */
   if (brw->gen == 5)
      chipset_max_threads = 48;
   else
      chipset_max_threads = 24;

   sf.thread4.max_threads = MIN2(chipset_max_threads, key->nr_urb_entries) - 1;

   if (BRW_DEBUG & DEBUG_SINGLE_THREAD)
      sf.thread4.max_threads = 0;

   if (BRW_DEBUG & DEBUG_STATS)
      sf.thread4.stats_enable = 1;

   /* CACHE_NEW_SF_VP */
   /* reloc */
   sf.sf5.sf_viewport_state_offset = 0;

   sf.sf5.viewport_transform = 1;

   if (key->scissor)
      sf.sf6.scissor = 1;

   if (key->front_ccw)
      sf.sf5.front_winding = BRW_FRONTWINDING_CCW;
   else
      sf.sf5.front_winding = BRW_FRONTWINDING_CW;

   switch (key->cull_face) {
   case PIPE_FACE_FRONT:
      sf.sf6.cull_mode = BRW_CULLMODE_FRONT;
      break;
   case PIPE_FACE_BACK:
      sf.sf6.cull_mode = BRW_CULLMODE_BACK;
      break;
   case PIPE_FACE_FRONT_AND_BACK:
      sf.sf6.cull_mode = BRW_CULLMODE_BOTH;
      break;
   case PIPE_FACE_NONE:
      sf.sf6.cull_mode = BRW_CULLMODE_NONE;
      break;
   default:
      assert(0);
      sf.sf6.cull_mode = BRW_CULLMODE_NONE;
      break;
   }

   /* _NEW_LINE */
   /* XXX use ctx->Const.Min/MaxLineWidth here */
   sf.sf6.line_width = CLAMP(key->line_width, 1.0, 5.0) * (1<<1);

   sf.sf6.line_endcap_aa_region_width = 1;
   if (key->line_smooth)
      sf.sf6.aa_enable = 1;
   else if (sf.sf6.line_width <= 0x2)
       sf.sf6.line_width = 0;

   /* XXX: gl_rasterization_rules?  something else?
    */
   sf.sf6.point_rast_rule = BRW_RASTRULE_UPPER_RIGHT;
   sf.sf6.point_rast_rule = BRW_RASTRULE_LOWER_RIGHT;
   sf.sf6.point_rast_rule = 1;

   /* XXX clamp max depends on AA vs. non-AA */

   /* _NEW_POINT */
   sf.sf7.sprite_point = key->point_sprite;
   sf.sf7.point_size = CLAMP(rint(key->point_size), 1, 255) * (1<<3);
   sf.sf7.use_point_size_state = !key->point_attenuated;
   sf.sf7.aa_line_distance_mode = 0;

   /* might be BRW_NEW_PRIMITIVE if we have to adjust pv for polygons:
    */
   if (!key->flatshade_first) {
      sf.sf7.trifan_pv = 2;
      sf.sf7.linestrip_pv = 1;
      sf.sf7.tristrip_pv = 2;
   } else {
      sf.sf7.trifan_pv = 1;
      sf.sf7.linestrip_pv = 0;
      sf.sf7.tristrip_pv = 0;
   }

   sf.sf7.line_last_pixel_enable = key->line_last_pixel_enable;

   /* Set bias for OpenGL rasterization rules:
    */
   if (key->gl_rasterization_rules) {
      sf.sf6.dest_org_vbias = 0x8;
      sf.sf6.dest_org_hbias = 0x8;
   }
   else {
      sf.sf6.dest_org_vbias = 0x0;
      sf.sf6.dest_org_hbias = 0x0;
   }

   ret = brw_upload_cache(&brw->cache, BRW_SF_UNIT,
                          key, sizeof(*key),
                          reloc, 2,
                          &sf, sizeof(sf),
                          NULL, NULL,
                          bo_out);
   if (ret)
      return ret;

   
   return PIPE_OK;
}