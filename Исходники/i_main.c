int main(int argc, char** argv)
{
#ifdef USE_DEBUGNET
    int ret = debugNetInit("255.255.255.255", 18194, DEBUG);
    printf("debugNetInit: %d", ret);
#endif

    printf("DOOM started\n");

    setbuf(stdout, NULL);

    int res = scePowerSetArmClockFrequency(50);
    if (res != 0x0)
    {
        printf("scePowerSetArmClockFrequency failed! (0x%08x) (Normal if not using PSM Unity 1.06. No clock speed change for you.)\n", res);
    }

    myargc = 0;
    myargv = 0;

    doomwaddir = PSP2_DIR("Documents/");
    strcpy_s(doomwaddir2, 256, doomwaddir);
    strcat(doomwaddir2, "WADS/");

    printf("WAD folder: %s\n", doomwaddir2);

	//pspAudioInit();
	//pspAudioSetChannelCallback(0, (void *)&sound_callback);

	//_DisableFPUExceptions();
//	pspDebugScreenInit();

	//sceCtrlSetSamplingCycle(0);

	//int result = sceCtrlSetSamplingMode(PSP2_CTRL_MODE_ANALOG);
 //   if (result < 0)
 //   {
 //       printf("sceCtrlSetSamplingMode : 0x%x", result);
 //   }

	//SetupCallbacks();
        pgInit();
        pgScreenFrame(2,0);
        pgFillvram(0);

    Get_DirList(doomwaddir2);
    dlist_start  = 0;
    dlist_curpos = 0;
    now_depth    = 0;

while(1) {
    Draw_All();
switch(Control()) {
		case 1:
			Get_DirList(doomwaddir2);
			break;
		case 2:
                        pgFillvram(0);
                        strcpy_s(target, 264, doomwaddir2);
                        strcat(target, dlist[dlist_curpos].name);

                        pgScreenFlipV();
                        //pspDebugScreenInit();

    D_DoomMain (); 
        }
    }    

    return 0;

}