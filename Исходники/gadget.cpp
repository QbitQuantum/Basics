// loads nframes bitmaps, starting at index start_frame.
// anything < start_frame will not be loaded.
// this keeps the loading code from trying to load bitmaps which don't exist
// and taking an unnecessary disk hit.		
int UI_GADGET::set_bmaps(char *ani_fname, int nframes, int start_frame)
{
	int first_frame, i;	
	char full_name[MAX_FILENAME_LEN] = "";
	char tmp[33];
	int idx, s_idx;	
	int num_digits;
	int its_all_good = 0;
	
	// clear out all frames
	for(idx=0; idx<MAX_BMAPS_PER_GADGET; idx++){
		bmap_ids[idx] = -1;
	}
	
	// load all the bitmaps
	bm_filename = ani_fname;

	Assertion(nframes < MAX_BMAPS_PER_GADGET, "Too many frames specified (%d), must be less than MAX_BMAPS_PER_GADGET", nframes);
	m_num_frames = nframes;
	for(idx=start_frame; idx<nframes; idx++){
		// clear the string
		strcpy_s(full_name, "");

		// get the # of digits for this index
		num_digits = (idx < 10) ? 1 : (idx < 100) ? 2 : (idx < 1000) ? 3 : 4;

		// build the actual filename
		strcpy_s(full_name, ani_fname);
		for(s_idx=0; s_idx<(4-num_digits); s_idx++){
			strcat_s(full_name, NOX("0"));
		}
		sprintf(tmp, "%d", idx);
		strcat_s(full_name, tmp);

		// try and load the bitmap				
		bmap_ids[idx] = bm_load(full_name);	
		if(bmap_ids[idx] != -1){		
			
			its_all_good = 1;
		} 
	}

	// done
	if(its_all_good){
		uses_bmaps = 1;		
		return 0;
	}

	// no go, so try and load as an ani. try and load as an .ani	
	first_frame = bm_load_animation(ani_fname, &m_num_frames);	
	if((first_frame >= 0) && (m_num_frames <= MAX_BMAPS_PER_GADGET)){					
		// seems pretty stupid that we didn't just use a variable for the first frame and access all
		// other frames offset from it instead of accessing this bmap_ids[] array, but probably too
		// much trouble to go through and change this anymore.  How sad..
		for ( i=0; i<m_num_frames; i++ ) {
			bmap_ids[i] = first_frame + i;
		}	
	}	

	// flag that this control is using bitmaps for art	
	uses_bmaps = 1;
	return 0;
}