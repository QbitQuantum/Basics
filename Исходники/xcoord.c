/*
 ****************************************************************
 *	Programa principal					*
 ****************************************************************
 */
void
main (int argc, const char *argv[])
{
	Display		*dp;
	Window		win;
	int		screen;
	ulong		fg, bg;
	GC		gc;
	XEvent		ev;
	Font		font;
	KeySym		key;
	char		text[80];
	int		doneflag, len, opt, exitval;

	/*
	 *	Inicializa opções.
	 */
	exitval = 0;

	/*
	 *	Analisa as opções de execução.
	 */
	while ((opt = getopt (argc, argv, "G:f:MH")) != EOF)
	{
		switch (opt)
		{
		    case 'M':
			exit (0);

		    case 'H':
			help (0);
			break;

		    case 'f':
			fontname = (char *)optarg;
			break;

		    case 'G':
			get_geometry (optarg);
			break;

		    default:
			putc ('\n', stderr);
			help (2);

		}	/* end switch (opt) */

	}	/* while ((opt = getopt (...))) */

	/*
	 *	Conecta-se ao servidor.
	 */
	if ((dp = XOpenDisplay (NULL)) == (Display *)NULL)
		msg ("$Não consegui conectar-me ao servidor");

	screen = DefaultScreen (dp);

	bg = WhitePixel (dp, screen);
	fg = BlackPixel (dp, screen);

	win =	XCreateSimpleWindow
		(	dp,
			DefaultRootWindow (dp), 
			x, y, dx, dy,
			2,
			fg, bg			/* cores: frente e fundo */
		);

	gc = DefaultGC (dp, screen);

	if (fontname != NOSTR)
	{
		if (font = XLoadFont (dp, fontname))
			XSetFont (dp, gc, font);
	}

	XSelectInput (dp, win, ButtonPressMask|KeyPressMask|ExposureMask);

	XMapRaised (dp, win);

	for (doneflag = 0; doneflag == 0; /* sem incremento */)
	{
		XNextEvent (dp, &ev);

		switch (ev.type)
		{
		    case Expose:
			break;

		    case ButtonPress:
			sprintf
			(	text,
#if (0)	/****************************************************/
				"(%d, %d), (%d, %d)",
				ev.xbutton.x_root, ev.xbutton.y_root,
#endif	/****************************************************/
				"(%d, %d)",
				ev.xbutton.x, ev.xbutton.y
			);

			XDrawImageString
			(	dp, win, gc,
				ev.xbutton.x, ev.xbutton.y,
				text, strlen (text)
			);

			break;

		    case KeyPress:
			len = XLookupString (&ev.xkey, text, 10, &key, 0);

			if (len == 1 && text[0] == 'q')
				doneflag++;
			break;
		}
	}


	XDestroyWindow (dp, win);
	XCloseDisplay (dp);

	exit (0);

}	/* end main */