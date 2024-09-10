bool SupportedEncodersLoader::scan(ConverterOptions::SupportedEncoders& encoders, const Path& ffmpegPath){
	std::list<std::string> args;
	args.push_back("-codecs");
	ProcessExecutor::Process ffmpeg(ffmpegPath.getPath(), args);

	if(ffmpeg.waitForProcessBegin()){
		std::string message = getExecutorError(ffmpeg);
		easylog(CppExtension::Logger::ERROR, message);
		return false;
	}

	std::string line;
	bool findMatch = false;
	while(ffmpeg.getStdOut() >> line){
		parseLine(line, encoders, findMatch);
	}
	return findMatch & (ffmpeg.waitForProcessEnd() == 0);
}