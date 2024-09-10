void Expose_about_window(void)
{
    int	i, y, old_y, box_start, box_end, first, last;

    XClearWindow(dpy, aboutWindow);

    switch (about_page) {

    case 0:
	DrawShadowText(dpy, aboutWindow, textGC,
	BORDER, BORDER,
	"ABOUT XPILOT\n"
	"\n"
	"The game was conceived in its original form at the "
	"University of Tromsø (Norway) by Ken Ronny Schouten and "
	"Bjørn Stabell during the fall of 1991, but much of the game today "
	"is the result of hard efforts by Bert Gijsbers of the "
	"molecular cytology lab at the University of Amsterdam "
	"(The Netherlands).  "
	"Bert joined the team in the spring of 1993.\n"
	"\n"
	"Dick Balaska (Connecticut, USA) ported XPilot to Windows 95 and NT "
	"in the summer of 1996.\n"
	"\n"
	"A large number of features have been contributed by XPilot fans from "
	"all around the world.  See the CREDITS file for details.\n"
	"\n"
	"For more information, "
	"read the XPilot FAQ (Frequently Asked Questions).\n"
	"\n\n"
	"Good luck as a future xpilot,\n"
	"Bjørn Stabell, Ken Ronny Schouten, Bert Gijsbers & Dick Balaska",
	colors[WHITE].pixel, colors[BLACK].pixel);
	break;

    case 1:
	DrawShadowText(dpy, aboutWindow, textGC,
	BORDER, BORDER,
	"ABOUT XPILOT NG\n"
	"\n"
	"XPilot NG is an improved version of XPilot.\n\n"
	"For more info visit http://xpilot.sourceforge.net/ or\n"
	"read the man pages xpilot-ng-x11(6) and xpilot-ng-server(6).\n\n"
	"You can report any bug you find to <" PACKAGE_BUGREPORT ">.",
	colors[WHITE].pixel, colors[BLACK].pixel);
	break;

    case 2:
	DrawShadowText(dpy, aboutWindow, textGC,
	BORDER, BORDER,
	"GAME OBJECTIVE\n"
	"\n"
	"XPilot is a multi-player 2D space game.  "
	"Some features are borrowed from classics like the Atari coin-ups "
	"Asteroids and Gravitar, and the home-computer games "
	"Thrust (Commdore 64) and Gravity Force, but XPilot has many "
	"new features as well.\n"
	"\n"
	"The primary goal of the game is to collect points and increase "
	"your rating by destroying enemy fighters and cannons.  "
	"You are equipped with a machine gun when you start the game, "
	"but after a while you should have managed to collect some other "
	"fancy equipment.\n"
	"\n"
	"Another important task is to refuel your ship.  This is "
	"vital because your engine, radar, weapons and shields all "
	"require fuel.  Some even work better the more fuel you "
	"have aboard (mainly the radar).\n"
	"\n"
	"Optional modes include variations on this game play: "
	"you can play together in teams, you can disable shields "
	"(and all other equipment if you like), "
	"you can race against time and fellow players, and much much more.",
	colors[WHITE].pixel, colors[BLACK].pixel);
	break;

    case 3:
    case 4:
	if (about_page == 3) {
	    y = DrawShadowText(dpy, aboutWindow, textGC,
			   BORDER, BORDER,
			   "BONUS ITEMS\n"
			   "\n"
			   "Scattered around the world you might find some "
			   "of these red triangle objects.  They are "
			   "well worth picking up since they either improve "
			   "on the equipment you have, or they give you "
			   "new equipment.  If a fighter explodes, some of "
			   "its equipment might be found among the debris.",
			   colors[WHITE].pixel, colors[BLACK].pixel);
	    first = 0;
	    last = (itemsplit == -1) ? (NUM_ITEMS-1) : itemsplit;
	} else {
	    y = DrawShadowText(dpy, aboutWindow, textGC,
			   BORDER, BORDER,
			   "BONUS ITEMS CONTINUED\n",
			   colors[WHITE].pixel, colors[BLACK].pixel);
	    first = itemsplit+1;
	    last = (NUM_ITEMS-1);
	}

	y += BORDER;
	box_start = y;
	y += BORDER / 2;
	for (i = first; i <= last; i++) {

	    y += BORDER / 2;

	    /* Draw description text */
	    old_y = y;
	    y = DrawShadowText(dpy, aboutWindow, textGC,
			       5*BORDER + 2*ITEM_SIZE, old_y,
			       Item_get_text(i),
			       colors[WHITE].pixel, colors[BLACK].pixel);
	    if (y - old_y < 2 * ITEM_TRIANGLE_SIZE)
		y = old_y + 2 * ITEM_TRIANGLE_SIZE;
	    box_end = y + BORDER / 2;
	    if (i == last)
		box_end += BORDER / 2;

	    /* Paint the item on the left side */
	    XSetForeground(dpy, textGC, colors[BLACK].pixel);
	    XFillRectangle(dpy, aboutWindow, textGC,
			   BORDER, box_start,
			   2*ITEM_SIZE+2*BORDER,
			   (unsigned)box_end - box_start);
	    XSetForeground(dpy, textGC, colors[RED].pixel);
	    Gui_paint_item((u_byte)i, aboutWindow, textGC, 2*BORDER + ITEM_SIZE,
		       old_y + ITEM_TRIANGLE_SIZE);
	    XSetForeground(dpy, textGC, colors[WHITE].pixel);

	    /*
	     * Check for items overlapping button window, if so then
	     * remove this item, set itemsplit to previous item and
	     * stop adding more items.
	     */
	    if (about_page == 3
		&& itemsplit == -1
		&& box_end >= (ABOUT_WINDOW_HEIGHT - BORDER * 2 - 4
			       - (2*BTN_BORDER + buttonFont->ascent
				  + buttonFont->descent))) {
		itemsplit = i-1;
		XSetForeground(dpy, textGC, colors[windowColor].pixel);
		XFillRectangle(dpy, aboutWindow, textGC,
			       BORDER, box_start,
			       ABOUT_WINDOW_WIDTH,
			       (unsigned)box_end - box_start);
		XSetForeground(dpy, textGC, colors[WHITE].pixel);
		break;
	    }

	    y = box_end;
	    box_start = box_end;

	}
	/*
	 * No page split, obviously font is small enough or not enough
	 * items.
	 */
	if (about_page == 3 && itemsplit == -1)
	    itemsplit = NUM_ITEMS-1;
	break;

    default:
	error("Unkown page number %d\n", about_page);
	break;
    }
}