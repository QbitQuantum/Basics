int main(void)
{
		char dpage=0;
		unsigned char i=0;
		unsigned char j=0;
		
		comm_ioctl_parms_t commparm = {38400,0};
	hires=0;
		/* Disable JTAG port */
		MCUCR |= _BV(JTD);
		MCUCR |= _BV(JTD);
	
	
		DDRA=0;    //all input
		PORTA=0xff;   //pullup
	
		xram_init();  //enable external ram
		
		dev_comm.ioctl(COMM_IOCTL_INITBAUD, &commparm);
		
	//	dev_key.ioctl(KEY_IOCTL_INIT, NULL);
		
	//		
	//	dev_key.ioctl(KEY_IOCTL_INTERRUPT_DISABLE, NULL); /*disable keyboard interrupt */
		vga_init();
		
		sei(); //enable interrupts
		
		
		VGA_DISPLAY(0);
		
				
		
		vga_slow();
		
		SELECT_RAM_BANK(0);
		clearscreen(0);
		SELECT_RAM_BANK(1);
		clearscreen(0);		
		{
			
			char x=0;
			char y=0;
			char pos[] = {0,0};
			char dir=1;
			char scr=0;
			char cposr[]={100,100};
				
			char cpos=100;
					
			while(1) {
				
				VGA_DISPLAY(scr); //show 1 page
	
				SELECT_RAM_BANK(scr^1); //draw on other page;

							
				//undraw what we drew on this page last time
				for (x=30+pos[scr^1];x<100+pos[scr^1];x+=12) {
					for (y=10;y<80;y+=12) {
						drawchar(x,y, ' ', BLACK, BLACK);
						
						
					}
				}
				
				//undraw player position
				
				drawchar(cposr[scr^1], 210, '^', BLACK, TRANSPARENT);
				
				
				//incrment positions
				pos[scr^1] = pos[scr]+dir;
				
				if(pos[scr^1] > 100)
					dir=-1;
					
				if (pos[scr^1] < 1)
					dir = 1;
				
				if(dev_multi_input.kbhit()) {
					char c = dev_multi_input.getc();
					if (c =='a'	)
						cpos-=5;
						
					if (c =='d'	)
						cpos+=5;
					
				}
							
				//draw new stuff
				
				for (x=30+pos[scr^1];x<100+pos[scr^1];x+=12) {
					for (y=10;y<80;y+=12) {
						drawchar(x,y,0xea, YELLOW, TRANSPARENT);
						drawchar(x,y, '^' , RED, TRANSPARENT);	
					}
				}
				
				//draw player position
				cposr[scr^1] = cpos;
				drawchar(cpos, 210, '^', GREEN, TRANSPARENT);
				
					
				scr ^=1; //flip roles
				
			}
			
			
			
		
			while(1){
				drawsprite( x, y, catsprite, 16, 16);			
				
				drawsprite( x, y+20, catsprite, 16, 16);
				drawsprite( x, y+40, catsprite, 16, 16);
				drawsprite( x, y+60, catsprite, 16, 16);
				drawsprite( x, y+80, catsprite, 16, 16);
				drawsprite( x, y+100, catsprite, 16, 16);
				
				drawsprite( x, y+120, catsprite, 16, 16);
				drawsprite( x, y+140, catsprite, 16, 16);
				drawsprite( x, y+160, catsprite, 16, 16);
				
				
				x+=1;
				if (x==0)
					y+=1;
				
					
				
			}
		
		}
		
		#if 1
		{

prints(&dev_keyincommout, "pressenter");
dev_keyincommout.getc();
			
			SELECT_RAM_BANK(0);
			START_FAST_WRITE;
			for(i=0;i<240;i++) {
				
				SELECT_RAM_PAGE(i);
				
				for(j=0;j<240;j++) {
					FAST_WRITE(j,7);
				
				}
			}
			
			vga_fast();
			
			prints(&dev_keyincommout, "pressenter2");
			dev_keyincommout.getc();
			vga_mode(VGA_512);
			
			SELECT_RAM_BANK(1);
			START_FAST_WRITE;
			for(i=0;i<240;i++) {
				SELECT_RAM_PAGE(i);
				for(j=0;j<240;j++) {
					FAST_WRITE(j,63);
					FAST_WRITE(j,63);
					FAST_WRITE(j,63);
					FAST_WRITE(j,63);
					FAST_WRITE(j,63);
					FAST_WRITE(j,63);
					FAST_WRITE(j,63);
				}
			}
			
			END_FAST_WRITE;
		}
		
			prints(&dev_keyincommout, "pressenter3");
			dev_keyincommout.getc();
				
		
			
			
			prints(&dev_keyincommout, "pressenter3");
			dev_keyincommout.getc();
			
			vga_mode(VGA_256);
		
		#endif
			
		VGA_BEGIN_DRAW;	
		for (i=20;i<200;i++)
		{
			
			j=i>>1;
			VGA_DOT(i,j,i);	
		}
		VGA_END_DRAW;
			
		vga_slow();
			
		//keyboard/comm test
		while (1){
			/*
			prints(&dev_comm, "This is a test comm>");
			readline(&dev_comm, str, sizeof(str), 1);
			prints(&dev_comm, "You said ");
			prints(&dev_comm, str);
			while (! dev_comm.kbhit())
				prints(&dev_comm, ".");
			*/
				
			prints(&dev_keyincommout, "This is a test keyb>");
			readline(&dev_keyincommout, str, sizeof(str), 1);
			prints(&dev_keyincommout, "You said ");
			prints(&dev_keyincommout, str);
			while (! dev_keyincommout.kbhit())
				prints(&dev_keyincommout, ".");
				
				
				
			VGA_DISPLAY(dpage);
			
			
			//SELECT_RAM_BANK(dpage);
			
			sprintf(str, "dpage:%d", dpage);
			prints(&dev_comm, str);
			
			dpage++;
			if (dpage==2)
				dpage=0;
				
		}
};