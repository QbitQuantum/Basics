/* 
########################
System functions
########################
 */
void gp_Reset(void)
{
	unsigned int i=0;
	
	gp_setCpuspeed(533);

	if( gp2x_sound_thread) 
	{ 
		gp2x_sound_thread_exit=1; 
		usleep(500); 
	}
 
	MLCADDRESS0 = bkregs32[0]; MLCADDRESS1 = bkregs32[1]; MLCCONTROL0 = bkregs32[2]; MLCCONTROL1 = bkregs32[3]; MLCLEFTRIGHT0 = bkregs32[4];
	MLCTOPBOTTOM0 = bkregs32[5]; MLCLEFTRIGHT1 = bkregs32[6]; MLCTOPBOTTOM1 = bkregs32[7]; MLCBGCOLOR = bkregs32[8]; MLCHSTRIDE0 = bkregs32[9];
	MLCVSTRIDE0 = bkregs32[10]; MLCHSTRIDE1 = bkregs32[11]; MLCVSTRIDE1 = bkregs32[12]; DPCCTRL1 = bkregs32[13]; MLCSCREENSIZE = bkregs32[14];

	lc_dirtylayer(0);
	lc_dirtylayer(1);
	lc_dirtymlc();

   	munmap((void *)memregs32, 0x20000);
	
	munmap(framebuffer_mmap[0], fb_size * BUFFERS);

	if (wiz_dev[0]) close(wiz_dev[0]);
	if (wiz_dev[1]) close(wiz_dev[1]);
	if (wiz_dev[2]) close(wiz_dev[2]);
	
	fcloseall();

	chdir("/usr/gp2x");
	execl("gp2xmenu",NULL);
}