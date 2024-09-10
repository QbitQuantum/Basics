void StepTwoApp::setup()
{
    FMODListDevices();
    FMODErrorCheck(FMOD::System_Create( &mSystem ));
    FMODErrorCheck(mSystem->setDriver(0));
	FMOD_INITFLAGS flags = FMOD_INIT_NORMAL; // right-click, Go To Definition
	FMODErrorCheck(mSystem->init( 32, flags, NULL ));

    vector<fs::path> paths;
    paths.push_back( getAssetPath("gong-loud-hit.mp3") );
    paths.push_back( getAssetPath("orch-hit.wav") );
    paths.push_back( getAssetPath("trumpethit07.wav") );
    
    for(auto& path: paths) {
        FMOD::Sound* sound;
        mSystem->createSound( path.string().c_str(), FMOD_SOFTWARE, NULL, &sound );
        
        // You can change the mode of sounds at any time.
        FMOD_MODE mode = FMOD_SOFTWARE | FMOD_2D | FMOD_LOOP_OFF;
        FMODErrorCheck( sound->setMode( mode ) );
        
        mSounds.push_back(sound);
    }
}