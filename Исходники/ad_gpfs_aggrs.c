/*
 * This is more general aggregator search function which does not base on the assumption
 * that each aggregator hosts the file domain with the same size
 */
int ADIOI_GPFS_Calc_aggregator(ADIO_File fd,
			      ADIO_Offset off,
			      ADIO_Offset min_off,
			      ADIO_Offset *len,
			      ADIO_Offset fd_size,
			      ADIO_Offset *fd_start,
			      ADIO_Offset *fd_end)
{
    int rank_index, rank;
    ADIO_Offset avail_bytes;
    TRACE_ERR("Entering ADIOI_GPFS_Calc_aggregator\n");

    ADIOI_Assert ( (off <= fd_end[fd->hints->cb_nodes-1] && off >= min_off && fd_start[0] >= min_off ) );

    /* binary search --> rank_index is returned */
    int ub = fd->hints->cb_nodes;
    int lb = 0;
    /* get an index into our array of aggregators */
    /* Common code for striping - bg doesn't use it but it's
       here to make diff'ing easier.
    rank_index = (int) ((off - min_off + fd_size)/ fd_size - 1);

    if (fd->hints->striping_unit > 0) {
        * wkliao: implementation for file domain alignment
           fd_start[] and fd_end[] have been aligned with file lock
	   boundaries when returned from ADIOI_Calc_file_domains() so cannot
	   just use simple arithmatic as above *
        rank_index = 0;
        while (off > fd_end[rank_index]) rank_index++;
    }
    bg does it's own striping below
    */
    rank_index = fd->hints->cb_nodes / 2;
    while ( off < fd_start[rank_index] || off > fd_end[rank_index] ) {
	if ( off > fd_end  [rank_index] ) {
	    lb = rank_index;
	    rank_index = (rank_index + ub) / 2;
	}
	else
	if ( off < fd_start[rank_index] ) {
	    ub = rank_index;
	    rank_index = (rank_index + lb) / 2;
	}
    }
    /* we index into fd_end with rank_index, and fd_end was allocated to be no
     * bigger than fd->hins->cb_nodes.   If we ever violate that, we're
     * overrunning arrays.  Obviously, we should never ever hit this abort */
    if (rank_index >= fd->hints->cb_nodes || rank_index < 0) {
        FPRINTF(stderr, "Error in ADIOI_Calc_aggregator(): rank_index(%d) >= fd->hints->cb_nodes (%d) fd_size=%lld off=%lld\n",
			rank_index,fd->hints->cb_nodes,fd_size,off);
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    /* DBG_FPRINTF ("ADIOI_GPFS_Calc_aggregator: rank_index = %d\n",
       rank_index ); */

    /*
     * remember here that even in Rajeev's original code it was the case that
     * different aggregators could end up with different amounts of data to
     * aggregate.  here we use fd_end[] to make sure that we know how much
     * data this aggregator is working with.
     *
     * the +1 is to take into account the end vs. length issue.
     */
    avail_bytes = fd_end[rank_index] + 1 - off;
    if (avail_bytes < *len && avail_bytes > 0) {
        /* this file domain only has part of the requested contig. region */

        *len = avail_bytes;
    }

    /* map our index to a rank */
    /* NOTE: FOR NOW WE DON'T HAVE A MAPPING...JUST DO 0..NPROCS_FOR_COLL */
    rank = fd->hints->ranklist[rank_index];
    TRACE_ERR("Leaving ADIOI_GPFS_Calc_aggregator\n");

    return rank;
}