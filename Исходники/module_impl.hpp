	template<typename ProcType> bool getProcAddress(const char * name,ProcType &proc)
	{
		void *ptr=getProcAddress(name);
		proc=(ProcType)ptr;
		if(!ptr)
		{
			processError();
			return false;
		}
		return true;
	}