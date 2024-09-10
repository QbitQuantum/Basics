/* Partition the CURBE between the various users of constant values:
 */
static void calculate_curbe_offsets( struct brw_context *brw )
{
   /* CACHE_NEW_WM_PROG */
   unsigned nr_fp_regs = align(brw->wm.prog_data->max_const, 16);

   /* BRW_NEW_VERTEX_PROGRAM */
   unsigned nr_vp_regs = align(brw->vs.prog_data->max_const, 16);
   unsigned nr_clip_regs = 0;
   unsigned total_regs;

#if 0
   /* BRW_NEW_CLIP ? */
   if (brw->attribs.Transform->ClipPlanesEnabled) {
      unsigned nr_planes = 6 + brw_count_bits(brw->attribs.Transform->ClipPlanesEnabled);
      nr_clip_regs = align(nr_planes * 4, 16);
   }
#endif


   total_regs = nr_fp_regs + nr_vp_regs + nr_clip_regs;

   /* This can happen - what to do?  Probably rather than falling
    * back, the best thing to do is emit programs which code the
    * constants as immediate values.  Could do this either as a static
    * cap on WM and VS, or adaptively.
    *
    * Unfortunately, this is currently dependent on the results of the
    * program generation process (in the case of wm), so this would
    * introduce the need to re-generate programs in the event of a
    * curbe allocation failure.
    */
   /* Max size is 32 - just large enough to
    * hold the 128 parameters allowed by
    * the fragment and vertex program
    * api's.  It's not clear what happens
    * when both VP and FP want to use 128
    * parameters, though.
    */
   assert(total_regs <= 32);

   /* Lazy resize:
    */
   if (nr_fp_regs > brw->curbe.wm_size ||
       nr_vp_regs > brw->curbe.vs_size ||
       nr_clip_regs != brw->curbe.clip_size ||
       (total_regs < brw->curbe.total_size / 4 &&
	brw->curbe.total_size > 16)) {

      unsigned reg = 0;

      /* Calculate a new layout:
       */
      reg = 0;
      brw->curbe.wm_start = reg;
      brw->curbe.wm_size = nr_fp_regs; reg += nr_fp_regs;
      brw->curbe.clip_start = reg;
      brw->curbe.clip_size = nr_clip_regs; reg += nr_clip_regs;
      brw->curbe.vs_start = reg;
      brw->curbe.vs_size = nr_vp_regs; reg += nr_vp_regs;
      brw->curbe.total_size = reg;

#if 0
      if (0)
	 DBG("curbe wm %d+%d clip %d+%d vs %d+%d\n",
		      brw->curbe.wm_start,
		      brw->curbe.wm_size,
		      brw->curbe.clip_start,
		      brw->curbe.clip_size,
		      brw->curbe.vs_start,
		      brw->curbe.vs_size );
#endif

      brw->state.dirty.brw |= BRW_NEW_CURBE_OFFSETS;
   }
}