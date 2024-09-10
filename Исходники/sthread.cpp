ScriptThread &Script::createThread(uint16 scriptModuleNumber, uint16 scriptEntryPointNumber) {
	loadModule(scriptModuleNumber);
	if (_modules[scriptModuleNumber].entryPoints.size() <= scriptEntryPointNumber) {
		error("Script::createThread wrong scriptEntryPointNumber");
	}

	ScriptThread tmp;
	_threadList.push_front(tmp);
	ScriptThread &newThread = _threadList.front();
	newThread._instructionOffset = _modules[scriptModuleNumber].entryPoints[scriptEntryPointNumber].offset;
	newThread._commonBase = _commonBuffer.getBuffer();
	newThread._staticBase = _commonBuffer.getBuffer() + _modules[scriptModuleNumber].staticOffset;
	newThread._moduleBase = _modules[scriptModuleNumber].moduleBase.getBuffer();
	newThread._moduleBaseSize = _modules[scriptModuleNumber].moduleBase.size();
	newThread._strings = &_modules[scriptModuleNumber].strings;

	if (_vm->getGameId() == GID_IHNM)
		newThread._voiceLUT = &_globalVoiceLUT;
	else
		newThread._voiceLUT = &_modules[scriptModuleNumber].voiceLUT;

	newThread._stackBuf.resize(ScriptThread::THREAD_STACK_SIZE);
	newThread._stackTopIndex = ScriptThread::THREAD_STACK_SIZE - 2;
	debug(3, "createThread(). Total threads: %d", _threadList.size());
	return newThread;
}