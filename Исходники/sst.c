static void makemoves(void) {
	int i, hitme;
	char ch;
	while (TRUE) { /* command loop */
		hitme = FALSE;
		justin = 0;
		Time = 0.0;
		i = -1;
		while (TRUE)  { /* get a command */
			chew();
			skip(1);
			proutn("COMMAND> ");
      // Use of scan() here (after chew) will get a new line of input
      // and will return IHEOL iff new line of input contains nothing
      // or a numeric input is detected but conversion fails.
			if (scan() == IHEOL) continue;
			for (i=0; i < 26; i++)
				if (isit(commands[i]))
					break;
			if (i < 26) break;
			for (; i < NUMCOMMANDS; i++)
				if (strcmp(commands[i], citem) == 0) break;
			if (i < NUMCOMMANDS) break;
      // we get here iff the first parsed input from the line does not 
      // match one of the commands. In this case, the rest of the line
      // is discarded, the below message is printed, and we go back to 
      // get a new command.
			if (skill <= 2)  {
				prout("UNRECOGNIZED COMMAND. LEGAL COMMANDS ARE:");
				listCommands(TRUE);
			}
			else prout("UNRECOGNIZED COMMAND.");
		} // end get command loop
    // we get here iff the first parsed input from the line matches one
    // of the commands (i.e., command i). We use i to dispatch the 
    // handling of the command. The line may still contain additional
    // inputs (i.e., parameters of the command) that is to be parsed by
    // the dispatched command handler. If the line does not contain
    // all the necessary parameters, the dispatched command handler is 
    // responsible to get additional input(s) interactively using scan().
    // The dispatched command handler is also responsible to handle any 
    // input errors.
		switch (i) { /* command switch */
			case 0:			// srscan
				srscan(1);
				break;
			case 1:			// lrscan
				lrscan();
				break;
			case 2:			// phasers
				phasers();
				if (ididit) hitme = TRUE;
				break;
			case 3:			// photons
				photon();
				if (ididit) hitme = TRUE;
				break;
			case 4:			// move
				warp(1);
				break;
			case 5:			// shields
				sheild(1);
				if (ididit) {
					attack(2);
					shldchg = 0;
				}
				break;
			case 6:			// dock
				dock();
				break;
			case 7:			// damages
				dreprt();
				break;
			case 8:			// chart
				chart(0);
				break;
			case 9:			// impulse
				impuls();
				break;
			case 10:		// rest
				waiting();
				if (ididit) hitme = TRUE;
				break;
			case 11:		// warp
				setwrp();
				break;
			case 12:		// status
				srscan(3);
				break;
			case 13:			// sensors
				sensor();
				break;
			case 14:			// orbit
				orbit();
				if (ididit) hitme = TRUE;
				break;
			case 15:			// transport "beam"
				beam();
				break;
			case 16:			// mine
				mine();
				if (ididit) hitme = TRUE;
				break;
			case 17:			// crystals
				usecrystals();
				break;
			case 18:			// shuttle
				shuttle();
				if (ididit) hitme = TRUE;
				break;
			case 19:			// Planet list
				preport();
				break;
			case 20:			// Status information
				srscan(2);
				break;
			case 21:			// Game Report 
				report(0);
				break;
			case 22:			// use COMPUTER!
				eta();
				break;
			case 23:
				listCommands(TRUE);
				break;
			case 24:		// Emergency exit
				clearscreen();	// Hide screen
				freeze(TRUE);	// forced save
				exit(1);		// And quick exit
				break;
			case 25:
				probe();		// Launch probe
				break;
			case 26:			// Abandon Ship
				abandn();
				break;
			case 27:			// Self Destruct
				dstrct();
				break;
			case 28:			// Save Game
				freeze(FALSE);
				if (skill > 3)
					prout("WARNING--Frozen games produce no plaques!");
				break;
			case 29:			// Try a desparation measure
				deathray();
				if (ididit) hitme = TRUE;
				break;
			case 30:			// What do we want for debug???
#ifdef DEBUG
				debugme();
#endif
				break;
			case 31:		// Call for help
				help();
				break;
			case 32:
				alldone = 1;	// quit the game
#ifdef DEBUG
				if (idebug) score();
#endif
				break;
			case 33:
				helpme();	// get help
				break;
		} // end command switch
		for (;;) {
			if (alldone) break;		// Game has ended
#ifdef DEBUG
			if (idebug) prout("2500");
#endif
			if (Time != 0.0) {
				events();
				if (alldone) break;		// Events did us in
			}
			if (d.galaxy[quadx][quady] == 1000) { // Galaxy went Nova!
				atover(0);
				continue;
			}
			if (nenhere == 0) movetho();
			if (hitme && justin==0) {
				attack(2);
				if (alldone) break;
				if (d.galaxy[quadx][quady] == 1000) {	// went NOVA! 
					atover(0);
					hitme = TRUE;
					continue;
				}
			}
			break;
		} // end event loop
		if (alldone) break;
	} // end command loop
}