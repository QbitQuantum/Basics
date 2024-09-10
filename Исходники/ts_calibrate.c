int ts_test()
{
//	struct tsdev *ts;
	calibration cal;
	int cal_fd;
	char cal_buffer[256];
	char *tsdevice = NULL;
	char *calfile = NULL;
	unsigned int i;

	int xtemp,ytemp;
	int x,y;

  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_WHITE);
	get_sample (&cal, 0, 50,        50,        "Top left");
//	clearbuf(ts);
  /* Clear the LCD */ 
//  LCD_Clear(LCD_COLOR_WHITE);
	get_sample (&cal, 1, XRES - 50, 50,        "Top right");
//	clearbuf(ts);
  /* Clear the LCD */ 
//  LCD_Clear(LCD_COLOR_WHITE);
	get_sample (&cal, 2, XRES - 50, YRES - 50, "Bot right");
//	clearbuf(ts);
  /* Clear the LCD */ 
//  LCD_Clear(LCD_COLOR_WHITE);
	get_sample (&cal, 3, 50,        YRES - 50, "Bot left");
//	clearbuf(ts);
  /* Clear the LCD */ 
//  LCD_Clear(LCD_COLOR_WHITE);
	get_sample (&cal, 4, XRES / 2,  YRES / 2,  "Center");

	if (perform_calibration (&cal)) {
		printf ("Calibration constants: ");
		for (i = 0; i < 7; i++) printf("%d ", cal.a [i]);
		printf("\n\r");
//		if ((calfile = getenv("TSLIB_CALIBFILE")) != NULL) {
//			cal_fd = open (calfile, O_CREAT | O_RDWR);
//		} else {
//			cal_fd = open ("/etc/pointercal", O_CREAT | O_RDWR);
//		}
		sprintf (cal_buffer,"%d %d %d %d %d %d %d",
			 cal.a[0], cal.a[1], cal.a[2],
			 cal.a[3], cal.a[4], cal.a[5], cal.a[6]);
		printf ("%d %d %d %d %d %d %d",
			 cal.a[1], cal.a[2], cal.a[0],
			 cal.a[4], cal.a[5], cal.a[3], cal.a[6]);
//		write (cal_fd, cal_buffer, strlen (cal_buffer) + 1);
//		close (cal_fd);
                i = 0;
	} else {
		printf("Calibration failed.\n\r");
		i = -1;
	}
	while(1)
	{
	getxy (&cal.x[0], &cal.y[0]);
	printf("before Calibration x = %d y=%d\n\r",cal.x[0],cal.y[0]);
	   		xtemp = cal.x[0];
			ytemp = cal.y[0];
			x = 	(int)(( cal.a[0] +
					cal.a[1]*xtemp + 
					cal.a[2]*ytemp ) / cal.a[6]);
			y =		(int)(( cal.a[3] +
					cal.a[4]*xtemp +
					cal.a[5]*ytemp ) / cal.a[6]);
	printf("after Calibration x = %d y=%d\n\r",x,y);
        LCD_Clear(LCD_COLOR_WHITE);
        LCD_DispNum(0,0,x,5,0);
        LCD_DispNum(0,16,y,5,0);
	}

//	close_framebuffer();
	return i;
}