static void
process_opts (int argc, char* argv[],
		const char* shortopts, struct option longopts[],
		GEN_PAR* pg, IN_PAR* pi, OUT_PAR* po)
{
int	c, i,j, longind;
char	*p, cdummy;

  while ((c=getopt_long(argc,argv, shortopts, longopts, &longind)) != EOF)
	switch (c)	/* Easy addition of options ... */
	{
	  case 'a':
		pi->aspectfactor = atof (optarg);
		if (pi->aspectfactor <= 0.0)
		{
			Eprintf("Aspect factor: %g illegal\n",
				pi->aspectfactor);
			exit(ERROR);
		}
		break;

	  case 'c':
		i = strlen(optarg);
		if ((i<1) || (i>8))
		{
			Eprintf("Invalid pencolor string: %s\n", optarg);
			exit(ERROR);
		}
		for (j=1, p = optarg; j <= i; j++, p++)
		{
		    switch (*p-'0')
		    {
			case xxBackground:pt.color[j] = xxBackground; break;
			case xxForeground:pt.color[j] = xxForeground; break;
			case xxRed:	  pt.color[j] = xxRed;	  break;
			case xxGreen:	  pt.color[j] = xxGreen;	  break;
			case xxBlue:	  pt.color[j] = xxBlue;	  break;
			case xxCyan:	  pt.color[j] = xxCyan;	  break;
			case xxMagenta:	  pt.color[j] = xxMagenta;  break;
			case xxYellow:	  pt.color[j] = xxYellow;	  break;
			default :
				  Eprintf(
				    "Invalid color of pen %d: %c\n", j, *p);
				  exit(ERROR);
		    }
		    if (pt.color[j] != xxBackground &&
			pt.color[j] != xxForeground)
				pg->is_color = TRUE;
		}
		pi->hwcolor=TRUE;
		break;

	  case 'C':
		pi->center_mode = TRUE;
		break;

	  case 'd':
		switch (po->dpi_x = atoi (optarg))
		{
		  case 75:
			break;
		  case 100:
		  case 150:
		  case 300:
		  case 600:
			if ((!pg->quiet) && (strcmp(pg->mode,"pcl")==0) &&
				po->specials == 0)
			Eprintf(
			  "Warning: DPI setting is no PCL level 3 feature!\n");
			break;
		  default:
			if ((!pg->quiet) && (strcmp(pg->mode,"pcl")==0))
			Eprintf(
			  "Warning: DPI value %d is invalid for PCL mode\n",
				po->dpi_x);
			break;
		}
		break;

	  case 'D':
		po->dpi_y = atoi (optarg);
		if ((!pg->quiet) && strcmp(pg->mode,"pcl")==0 && po->specials==0)
			Eprintf("Warning: %s\n",
			"Different DPI for x & y is invalid for PCL mode");
		break;

	  case 'F':
		po->formfeed = TRUE;
		break;

	  case 'f':
		po->outfile = optarg;
		break;

	  case 'h':
		pi->height = atof (optarg);
		if (pi->height < 0.1)
			Eprintf("Warning: Small height: %g mm\n", pi->height);
		if (pi->height > 300.0)
			Eprintf("Warning: Huge  height: %g mm\n", pi->height);
		break;

	  case 'i':
		po->init_p = TRUE;
		break;

	  case 'l':
		pg->logfile = optarg;
		if (freopen(pg->logfile, "w", stderr) == NULL)
		{
			PError ("Cannot open log file");
			Eprintf("Error redirecting stderr\n");
			Eprintf("Continuing with output to stderr\n");
		}
		else
			Logfile_flag = TRUE;
		break;

	  case 'm':
		pg->mode = optarg;
		for (i=0; ModeList[i].mode != XX_TERM; i++)
			if (strcmp(ModeList[i].modestr, pg->mode) == 0)
				break;
		if (ModeList[i].mode == XX_TERM)
		{
			Eprintf("'%s': unknown mode!\n", pg->mode);
			Eprintf("Supported are:\n\t");
			print_supported_modes();
			Send_Copyright();
		}
		break;

	  case 'n':
	  	pg->nofill = TRUE;
	  	break;

	  case 'N':
	  	pg->no_ps = TRUE;
	  	break;
	  		  	
	  case 'o':
		pi->xoff = atof (optarg);
		if (pi->xoff < 0.0)
		{
			Eprintf("Illegal X offset: %g < 0\n", pi->xoff);
			exit(ERROR);
		}
		if (pi->xoff > 210.0)	/* About DIN A4 width */
		{
			Eprintf("Illegal X offset: %g > 210\n", pi->xoff);
			exit(ERROR);
		}
		break;

	  case 'O':
		pi->yoff = atof (optarg);
		if (pi->yoff < 0.0)
		{
			Eprintf("Illegal Y offset: %g < 0\n", pi->yoff);
			exit(ERROR);
		}
		if (pi->yoff > 300.0)	/* About DIN A4 height */
		{
			Eprintf("Illegal Y offset: %g > 300\n", pi->yoff);
			exit(ERROR);
		}
		break;

	  case 'p':
		i = strlen(optarg);
		if ((i<1) || (i>8))
		{
			Eprintf("Invalid pensize string: %s\n", optarg);
			exit(ERROR);
		}
		for (j=1, p = optarg; j <= i; j++, p++)
		{
			if ((*p < '0') || (*p > '9'))
			{
				Eprintf("Invalid size of pen %d: %c\n",	j, *p);
				exit(ERROR);
			}
			pt.width[j] = *p - '0';
			if (pg->maxpensize < pt.width[j])
				pg->maxpensize = pt.width[j];
		}
		pi->hwsize=TRUE;
		break;

	  case 'P':
		if (*optarg == ':')
		{
			pi->first_page = 0;
			optarg++;
			if (sscanf(optarg,"%d", &pi->last_page) != 1)
				pi->last_page = 0;
		}
		else
			switch (sscanf(optarg,"%d%c%d",
				&pi->first_page, &cdummy, &pi->last_page))
			{
			  case 1:
				pi->last_page = pi->first_page;
				break;

			  case 2:
				if (cdummy == ':')
				{
					pi->last_page = 0;
					break;
				}
				/* not ':' Syntax error -- drop through	*/
			  case 3:
				if (cdummy == ':')
					break;
				/* not ':' Syntax error -- drop through	*/
			  default:
				Eprintf("Illegal page range.\n");
				usage_msg (pg, pi, po);
				exit(ERROR);
			}
		break;

	  case 'q':
		pg->quiet = TRUE;
		break;

	  case 'r':
		pi->rotation = atof(optarg);
		break;

	  case 'S':
		po->specials = atoi (optarg);
		break;

	  case 's':
		pg->swapfile = optarg;
		break;

	  case 't':
		pi->truesize = TRUE;
		break;

	  case 'V':
		po->vga_mode = atoi (optarg);
		break;

	  case 'w':
		pi->width = atof (optarg);
		if (pi->width < 0.1)
			Eprintf("Warning: Small width: %g mm\n", pi->width);
		if (pi->width > 300.0)
			Eprintf("Warning: Huge  width: %g mm\n", pi->width);
		break;

	  case 'v':
		Send_version();
		exit (NOERROR);

	  case 'x':
		pi->x0 = atof (optarg);
		break;

	  case 'X':
		pi->x1 = atof (optarg);
		break;

	  case 'y':
		pi->y0 = atof (optarg);
		break;

	  case 'Y':
		pi->y1 = atof (optarg);
		break;

	  case 'H':
	  case '?':
	  default:
		usage_msg (pg, pi, po);
		exit (ERROR);
	}
}