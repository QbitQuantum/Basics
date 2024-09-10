int ms_pack_int 
   (DATA_HDR	*hdr0,		/* ptr to initial data hdr.		*/
    BS		*init_bs,	/* ptr to onetime blockettes.		*/
    int		*data,		/* ptr to data buffer.			*/
    int		num_samples,	/* number of data samples.		*/
    int		*n_blocks,	/* # miniSEED blocks (returned).	*/
    char	**pp_ms,	/* ptr **miniSEED (returned).		*/
    int		ms_len,		/* miniSEED buffer len (if supplied).	*/
    char	*p_errmsg)	/* ptr to error msg buffer.		*/
{
    DATA_HDR *hdr;		/* data header used for writing miniSEED*/
    char *p_ms;			/* ptr to current miniSEED block.	*/
    void *p_packed;		/* ptr to packed output data.		*/
    char errmsg[256];		/* error msg buffer.			*/
    int ipt;			/* index of data to pack.		*/
    int nblks_malloced;		/* # of miniSEED output blocks malloced.*/
    int num_blocks;		/* # of miniSEED block created.		*/
    int samples_remaining;	/* # samples left to cvt to miniseed.	*/
    int nsamples;		/* # of samples in miniSEED block.	*/
    int max_bytes;		/* max # of data bytes in record.	*/
    int nbytes;			/* # of bytes packed into record.	*/
    int seconds, usecs;		/* seconds and usecs for time calcs.	*/
    int pad;			/* flag to indicate padding of frames.	*/
    int blksize = hdr0->blksize;/* output blksize.			*/

    /* Initialization.							*/
    *n_blocks = 0;

    /* Check for invalid arguments.					*/
    if (num_samples <= 0) return(MS_ERROR);
    if (blksize < 128 ||
	(blksize != (int)pow(2.0,rint(log2((double)blksize))))) {
	sprintf (errmsg, "Warning: invalid blksize: %d\n", blksize);
	if (p_errmsg) strcpy(p_errmsg, errmsg);
	else fprintf (stderr, errmsg);
	return (MS_ERROR);
    }

    /* If *pp_ms != NULL, assume that the caller is providing sufficient*/
    /* memory to hold all of the resulting miniSEED records.		*/
    /* If it is NULL, we allocate the space, and set it to point to the	*/
    /* allocated miniSEED records.					*/
    /* If we allocated the space for the miniSEED, the caller is	*/
    /* responsible for freeing the space.				*/
    if (*pp_ms) nblks_malloced = -1;
    else nblks_malloced = 0;

    /* Create a copy of the initial data_hdr for our use.		*/
    /* We will update this each time we create a miniSEED block.	*/
    hdr = dup_data_hdr (hdr0);
    if (hdr == NULL) {
	return (MS_ERROR);
    }

    /* Start compressor.						*/
    num_blocks = 0;
    samples_remaining = num_samples;
    ipt = 0;
    pad = 1;

    while (samples_remaining) {
	/* Check for available space.					*/
	/* Allocate more space for Mini-SEED blocks if necessary.	*/
	if (nblks_malloced < 0) {
	    if (ms_len < blksize) {
		*n_blocks = num_blocks;
		free_data_hdr (hdr);
		return (num_samples - samples_remaining);
	    }
	    ms_len -= blksize;
	}
	if (nblks_malloced >= 0 && num_blocks == nblks_malloced) {
	    *pp_ms = (*pp_ms == NULL) ?
		(char *)malloc((nblks_malloced+MALLOC_INCREMENT)*blksize) :
		(char *)realloc(*pp_ms,(nblks_malloced+MALLOC_INCREMENT)*blksize);
	    if (*pp_ms == NULL) {
		sprintf (errmsg, "Error mallocing miniSEED buffer\n");
		if (p_errmsg) strcpy(p_errmsg, errmsg);
		else fprintf (stderr, errmsg);	    
		free_data_hdr (hdr);
		return (QLIB2_MALLOC_ERROR);
	    }
	    nblks_malloced += MALLOC_INCREMENT;
	}

	/* Initialize the next fixed data header.			*/
	p_ms = *pp_ms + (num_blocks * blksize);
	if (init_miniseed_hdr ((SDR_HDR *)p_ms, hdr, init_bs) < 0) {
	    sprintf (errmsg, "Error: initializing MiniSEED header");
	    if (p_errmsg) strcpy(p_errmsg, errmsg);
	    else fprintf (stderr, errmsg);	    
	    free_data_hdr (hdr);
	    if (nblks_malloced > 0) free(*pp_ms);
	    return (MS_ERROR);
	}
	    
	init_bs = NULL;
	p_packed = (void *)(p_ms + hdr->first_data);
	max_bytes = blksize + 1 - hdr->first_data;

	/* Pack the rest of the miniSEED record with data.		*/
	switch (hdr->data_type) {
	  case INT_32:
	    pack_int_32 ((int *)p_packed, &data[ipt], samples_remaining, 
			 max_bytes, pad, hdr->data_wordorder, &nbytes, &nsamples);
	    break;
	  case INT_24:
	    pack_int_24 ((unsigned char *)p_packed, &data[ipt], samples_remaining, 
			 max_bytes, pad, hdr->data_wordorder, &nbytes, &nsamples);
	    break;
	  case INT_16:
	    pack_int_16 ((short int *)p_packed, &data[ipt], samples_remaining, 
			 max_bytes, pad, hdr->data_wordorder, &nbytes, &nsamples);
	    break;
	}

	/* End of data or Mini-SEED block is full.			*/
	/* Update Mini-SEED header with:				*/
	/*	final sample count.					*/
	/* Update hdr for the next record.				*/
	hdr->num_samples = nsamples;
	update_miniseed_hdr ((SDR_HDR *)p_ms, hdr);
	ms_pack_update_hdr (hdr, 1, nsamples, &data[ipt]);
	ipt += nsamples;
	samples_remaining -= nsamples;
	++num_blocks;
	hdr->num_samples = 0;
    }

    /* Cleanup.								*/
    free_data_hdr (hdr);
    *n_blocks = num_blocks;
    ms_pack_update_return_hdr (hdr0, num_blocks, num_samples, data);
    return(num_samples);
}