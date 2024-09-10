bool ChooseAnImageFTP(int sx,int sy, char *ftp_dir, int slot, char **filename, bool *isdir, int *index_file)
{
/*	Parameters:
 sx, sy - window size,
 ftp_dir - what FTP directory to use,
 slot - in what slot should an image go (common: #6 for 5.25' 140Kb floppy disks, and #7 for hard-disks).
 	slot #5 - for 800Kb floppy disks, but we do not use them in Apple][?
	(They are as a rule with .2mg extension)
 index_file	- from which file we should start cursor (should be static and 0 when changing dir)

 Out:	filename	- chosen file name (or dir name)
	isdir		- if chosen name is a directory
*/
		double facx = double(g_ScreenWidth) / double(SCREEN_WIDTH);
		double facy = double(g_ScreenHeight) / double(SCREEN_HEIGHT);

	SDL_Surface *my_screen;	// for background
	struct ftpparse FTP_PARSE; // for parsing ftp directories
	
#ifndef _WIN32
	struct stat info;
#endif

	if(font_sfc == NULL)
		if(!fonts_initialization()) return false;	//if we don't have a fonts, we just can do none
	char tmpstr[512];
	char ftpdirpath [MAX_PATH];
	snprintf(ftpdirpath, MAX_PATH, "%s/%s%s", g_sFTPLocalDir, g_sFTPDirListing, md5str(ftp_dir));	// get path for FTP dir listing
//	printf("Dir: %s, MD5(dir)=%s\n",ftp_dir,ftpdirpath);

	List<char> files;		// our files
	List<char> sizes;		// and their sizes (or 'dir' for directories)

	int act_file;		// current file
	int first_file;		// from which we output files
	char ch = 0;
// prepare screen
	SDL_Surface *tempSurface;

	if(!g_WindowResized) {
		if(g_nAppMode == MODE_LOGO) tempSurface = g_hLogoBitmap;	// use logobitmap
			else tempSurface = g_hDeviceBitmap;
	}
	else tempSurface = g_origscreen;

	my_screen = SDL_CreateRGBSurface(SDL_SWSURFACE, tempSurface->w, tempSurface->h, tempSurface->format->BitsPerPixel, 0, 0, 0, 0);
	if(tempSurface->format->palette && my_screen->format->palette)
		SDL_SetColors(my_screen, tempSurface->format->palette->colors,
			      0, tempSurface->format->palette->ncolors);

	surface_fader(my_screen, 0.2F, 0.2F, 0.2F, -1, 0);	// fade it out to 20% of normal
	SDL_BlitSurface(tempSurface, NULL, my_screen, NULL);
	SDL_BlitSurface(my_screen, NULL, screen, NULL);		// show background
//	ch = 0;
	#define	NORMAL_LENGTH 60
	if(strlen(ftp_dir) > NORMAL_LENGTH) { ch = ftp_dir[NORMAL_LENGTH]; ftp_dir[NORMAL_LENGTH] = 0;} //cut-off too long string
	font_print_centered(sx/2 ,5 * facy , ftp_dir, screen, 1.5 * facx, 1.3 * facy);
	if(ch) ftp_dir[NORMAL_LENGTH] = ch; //restore cut-off char	

	font_print_centered(sx/2,20 * facy,"Connecting to FTP server... Please wait.", screen, 1 * facx, 1 * facy);
	SDL_Flip(screen);	// show the screen

	bool OKI;
#ifndef _WIN32
	if(stat(ftpdirpath,&info) == 0 && info.st_mtime > time(NULL) - RENEW_TIME) {
		OKI = false; // use this file
	}
	else {
		OKI = ftp_get(ftp_dir,ftpdirpath); // get ftp dir listing
	}
#else
// in WIN32 let's use constant caching? -- need to be redone using file.mtime
	if(GetFileAttributes(ftpdirpath) != DWORD(-1)) OKI = false;
		else OKI = ftp_get(ftp_dir,ftpdirpath); // get ftp dir listing
#endif

	if(OKI) {	// error
		printf("Failed getting FTP directory %s to %s\n",ftp_dir,ftpdirpath);	
		font_print_centered(sx/2,30 * facy, "Failure. Press any key!",screen, 1.4 * facx, 1.1 * facy);
		SDL_Flip(screen);	// show the screen
		SDL_Delay(KEY_DELAY);	// wait some time to be not too fast
		//////////////////////////////////
		// Wait for keypress
		//////////////////////////////////
		SDL_Event event;	// event
		Uint8 *keyboard;	// key state

		event.type = SDL_QUIT;
		while(event.type != SDL_KEYDOWN) {	// wait for key pressed
					SDL_Delay(100);
					SDL_PollEvent(&event);
		}
		SDL_FreeSurface(my_screen);		
		return false;	
	 }

		FILE *fdir = fopen(ftpdirpath,"r");
	
		char *tmp;
		int i,j, B, N;	// for cycles, beginning and end of list

// build prev dir
	if(strcmp(ftp_dir, "ftp://")) {
		tmp = new char[3];
		strcpy(tmp, "..");
		files.Add(tmp);
		tmp = new char[5];
		strcpy(tmp, "<UP>");
		sizes.Add(tmp);	// add sign of directory
		B = 1;
	}
	else	B = 0;	// for sorting dirs 

			while (tmp = fgets(tmpstr,512,fdir)) // first looking for directories
			{
				// clear and then try to fill in FTP_PARSE struct
				memset(&FTP_PARSE,0,sizeof(FTP_PARSE));
				ftpparse(&FTP_PARSE, tmp, strlen(tmp));
				
				int what = getstatFTP(&FTP_PARSE, NULL);
				
				if (strlen(FTP_PARSE.name) > 0 &&  what == 1) // is directory!
				{
					tmp = new char[strlen(FTP_PARSE.name)+1];	// add entity to list
					strcpy(tmp, FTP_PARSE.name);
					files.Add(tmp);
					tmp = new char[6];
					strcpy(tmp, "<DIR>");
					sizes.Add(tmp);	// add sign of directory
				} /* if */

			}
// sort directories. Please, don't laugh at my bubble sorting - it the simplest thing I've ever seen --bb
			if(files.Length() > 2)
			{
				N = files.Length() - 1;
//				B = 1; - defined above
				for(i = N; i > B; i--)
					for(j = B; j < i; j++)
						if(strcasecmp(files[j], files[j + 1]) > 0)
						{
							files.Swap(j,j + 1);
							sizes.Swap(j,j + 1);
						}

			}
			B = files.Length();	// start for files

			(void) rewind (fdir);	// to the start
				// now get all regular files
			while (tmp = fgets(tmpstr,512,fdir))
			{
				int fsize;
				// clear and then try to fill in FTP_PARSE struct
				memset(&FTP_PARSE,0,sizeof(FTP_PARSE));
				ftpparse(&FTP_PARSE, tmp, strlen(tmp));
				
				if ((getstatFTP(&FTP_PARSE, &fsize) == 2)) // is normal file!
				{
					tmp = new char[strlen(FTP_PARSE.name)+1];	// add this entity to list
					strcpy(tmp, FTP_PARSE.name);
					files.Add(tmp);
					tmp = new char[10];	// 1400000KB
					snprintf(tmp, 9, "%dKB", fsize);
					sizes.Add(tmp);	// add this size to list
				} /* if */
			}
			(void) fclose (fdir);
// do sorting for files
			if(files.Length() > 2 && B < files.Length())
			{
				N = files.Length() - 1;
//				B = 1;
				for(i = N; i > B; i--)
					for(j = B; j < i; j++)
						if(strcasecmp(files[j], files[j + 1]) > 0)
						{
							files.Swap(j,j + 1);
							sizes.Swap(j,j + 1);
						}
			}
//	Count out cursor position and file number output
	act_file = *index_file;
	if(act_file >= files.Length()) act_file = 0;		// cannot be more than files in list
	first_file = act_file - (FILES_IN_SCREEN / 2);
	if (first_file < 0) first_file = 0;	// cannot be negativ...

// Show all directories (first) and files then
//	char *tmp;
	char *siz;
//	int i;

	while(true)
	{
		SDL_BlitSurface(my_screen, NULL, screen, NULL);		// show background
		font_print_centered(sx/2 ,5 * facy , ftp_dir, screen, 1.5 * facx, 1.3 * facy);
		if (slot == 6) font_print_centered(sx/2,20 * facy,"Choose image for floppy 140KB drive", screen, 1 * facx, 1 * facy);
		else
			if (slot == 7) font_print_centered(sx/2,20 * facy,"Choose image for Hard Disk", screen, 1 * facx, 1 * facy);
		else
			if (slot == 5) font_print_centered(sx/2,20 * facy,"Choose image for floppy 800KB drive", screen, 1 * facx, 1 * facy);
		else
			if (slot == 1) font_print_centered(sx/2,20 * facy,"Select file name for saving snapshot", screen, 1 * facx, 1 * facy);
		else
			if (slot == 0) font_print_centered(sx/2,20 * facy,"Select snapshot file name for loading", screen, 1 * facx, 1 * facy);

		font_print_centered(sx/2,30 * facy, "Press ENTER to choose, or ESC to cancel",screen, 1.4 * facx, 1.1 * facy);

		files.Rewind();	// from start
		sizes.Rewind();
		i = 0;

//		printf("We've printed some messages, go to file list!\n");
// show all fetched dirs and files
// topX of first fiel visible
		int TOPX	= 45 * facy;

		while(files.Iterate(tmp)) {
			sizes.Iterate(siz);	// also fetch size string

			if (i >= first_file && i < first_file + FILES_IN_SCREEN)
			{ // FILES_IN_SCREEN items on screen
//				char tmp2[80],tmp3[256];

				if (i == act_file) { // show item under cursor (in inverse mode)
					SDL_Rect r;
					r.x= 2;
					r.y= TOPX + (i-first_file) * 15 * facy - 1;
					if(strlen(tmp) > 46) r.w = 46 * 6 * 1.7 * facx + 2;
					   else r.w= strlen(tmp) * 6 * 1.7 * facx + 2;	// 6- FONT_SIZE_X
					r.h= 9 * 1.5 * facy;
					SDL_FillRect(screen, &r, SDL_MapRGB(screen->format,255,0,0));// in RED
				} /* if */

				// print file name with enlarged font
				ch = 0;
				if(strlen(tmp) > 46) { ch = tmp[46]; tmp[46] = 0;} //cut-off too long string
				font_print(4, TOPX + (i - first_file) * 15 * facy, tmp, screen, 1.7 * facx, 1.5 * facy); // show name
				font_print(sx - 70*facx, TOPX + (i - first_file) * 15 * facy, siz, screen, 1.7 * facx, 1.5 * facy);// show info (dir or size)
				if(ch) tmp[46] = ch; //restore cut-off char
			} /* if */
			i++;		// next item
		} /* while */

/////////////////////////////////////////////////////////////////////////////////////////////
// draw rectangles
	rectangle(screen, 0, TOPX - 5, g_ScreenWidth, 320 * facy, SDL_MapRGB(screen->format, 255, 255, 255));
	rectangle(screen, 480 * facx, TOPX - 5, 0, 320 * facy, SDL_MapRGB(screen->format, 255, 255, 255));

	SDL_Flip(screen);	// show the screen
	SDL_Delay(KEY_DELAY);	// wait some time to be not too fast

	//////////////////////////////////
	// Wait for keypress
	//////////////////////////////////
	SDL_Event event;	// event
	Uint8 *keyboard;	// key state

	event.type = SDL_QUIT;
	while(event.type != SDL_KEYDOWN) {	// wait for key pressed
				SDL_Delay(10);
				SDL_PollEvent(&event);
	}

// control cursor
		keyboard = SDL_GetKeyState(NULL);	// get current state of pressed (and not pressed) keys
		if (keyboard[SDLK_UP] || keyboard[SDLK_LEFT]) {
			if (act_file>0) act_file--;	// up one position
			if (act_file<first_file) first_file=act_file;
		} /* if */

		if (keyboard[SDLK_DOWN] || keyboard[SDLK_RIGHT]) {
			if (act_file < (files.Length() - 1)) act_file++;
			if (act_file >= (first_file + FILES_IN_SCREEN)) first_file=act_file - FILES_IN_SCREEN + 1;
		} /* if */

		if (keyboard[SDLK_PAGEUP]) {
			act_file-=FILES_IN_SCREEN;
			if (act_file<0) act_file=0;
			if (act_file<first_file) first_file=act_file;
		} /* if */

		if (keyboard[SDLK_PAGEDOWN]) {
			act_file+=FILES_IN_SCREEN;
			if (act_file>=files.Length()) act_file=(files.Length()-1);
			if (act_file>=(first_file+FILES_IN_SCREEN)) first_file=act_file-FILES_IN_SCREEN + 1;
		} /* if */

		// choose an item?
		if (keyboard[SDLK_RETURN]) {
			// dup string from selected file name
			*filename = strdup(php_trim(files[act_file],strlen(files[act_file])));
//			printf("files[act_file]=%s, *filename=%s\n\n", files[act_file], *filename);
			if(!strcmp(sizes[act_file], "<DIR>") || !strcmp(sizes[act_file], "<UP>"))
			   		*isdir = true;
				else *isdir = false;	// this is directory (catalog in Apple][ terminology)
			*index_file = act_file;	// remember current index
			files.Delete();
			sizes.Delete();
			SDL_FreeSurface(my_screen);

			return true;
		} /* if */

		if (keyboard[SDLK_ESCAPE]) {
			files.Delete();
			sizes.Delete();
			SDL_FreeSurface(my_screen);
			return false;		// ESC has been pressed
		} /* if */

		if (keyboard[SDLK_HOME]) {	// HOME?
			act_file=0;
			first_file=0;
		} /* if */
		if (keyboard[SDLK_END]) {	// END?
			act_file=files.Length() - 1;	// go to the last possible file in list
			first_file=act_file - FILES_IN_SCREEN + 1;
			if(first_file < 0) first_file = 0;
		} /* if */

	}
} /* ChooseAnImageFTP */