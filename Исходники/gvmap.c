static void 
init(int argc, char **argv, params_t* pm)
{
  char* cmd = argv[0];
  unsigned int c;
  real s;
  int v, r;
  char stmp[3];  /* two character string plus '\0' */

  pm->outfile = NULL;
  pm->opacity = NULL;
  pm->nrandom = -1;
  pm->dim = 2;
  pm->shore_depth_tol = 0;
  pm->highlight_cluster = 0;
  pm->useClusters = 0;
  pm->plotedges = 0;
  pm->whatout = 0;
  pm->show_points = 0;
  pm->color_scheme = COLOR_SCHEME_PASTEL; 
  pm->line_width = 0;
  pm->plot_label = NULL;
  pm->bg_color = NULL;
  pm->improve_contiguity_n = 0;
  pm->whatout = OUT_DOT;
  pm->nart = -1;
  pm->color_optimize = 1;
  pm->maxcluster = 0;
  pm->nedgep = 0;

  pm->cmd = cmd;
  pm->infiles = NULL;
  pm->line_color = N_NEW(10,char);
  strcpy(pm->line_color,"#000000");
  pm->include_OK_points = FALSE;
  pm->seed = 123;

  /*  bbox_margin[0] =  bbox_margin[1] = -0.2;*/
  pm->bbox_margin[0] =  pm->bbox_margin[1] = 0;

  opterr = 0;
  while ((c = getopt(argc, argv, ":evODko:m:s:r:p:c:C:l:b:g:t:a:h:z:d:")) != -1) {
    switch (c) {
    case 'm':
      if ((sscanf(optarg,"%lf",&s) > 0) && (s != 0)){
	    pm->bbox_margin[0] =  pm->bbox_margin[1] = s;
      } else {
        usage(cmd, 1);
      }
      break;
#if 0
    case 'q':
      if ((sscanf(optarg,"%d",&r) > 0) && r >=0 && r <=OUT_PROCESSING){
        pm->whatout = r;
      } else {
        usage(cmd,1);
      }
      break;
#endif
    case 's':
      if ((sscanf(optarg,"%lf",&s) > 0)){
        pm->shore_depth_tol = s;
      } else {
        usage(cmd,1);
      }
      break;
    case 'h':
      if ((sscanf(optarg,"%d",&v) > 0)){
        pm->nedgep = MAX(0, v);
      } else if (!strncmp(optarg, HLPFX, N_HLPFX) && (sscanf(optarg+N_HLPFX,"%d",&v) > 0)) {
        pm->highlight_cluster = MAX(0, v);
      } else {
        usage(cmd,1);
      }
      break;
     case 'r':
      if ((sscanf(optarg,"%d",&r) > 0)){
        pm->nrandom = r;
      }
      break;
    case 't':
      if ((sscanf(optarg,"%d",&r) > 0) && r > 0){
        pm->improve_contiguity_n = r;
      }
      break;
    case 'p':
      pm->show_points = 1;
      if ((sscanf(optarg,"%d",&r) > 0)){
        pm->show_points = MIN(3, r);
      }
      break;
    case 'k':
      pm->include_OK_points = TRUE;
      break;
    case 'v':
      Verbose = 1;
      break;
    case 'D':
      pm->useClusters = 1;
      break;
    case 'e':
      pm->plotedges = 1;
      break;
    case 'o':
	  pm->outfile = openFile(optarg, "w", pm->cmd);
      break;
    case 'O':
      pm->color_optimize = 0;
      break;
    case 'a':
      if ((sscanf(optarg,"%d",&r) > 0)){
	    pm->nart = r;
      } else {
	    usage(cmd,1);
      }
      break;
    case 'c':
      if (sscanf(optarg,"_opacity=%2s", stmp) > 0 && strlen(stmp) == 2){
        pm->opacity = strdup(stmp);
      } else if ((sscanf(optarg,"%d",&r) > 0) && r >= COLOR_SCHEME_NONE && r <= COLOR_SCHEME_GREY){
        pm->color_scheme = r;
      } else {
        usage(cmd,1);
      }
      break;
    case 'd':
      if (sscanf(optarg,"%d",&v) <= 0){
        usage(cmd,1);
      }
      else
        pm->seed = v;
      break;
    case 'C':
      if (!((sscanf(optarg,"%d",&v) > 0) && v >= 0)){
        usage(cmd,1);
      }
      else
        pm->maxcluster = v;
      break;
    case 'g': {
      gvcolor_t color;
      if (colorxlate(optarg, &color, RGBA_DOUBLE) == COLOR_OK) {
        if (!pm->bg_color) pm->bg_color = N_NEW(3,real);
        pm->bg_color[0] = color.u.RGBA[0];
        pm->bg_color[1] = color.u.RGBA[1];
        pm->bg_color[2] = color.u.RGBA[2];
      }
      break;
    }
    case 'z': {
      FREE (pm->line_color);
      pm->line_color = strdup (optarg);
      break;
    }
    case 'b':
      if (sscanf(optarg,"%lf",&s) > 0) {
        pm->line_width = s;
      } else {
        fprintf (stderr, "%s: unexpected argument \"%s\" for -b flag\n", cmd, optarg);
      }
      break;
    case 'l':
      if (pm->plot_label) free (pm->plot_label);
      pm->plot_label = strdup (optarg);
      break;
    case ':':
      fprintf(stderr, "gvpack: option -%c missing argument - ignored\n", optopt);
      break;
    case '?':
      if (optopt == '?')
        usage(cmd, 0);
      else {
        fprintf(stderr, " option -%c unrecognized - ignored\n", optopt);
        usage(cmd, 0);
      }
      break;
    }
  }

  argv += optind;
  argc -= optind;
  if (argc)
    pm->infiles = argv;
  if (!pm->outfile)
    pm->outfile = stdout;
}