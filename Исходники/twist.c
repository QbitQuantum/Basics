main()
{
	int i;
	Point savept;

        /*
        ** Use "lprintf" to move the "current screen point"
        ** and set a position at which to display the
        ** image of the world.
        */
	lprintf("\n         ");
	savept = sPtCurrent();

	lprintf("\n  Hello        !");

	for (i=0; 1 ; i++) {
		/*
		** after the 18th Bitmap, go back to Bitmap zero.
		*/
		if(i==18)
			i=0;

		/*
		** Draw the current Bitmap of the world.
		*/
		bitblt(world[i], world[i]->rect, &display, savept, F_XOR);

		/*
		** Release the CPU for 10 ticks of the
		** 60 Hz system clock.
		*/
		sleep(10);

		/*
		** Erase the current Bitmap of the world in
		** preparation for drawing the next.
		*/
		bitblt(world[i], world[i]->rect, &display, savept, F_XOR);

	}
}