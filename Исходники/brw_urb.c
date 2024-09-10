/* Most minimal update, forces re-emit of URB fence packet after GS
 * unit turned on/off.
 */
static void recalculate_urb_fence( struct brw_context *brw )
{
   GLuint csize = brw->curbe.total_size;
   GLuint vsize = brw->vs.prog_data->base.urb_entry_size;
   GLuint sfsize = brw->sf.prog_data->urb_entry_size;

   if (csize < limits[CS].min_entry_size)
      csize = limits[CS].min_entry_size;

   if (vsize < limits[VS].min_entry_size)
      vsize = limits[VS].min_entry_size;

   if (sfsize < limits[SF].min_entry_size)
      sfsize = limits[SF].min_entry_size;

   if (brw->urb.vsize < vsize ||
       brw->urb.sfsize < sfsize ||
       brw->urb.csize < csize ||
       (brw->urb.constrained && (brw->urb.vsize > vsize ||
				 brw->urb.sfsize > sfsize ||
				 brw->urb.csize > csize))) {


      brw->urb.csize = csize;
      brw->urb.sfsize = sfsize;
      brw->urb.vsize = vsize;

      brw->urb.nr_vs_entries = limits[VS].preferred_nr_entries;	
      brw->urb.nr_gs_entries = limits[GS].preferred_nr_entries;	
      brw->urb.nr_clip_entries = limits[CLP].preferred_nr_entries;
      brw->urb.nr_sf_entries = limits[SF].preferred_nr_entries;	
      brw->urb.nr_cs_entries = limits[CS].preferred_nr_entries;	

      brw->urb.constrained = 0;

      if (brw->gen == 5) {
         brw->urb.nr_vs_entries = 128;
         brw->urb.nr_sf_entries = 48;
         if (check_urb_layout(brw)) {
            goto done;
         } else {
            brw->urb.constrained = 1;
            brw->urb.nr_vs_entries = limits[VS].preferred_nr_entries;
            brw->urb.nr_sf_entries = limits[SF].preferred_nr_entries;
         }
      } else if (brw->is_g4x) {
	 brw->urb.nr_vs_entries = 64;
	 if (check_urb_layout(brw)) {
	    goto done;
	 } else {
	    brw->urb.constrained = 1;
	    brw->urb.nr_vs_entries = limits[VS].preferred_nr_entries;
	 }
      }

      if (!check_urb_layout(brw)) {
	 brw->urb.nr_vs_entries = limits[VS].min_nr_entries;	
	 brw->urb.nr_gs_entries = limits[GS].min_nr_entries;	
	 brw->urb.nr_clip_entries = limits[CLP].min_nr_entries;
	 brw->urb.nr_sf_entries = limits[SF].min_nr_entries;	
	 brw->urb.nr_cs_entries = limits[CS].min_nr_entries;	

	 /* Mark us as operating with constrained nr_entries, so that next
	  * time we recalculate we'll resize the fences in the hope of
	  * escaping constrained mode and getting back to normal performance.
	  */
	 brw->urb.constrained = 1;
	
	 if (!check_urb_layout(brw)) {
	    /* This is impossible, given the maximal sizes of urb
	     * entries and the values for minimum nr of entries
	     * provided above.
	     */
	    fprintf(stderr, "couldn't calculate URB layout!\n");
	    exit(1);
	 }
	
	 if (unlikely(INTEL_DEBUG & (DEBUG_URB|DEBUG_PERF)))
	    fprintf(stderr, "URB CONSTRAINED\n");
      }

done:
      if (unlikely(INTEL_DEBUG & DEBUG_URB))
	 fprintf(stderr,
                 "URB fence: %d ..VS.. %d ..GS.. %d ..CLP.. %d ..SF.. %d ..CS.. %d\n",
                 brw->urb.vs_start,
                 brw->urb.gs_start,
                 brw->urb.clip_start,
                 brw->urb.sf_start,
                 brw->urb.cs_start,
                 brw->urb.size);

      brw->state.dirty.brw |= BRW_NEW_URB_FENCE;
   }
}