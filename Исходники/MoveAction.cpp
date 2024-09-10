	bool MoveAction::Act(const Archive & archive)
	{
		if (!dest_dir_.empty())
		{
			int create_dir = SHCreateDirectory(NULL, dest_dir_.c_str());
			if (create_dir != ERROR_SUCCESS)
			{
				std::wstring error = util::FormatErrorMessage();
				return false;
			}
		}
		int ret = CopyFileEx(archive.FullName().c_str(), dest_path_.c_str(), (LPPROGRESS_ROUTINE)Callback, this, NULL, 0);
		if (!ret)
		{			
			std::wstring errormessage = util::FormatErrorMessage();
			return false;
		}

		if (!orignal_reserved_)
		{
			DeleteFile(archive.FullName().c_str());
		}

		return true;
	}