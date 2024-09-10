int PPF_Print( MPI_Comm comm, const char * string, ... )
{
    va_list		args;

    static int	inited;
    static MPI_Op	PTC_Print_reduce;
    static size_t	linesize, blocksize;
    static MPI_Datatype	type;
    static char *	src_block;
    static char *	dest_block;
    static int	rank, size;

    int 		i;
    int		localrank;
    int 		status;
    LineData *	src_lines;
    LineData *	dest_lines;
    LineData *	pline;
    char *		ptoken, * plast;
    char		temp[PPF_MAXLINE];

    if( !inited ) {
        status = MPI_Op_create( PrintReduceOp, 1, &PTC_Print_reduce );
#ifdef _MSC_VER
        _set_printf_count_output(1);
#endif
        if( status != MPI_SUCCESS ) {
            fprintf( stderr, "Couldn't create Print Reduce op %d\n",
                     status );
            return status;
        }

        /* Use comm world so that output is identified in terms of
         * global rank.  (Should this be optional?)
         */
        MPI_Comm_rank( MPI_COMM_WORLD, &rank );
        MPI_Comm_size( MPI_COMM_WORLD, &size );

        /* Get enough memory to hold size line entries +
         * count field + and linesize field
         */
        linesize = CLOSED_SET_BYTES( size ) + PPF_MAXLINE;
        blocksize = linesize * size + 2 * sizeof(int);

        src_block = malloc( blocksize );
        dest_block = malloc( blocksize );

        /* Store the number of entries and linesize (since set size
         * varies from run to run)
         */
        ((int*)src_block)[0] = size;
        ((int*)src_block)[1] = linesize;

        MPI_Type_contiguous( blocksize, MPI_BYTE, &type );
        MPI_Type_commit( &type );

        inited = 1;
    }

    /* Initialize the line entries */
    src_lines = (LineData *)(src_block + 2 * sizeof(int));
    dest_lines = (LineData *)(dest_block + 2 * sizeof(int));

#if 0
    /* Truncate the string if necessary */
    if( strlen( string ) >= PPF_MAXLINE ) {
        string[PPF_MAXLINE - 1] = '\0';
    }
#endif

    /* Search for the pattern that means "put the node numbers here".
     * Since it will begin with at %, we have to convert it to
     * something else so sprintf doesn't try to interpret it.  When
     * we finally do the printout, we'll replace the placeholder
     * with the node list.  Likewise, since we're processing
     * this string twice through printf-like functions, any %%
     * patterns the user put in will get eaten up.  To prevent
     * that, we change %% to something else before the first
     * pass through sprintf and change it back before the second.
     */

    if( string != NULL ) {	/* Don't try formatting an empty string */
        /* First copy into a buffer that we can modify */
        strncpy( temp, string, PPF_MAXLINE );
        temp[PPF_MAXLINE-1] = '\0';

        for( ptoken = strchr( temp, '%' );
                ptoken != NULL;
                ptoken = strchr( ptoken + 2, '%' ) ) {
            if( ptoken[1] == NODECHAR ) {
                *ptoken = PERCENTSUB;
                ptoken[1] = NODESUB;
            } else if( ptoken[1] == '%' ) {
                *ptoken = ptoken[1] = PERCENTSUB;
            }
        }
    }

    /* Initialize all the strings and sets in our list to be
     * empty, except the one for this node.  That gets
     * initialized with the formatted string that the user
     * requested and the nodeset consisting of this node.
     */
    va_start( args, string );
    for( pline = src_lines, i = 0; i < size;
            pline += linesize, i++ ) {
        InitSet( size, pline+SET );
        if( i == rank ) {
            if( string != NULL ) {
                vsprintf( pline+TEXT, temp, args );
                AddSet( pline+SET, rank );
            }
            /* If string is NULL, this node won't appear in
             * the set for any string entry, so it won't
             * produce any output.
             */
        }
    }
    va_end( args );


    MPI_Reduce( src_block, dest_block, 1, type, PTC_Print_reduce, 0, comm );

    /* For this test, we use to input comm rank so that we're sure
     * "node 0" is in this group.
     */
    MPI_Comm_rank( comm, &localrank );
    if( localrank == 0 ) {
        PrintResult( dest_lines, size, linesize );
    }

    return MPI_SUCCESS;
}