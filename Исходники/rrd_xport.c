int 
rrd_xport(int argc, char **argv, int UNUSED(*xsize),
	  time_t         *start,
	  time_t         *end,        /* which time frame do you want ?
				       * will be changed to represent reality */
	  unsigned long  *step,       /* which stepsize do you want? 
				       * will be changed to represent reality */
	  unsigned long  *col_cnt,    /* number of data columns in the result */
	  char           ***legend_v, /* legend entries */
	  rrd_value_t    **data)      /* two dimensional array containing the data */

{

    image_desc_t   im;
    time_t	   start_tmp=0,end_tmp=0;
    struct rrd_time_value start_tv, end_tv;
    char           *parsetime_error = NULL;
    optind = 0; opterr = 0;  /* initialize getopt */

    rrd_graph_init(&im);

    parsetime("end-24h", &start_tv);
    parsetime("now", &end_tv);

    while (1){
	static struct option long_options[] =
	{
	    {"start",      required_argument, 0,  's'},
	    {"end",        required_argument, 0,  'e'},
	    {"maxrows",    required_argument, 0,  'm'},
	    {"step",       required_argument, 0,   261},
	    {0,0,0,0}
	};
	int option_index = 0;
	int opt;
	
	opt = getopt_long(argc, argv, "s:e:m:",
			  long_options, &option_index);

	if (opt == EOF)
	    break;
	
	switch(opt) {
	case 261:
	    im.step =  atoi(optarg);
	    break;
	case 's':
	    if ((parsetime_error = parsetime(optarg, &start_tv))) {
	        rrd_set_error( "start time: %s", parsetime_error );
		return -1;
	    }
	    break;
	case 'e':
	    if ((parsetime_error = parsetime(optarg, &end_tv))) {
	        rrd_set_error( "end time: %s", parsetime_error );
		return -1;
	    }
	    break;
	case 'm':
	    im.xsize = atol(optarg);
	    if (im.xsize < 10) {
		rrd_set_error("maxrows below 10 rows");
		return -1;
	    }
	    break;
	case '?':
	    rrd_set_error("unknown option '%c'", optopt);
            return -1;
	}
    }

    if (proc_start_end(&start_tv,&end_tv,&start_tmp,&end_tmp) == -1){
	return -1;
    }  
    
    if (start_tmp < 3600*24*365*10){
	rrd_set_error("the first entry to fetch should be after 1980 (%ld)",start_tmp);
	return -1;
    }
    
    if (end_tmp < start_tmp) {
	rrd_set_error("start (%ld) should be less than end (%ld)", 
	       start_tmp, end_tmp);
	return -1;
    }
    
    im.start = start_tmp;
    im.end = end_tmp;
    im.step = max((long)im.step, (im.end-im.start)/im.xsize);
    
    rrd_graph_script(argc,argv,&im,0);
    if (rrd_test_error()) {
	im_free(&im);
	return -1;
    }

    if (im.gdes_c == 0){
	rrd_set_error("can't make a graph without contents");
	im_free(&im);
	return(-1); 
    }
    
    if (rrd_xport_fn(&im, start, end, step, col_cnt, legend_v, data) == -1){
	im_free(&im);
	return -1;
    }

    im_free(&im);
    return 0;
}