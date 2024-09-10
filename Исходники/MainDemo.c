    int main(void)
{
    SHORT       width, height;	// variables to store the height and width of the 16-bit bitmap image
    SHORT       counter;		// loop control variable for each shape that controls how many shapes are printed and their scale
    SHORT  		triangle[] = {160,120,160,120,160,120,160,120};		// triangle polygon points (start triangle in center of LCD)
    
    #if defined(__dsPIC33F__) || defined(__PIC24H__)

    // Configure Oscillator to operate the device at 40Mhz
    // Fosc= Fin*M/(N1*N2), Fcy=Fosc/2
    // Fosc= 8M*40(2*2)=80Mhz for 8M input clock
    PLLFBD = 38;                    // M=40
    CLKDIVbits.PLLPOST = 0;         // N1=2
    CLKDIVbits.PLLPRE = 0;          // N2=2
    OSCTUN = 0;                     // Tune FRC oscillator, if FRC is used

    // Disable Watch Dog Timer
    RCONbits.SWDTEN = 0;

    // Clock switching to incorporate PLL
    __builtin_write_OSCCONH(0x03);  // Initiate Clock Switch to Primary

    // Oscillator with PLL (NOSC=0b011)
    __builtin_write_OSCCONL(0x01);  // Start clock switching
    while(OSCCONbits.COSC != 0b011);

    // Wait for Clock switch to occur	
    // Wait for PLL to lock
    while(OSCCONbits.LOCK != 1)
    { };
    #elif defined(__PIC32MX__)
    INTEnableSystemMultiVectoredInt();
    SYSTEMConfigPerformance(GetSystemClock());
    #ifdef MULTI_MEDIA_BOARD_DM00123
    CPLDInitialize();
    CPLDSetGraphicsConfiguration(GRAPHICS_HW_CONFIG);
    CPLDSetSPIFlashConfiguration(SPI_FLASH_CHANNEL);
    #endif
    #endif

    #if defined (PIC24FJ256DA210_DEV_BOARD)
    
    // _ANSG8 = 0; /* S1 */
    // _ANSE9 = 0; /* S2 */
    // _ANSB5 = 0; /* S3 */
        
    #else

    /////////////////////////////////////////////////////////////////////////////
    // ADC Explorer 16 Development Board Errata (work around 2)
    // RB15 should be output
    /////////////////////////////////////////////////////////////////////////////
    LATBbits.LATB15 = 0;
    TRISBbits.TRISB15 = 0;

    #endif

    /////////////////////////////////////////////////////////////////////////////
    #if defined(__dsPIC33FJ128GP804__) || defined(__PIC24HJ128GP504__)
    AD1PCFGL = 0xffff;
    #endif
    InitGraph();

    while(1)
    {
	    /* Display the Kettering Logo bit image with the Welcome to the ECE in the center 
	    /* The image was taken from a JPEG and converted to a 16-bit bitmap in order to meet 
	    /* the display requirement of 16-bits per pixel. This can be done by resaving the
	    /* JPEG as 16-bit bitmap in a image editing program and then converting it using
	    /* the graphics library resource converter. The LCD only supports 4-bit, 8-bit, and
	    /* 16-bits per pixel images 
	    */
	    width = GetImageWidth((void *) &kulogo);
		SetFont((void *) &Font25);
	    WAIT_UNTIL_FINISH(PutImage(45, 20 , (void *) &kulogo,  1)); // image location is relative to the top left corner of the image
        SetColor(WHITE);
        Bar(45, 110, width + 45, 135);	// Draw a bar over the image to place the text over.
        SetColor(BLUE);
        OutTextXY(65, 110, "WELCOME TO THE ECE");
        
        DelayMs(DEMODELAY);	// delay for 1 sec and clear the screen
        SetColor(BLACK);
        ClearDevice();

		/* Display multiple circles, starting at the center and increasing in size at 
        /* each draw until the LCD borders are met. Increasing the counter value will 
        /* expand the shape size more quickly. */
        for(counter = 0; counter < MIN(GetMaxX(), GetMaxY()) >> 1; counter += 14)
        {
	        SetColor(BLACK);	// refresh the screen
	        ClearDevice();	
	        SetColor(BRIGHTRED);
	        SetFont((void *) &Font25);		// draw the name of the shape in the center
	        OutTextXY(135, 110, "Circle");
            WAIT_UNTIL_FINISH(Circle(GetMaxX() >> 1, GetMaxY() >> 1, counter + 5));	// draw the shape
            DelayMs(50);	// display for 50 ms
        }

        DelayMs(DEMODELAY);	// delay for 1 sec and clear the screen
        SetColor(BLACK);
        ClearDevice();

		/* Display multiple rectangles, starting at the center and increasing in size at 
        /* each draw until the LCD borders are met. Increasing the counter value will 
        /* expand the shape size more quickly. */
        for(counter = 0; counter < MIN(GetMaxX() / 2, GetMaxY() / 2) >> 1; counter += 5)
        {	
	        SetColor(BLACK);	// refresh the screen
	        ClearDevice();	
	        SetColor(BRIGHTBLUE);
	        OutTextXY(120, 110, "Rectangle");	// draw the name of the shape in the center
            WAIT_UNTIL_FINISH
            (
                Rectangle
                    (
                        GetMaxX() / 2 - counter * 3 + 6,	// x value of top left corner of rectangle
                        GetMaxY() / 2 - counter * 2 - 8,	// y value of top left corner of rectangle
                        GetMaxX() / 2 + counter * 3 - 6,	// x value of bottom right corner of rectangle
                        GetMaxY() / 2 + counter * 2 + 8     // y value of bottom right corner of rectangle        
                    )
            );
            DelayMs(20); // Display for 20 ms
            
        }

        DelayMs(DEMODELAY); // delay for 1 sec and clear the screen
        SetColor(BLACK);
        ClearDevice();
        
        /* Display multiple triangles, starting at the center and increasing in size at 
        /* each draw until the LCD borders are met. Increasing the counter value will 
        /* expand the shape size more quickly. */
        int i;
		for(counter = 0; counter < MIN(GetMaxX() / 2, GetMaxY() / 2) >> 1; counter += 10)
		{
			SetColor(BLACK);	// refresh the screen
			ClearDevice();
			SetColor(GREEN);	// draw the name of the shape at the center
			OutTextXY(125, 110, "Triangle");
			
			//{160,120,160,120,160,120,160,120} start in center of screen
			triangle[1] = triangle[1] - counter * 2 - 20; 	 // top point y
			triangle[7] = triangle[1];				 		 // top point y (close triangle)
			triangle[2] = triangle[2] - counter * 2 - 58; 	 // left corner point x
			triangle[3] = triangle[3] + counter * 2 + 16;	 // left corner point y
			triangle[4] = triangle[4] + counter * 2 + 58; 	 // right corner point x
			triangle[5] = triangle[5] + counter * 2 + 16;	 // right corner point y
			
			DrawPoly(4, triangle);	// draw the triangle (4 points to enclose it)
			
			// reset each of the triangle points to the center to prevent over expansion
			for (i = 0; i < 8; i++)
				if (i % 2 == 0)
					triangle[i] = 160;
				else
					triangle[i] = 120;
				
			DelayMs(50);	// display for 50 ms
		}
		
       
		DelayMs(DEMODELAY); // delay for 1 sec and clear the screen
    	SetColor(BLACK);
    	ClearDevice();
        
    }
}