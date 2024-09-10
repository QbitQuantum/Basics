	void ApplicationBinding::_GetPID(const ValueList& args, KValueRef result)
	{
		if (this->current)
		{
			result->SetInt(GETPID());
		}
	}