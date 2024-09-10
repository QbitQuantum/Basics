int
main(int argc, char *argv[])
{
	fz_context *ctx;
	FILE *script = NULL;
	int c;

	while ((c = fz_getopt(argc, argv, "o:p:v")) != -1)
	{
		switch(c)
		{
		case 'o': output = fz_optarg; break;
		case 'p': prefix = fz_optarg; break;
		case 'v': verbosity ^= 1; break;
		default: usage(); break;
		}
	}

	if (fz_optind == argc)
		usage();

	ctx = fz_new_context(NULL, NULL, FZ_STORE_DEFAULT);
	if (!ctx)
	{
		fprintf(stderr, "cannot initialise context\n");
		exit(1);
	}
	pdfapp_init(ctx, &gapp);
	gapp.scrw = 640;
	gapp.scrh = 480;
	gapp.colorspace = fz_device_rgb(ctx);

	fz_try(ctx)
	{
		while (fz_optind < argc)
		{
			scriptname = argv[fz_optind++];
			script = fopen(scriptname, "rb");
			if (script == NULL)
				fz_throw(ctx, FZ_ERROR_GENERIC, "cannot open script: %s", scriptname);

			do
			{
				char *line = my_getline(script);
				if (line == NULL)
					continue;
				if (verbosity)
					fprintf(stderr, "'%s'\n", line);
				if (match(&line, "%"))
				{
					/* Comment */
				}
				else if (match(&line, "PASSWORD"))
				{
					strcpy(pd_password, line);
				}
				else if (match(&line, "OPEN"))
				{
					char path[1024];
					if (file_open)
						pdfapp_close(&gapp);
					strcpy(filename, line);
					if (prefix)
					{
						sprintf(path, "%s%s", prefix, line);
					}
					else
					{
						strcpy(path, line);
					}
					pdfapp_open(&gapp, path, 0);
					file_open = 1;
				}
				else if (match(&line, "GOTO"))
				{
					pdfapp_gotopage(&gapp, atoi(line)-1);
				}
				else if (match(&line, "SCREENSHOT"))
				{
					char text[1024];

					sprintf(text, output, ++shotcount);
					if (strstr(text, ".pgm") || strstr(text, ".ppm") || strstr(text, ".pnm"))
						fz_save_pixmap_as_pnm(ctx, gapp.image, text);
					else
						fz_save_pixmap_as_png(ctx, gapp.image, text, 0);
				}
				else if (match(&line, "RESIZE"))
				{
					int w, h;
					sscanf(line, "%d %d", &w, &h);
					pdfapp_onresize(&gapp, w, h);
				}
				else if (match(&line, "CLICK"))
				{
					float x, y, b;
					int n;
					n = sscanf(line, "%f %f %f", &x, &y, &b);
					if (n < 1)
						x = 0.0f;
					if (n < 2)
						y = 0.0f;
					if (n < 3)
						b = 1;
					/* state = 1 = transition down */
					pdfapp_onmouse(&gapp, (int)x, (int)y, b, 0, 1);
					/* state = -1 = transition up */
					pdfapp_onmouse(&gapp, (int)x, (int)y, b, 0, -1);
				}
				else if (match(&line, "TEXT"))
				{
					unescape_string(td_textinput, line);
				}
				else
				{
					fprintf(stderr, "Unmatched: %s\n", line);
				}
			}
			while (!feof(script));

			fclose(script);
		}
	}
	fz_catch(ctx)
	{
		fprintf(stderr, "error: cannot execute '%s'\n", scriptname);
	}

	if (file_open)
		pdfapp_close(&gapp);

	fz_drop_context(ctx);

	return 0;
}