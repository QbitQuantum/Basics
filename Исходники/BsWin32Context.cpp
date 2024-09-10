    Win32Context::~Win32Context()
    {
		if (mOwnsContext)
			releaseContext();
    }