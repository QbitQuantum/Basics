	SPtr<GpuProgram> GpuProgramManager::create(const String& source, const String& entryPoint, const String& language,
		GpuProgramType gptype, GpuProgramProfile profile,
		bool requiresAdjacencyInformation)
	{
		GpuProgram* program = new (bs_alloc<GpuProgram>()) GpuProgram(source, entryPoint, language, gptype, profile, requiresAdjacencyInformation);
		SPtr<GpuProgram> ret = bs_core_ptr<GpuProgram>(program);
		ret->_setThisPtr(ret);
		ret->initialize();

		return ret;
	}