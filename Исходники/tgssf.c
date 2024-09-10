int main(int argc, char **argv)
   {int i, k, l, nt, fast;
    int maxes[2], X_max, Y_max, n_pts, use_color, palette;
    double x, y, dx, dy, theta, phi, dp;
    char t[MAXLINE], *token, *emap;
    PG_rendering pty;
    PG_device *SCR_dev, *PS_mdev, *CGM_mdev, *PS_cdev, *CGM_cdev;
    double *rx, *ry, *rz, *rs, *px, *py, *pz, *ps, *ext;
    pcons *alist;
    char *palettes[] = {"spectrum", "rainbow", "bw"};

    X_max     = N_POINTS;
    Y_max     = N_POINTS;
    palette   = 0;
    use_color = FALSE;
    pty      = PLOT_WIRE_MESH;
    dp        = 0.0;
    nt        = 1;
    fast      = FALSE;
    for (i = 1; i < argc; i++)
        {if (argv[i][0] == '-')
            {switch (argv[i][1])
                {case 'c' :
		      use_color = TRUE;
		      break;
                 case 'd' :
		      dp = ATOF(argv[++i]);
		      break;
                 case 'f' :
		      fast = TRUE;
		      break;
                 case 'h' :
		      print_help();
		      return(1);
                 case 'n' :
		      nt = atoi(argv[++i]);
		      break;
                 case 'p' :
		      palette = atoi(argv[++i]);
		      break;
                 case 's' :
		      pty = PLOT_SURFACE;
		      break;
                 case 'w' :
		      pty = PLOT_WIRE_MESH;
		      break;
                 case 'z' :
		      X_max = Y_max = atoi(argv[++i]);
		      break;};}

         else
            break;};

    SC_init_threads(nt, NULL);

    maxes[0] = X_max;
    maxes[1] = Y_max;
    n_pts    = X_max*Y_max;

    emap = CMAKE_N(char, n_pts);
    memset(emap, 1, n_pts);
    alist = PG_set_attrs_alist(NULL,
			      "EXISTENCE", G_CHAR_I, TRUE, emap,
			      NULL);

    PG_open_console("TGSSF", "MONOCHROME", 1,
                    0.55, 0.1, 0.4, 0.8);

    if (use_color)
       SCR_dev = PG_make_device("WINDOW", "COLOR", "PGS Surface Test");
    else
       SCR_dev = PG_make_device("WINDOW", "MONOCHROME", "PGS Surface Test");
/*    PG_open_device(SCR_dev, 0.1, 0.1, 0.02, 0.02); */
    PG_open_device(SCR_dev, 0.1, 0.1, 0.4, 0.4);

    if (pty == PLOT_SURFACE)
       PG_fset_palette(SCR_dev, palettes[palette]);

    if (fast)
       {PS_cdev  = PG_make_device("PS", "COLOR", "tgssf-c");
	CGM_cdev = PG_make_device("CGM", "COLOR", "tgssf-c");
	PS_mdev  = PG_make_device("PS", "MONOCHROME", "tgssf-m");
	CGM_mdev = PG_make_device("CGM", "MONOCHROME", "tgssf-m");

	PG_open_device(PS_cdev, 0.0, 0.0, 0.0, 0.0);
	PG_open_device(CGM_cdev, 0.0, 0.0, 0.0, 0.0);
	PG_open_device(PS_mdev, 0.0, 0.0, 0.0, 0.0);
	PG_open_device(CGM_mdev, 0.0, 0.0, 0.0, 0.0);

	if (pty == PLOT_SURFACE)
	   {PG_fset_palette(PS_mdev, palettes[palette]);
	    PG_fset_palette(CGM_mdev, palettes[palette]);
	    PG_fset_palette(PS_cdev, palettes[palette]);
	    PG_fset_palette(CGM_cdev, palettes[palette]);};};

    rx = px = CMAKE_N(double, n_pts);
    ry = py = CMAKE_N(double, n_pts);
    rz = pz = CMAKE_N(double, n_pts);

    if (pty == PLOT_SURFACE)
       rs = ps = CMAKE_N(double, n_pts);
    else