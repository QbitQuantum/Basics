void initializeSound()
{
	FMOD::System     *system;
    unsigned int      version;
	
	result = FMOD::System_Create(&system);
    ERRCHECK(result);
	
    result = system->getVersion(&version);
    ERRCHECK(result);
	
	if (version < FMOD_VERSION)
    {
        printf("Error!  You are using an old version of FMOD %08x.  This program requires %08x\n", version, FMOD_VERSION);
        exit(-3);
    }
	
	result = system->init(32, FMOD_INIT_NORMAL, NULL);
    ERRCHECK(result);
	
	result = system->createSound("/Users/adrtwin/Music/What You Know (Mustang Remix).mp3", FMOD_SOFTWARE, 0, &sound1);
    ERRCHECK(result);
	
	
	
	/*
	result = system->createSound("CALIBRATING", FMOD_SOFTWARE, 0, &sound2);
    ERRCHECK(result);
	
    result = system->createSound("SHOT", FMOD_SOFTWARE, 0, &sound3);
    ERRCHECK(result);
	
    result = system->createSound("SHOT_NO_AMMO", FMOD_SOFTWARE, 0, &sound4);
    ERRCHECK(result);
	
	result = system->createSound("RELOADING", FMOD_SOFTWARE, 0, &sound5);
    ERRCHECK(result);
	*/
	globalSystem = system;
}