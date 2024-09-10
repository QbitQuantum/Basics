	void PosixProcess::SendSignal(int signal)
	{
		if (!running)
			return;

		if (kill(GetPID(), signal) != 0)
		{
			switch (errno)
			{
			case ESRCH:
				throw ValueException::FromString("Couldn't find process");
			case EPERM:
				throw ValueException::FromString("Invalid permissions for terminating process");
			default:
				throw ValueException::FromFormat("Couldn't send signal: %d to process", signal);
			}
		}
	}