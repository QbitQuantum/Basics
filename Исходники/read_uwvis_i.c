/*
 * Scan the named file, createing a grid_info struct for each grid.  Store
 * the grid_info structs in the grid data base.
 * Input:  name - name of UW VIS file.
 *         db - the grid data base
 * Return:  number of grids found.
 */
int get_uwvis_info( char *name, struct grid_db *db )
{
    static int init_flag = 0;
    FILE *f;
    int grids = 0;
    int var, numvars, nr, nc, nl;
    float height[MAXLEVELS];
    char ch;
    int i, vcs;

    if (init_flag==0) {
        init_visreader();
        init_flag = 1;
    }


    /* Open the file */
    f = fopen( name, "r" );
    if (!f) {
        return 0;
    }

    fscanf( f, "%d", &numvars );
    if (numvars>MAXVARS) {
        printf("ERROR: %s contains too many variables, limit is %d\n",
               name, MAXVARS );
    }

    /* grid size */
    fscanf( f, "%d", &nc );
    fscanf( f, "%d", &nr );
    fscanf( f, "%d", &nl );
    (void) getc(f);  /* get '\n' */

    /* this is tricky:
     * We look at the next character:
     * if it's a letter then
     *     we read the variable name and extract the height info from header
     * else
     *     read the height values for each grid level (variable delta Z).
     * endif
     */
    ch = getc(f);
    ungetc(ch, f);

    if (isalpha(ch)) {
        vcs = 1;
    }
    else {
        /* Read the height (in meters) of each grid level */
        for (i=0; i<nl; i++) {
            fscanf( f, "%8f", &height[i] );
            height[i] /= 1000.0;    /* convert from meters to km */
        }
        (void) getc(f);  /* get '\n' */
        vcs = 2;
    }


    for (var=0; var<numvars; var++) {
        int *header, header_size;
        char varname[100];
        struct grid_info *info;
        float args[100];

        /* read variable name */
        fgets( varname, 40, f );
        for (i=7; i>=0 && varname[i]==' '; i--) {
            varname[i] = '\0';
        }
        varname[8] = 0;

        /* read data header */
        header = read_int_block( f, &header_size );


        /*
         * Allocate grid info struct and initialize it.
         */
        info = alloc_grid_info();

        /* 01Feb06  Phil McDonald */
        info->FileName = TMP_STRDUP (name);
        /* end PM */
        info->Format = FILE_UWVIS;
        info->Position = ftell(f);    /* save position of data in file */

        info->Nr = nr;
        info->Nc = nc;
        info->Nl = nl;

        info->DateStamp = header[5];
        info->TimeStamp = header[6];
        /* 01Feb06  Phil McDonald */
        info->VarName = TMP_STRDUP (varname);
        /* end PM */

        args[0] = (float) header[22] / 10000.0;
        args[1] = (float) header[23] / 10000.0;
        args[2] = (float) header[24] / 10000.0;
        args[3] = (float) header[25] / 10000.0;
        info->Proj = new_projection( db, PROJ_LINEAR, nr, nc, args );

        if (vcs==1) {
            /* equally spaced km */
            float tophgt = (float) header[31] / 1000.0;
            float hgtinc = (float) header[32] / 1000.0;
            args[0] = tophgt - hgtinc*(nl-1);
            args[1] = hgtinc;
        }
        else {
            /* vcs==2 */
            /* unequally spaced km */
            memcpy( args, height, sizeof(float)*nl );
        }
        info->Vcs = new_vcs( db, vcs, nl, 0, args );

        /*
         * done with this grid
         */
        append_grid( info, db );
        grids++;

        /* 01Feb06  Phil McDonald */
        TMP_FREE (header);
        /* end PM */

#ifdef LEAVEOUT
        {
            float *data;
            int data_size;
            /* read and skip data */
            data = read_float_block( f, &data_size );
            /* 01Feb06  Phil McDonald */
            TMP_FREE (data);
            /* end PM */
        }
#else
        skip_float_block( f );
#endif
    }

    fclose(f);

    return grids;
}