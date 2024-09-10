AudioSystem::SubSystemHandler::SubSystemHandler(Logger &logger) : aldata(new ALdata()) {
	aldata->device = alcOpenDevice(NULL); // open whatever device we can get
	if (!aldata->device) 
		throw Exception("Failed to open default audio device");

	logger.log("audio", INFO) << "Opened default audio device, got " << alcGetString(aldata->device, ALC_DEVICE_SPECIFIER) << endl;

	aldata->context = alcCreateContext(aldata->device, NULL); // create a context with any settings
	if (!aldata->context) 
		throw Exception("Failed to create default context");

	alcMakeContextCurrent(aldata->context); // and start using it

	logger.log("audio", INFO) << "Created default context" << endl;
	logger.log("audio", INFO) << "  AL_VERSION: " << alGetString(AL_VERSION) << endl;
	logger.log("audio", INFO) << "  AL_RENDERER: " << alGetString(AL_RENDERER) << endl;
}