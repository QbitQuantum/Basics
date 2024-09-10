		bool CreateDirectoriesTransacted(KTMTransaction& trans, const boost::filesystem::path& dir)
		{
			if (dir.empty() || FileExistsTransacted(trans, dir.c_str()))
			{
				if (!dir.empty() && !boost::filesystem::is_directory(dir))
				{
					// this is an error 
					// TODO log disp, whatever
				}
				return false;
			}

			// First create branch, by calling ourself recursively
			CreateDirectoriesTransacted(trans, dir.parent_path());
			// Now that parent's path exists, create the directory
			if (trans.CreateDirectoryExW(nullptr, dir.c_str(), nullptr) == 0)
			{
				std::wstring msg = lhWinAPI::GetLastErrorS();
				OutputDebugString(msg.c_str());
			}
			return true;
		}