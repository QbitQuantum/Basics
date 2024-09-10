	//////////////////////////////////////////////////////////////////////////
	//	Utils
	//////////////////////////////////////////////////////////////////////////
	Justification GetJustEnumFromString(const std::string& just)
	{
		if (_strcmpi(just.c_str(), "center") == 0)
		{
			return CL_CENTER;
		}
		else if (_strcmpi(just.c_str(), "left") == 0)
		{
			return CL_LEFT;
		}
		else if (_strcmpi(just.c_str(), "right") == 0)
		{
			return CL_RIGHT;
		}
		else if (_strcmpi(just.c_str(), "top") == 0)
		{
			return CL_TOP;
		}
		else if (_strcmpi(just.c_str(), "bottom") == 0)
		{
			return CL_BOTTOM;
		}

		return CL_CENTER;
	}