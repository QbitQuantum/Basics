	bool BootUtils::RunInstaller(
		vector<SharedDependency> missing,
		SharedApplication application,
		std::string updateFile,
		std::string installerPath,
		bool quiet,
		bool forceInstall)
	{
		if (installerPath.empty())
		{
			installerPath = application->path;
		}

		string exec = FileUtils::Join(
			installerPath.c_str(), "installer", "Installer.exe", NULL);

		if (!FileUtils::IsFile(exec))
		{
			return false;
		}

		vector<string> args;
		args.push_back("-appPath");
		args.push_back(application->path);

		args.push_back("-exePath");
		args.push_back(application->GetExecutablePath());
		if (!updateFile.empty())
		{
			args.push_back("-updateFile");
			args.push_back(updateFile);
		}

		if (quiet)
		{
			args.push_back("-quiet");
		}
		
		if (forceInstall)
		{
			args.push_back("-forceInstall");
		}

		vector<string> jobs;
		vector<SharedDependency>::iterator mi = missing.begin();
		while (mi != missing.end())
		{
			SharedDependency d = *mi++;
			string url = application->GetURLForDependency(d);
			string job = d->name + "," + d->version + "," + url;
			jobs.push_back(job);
		}
	
		// A little bit of ugliness goes a long way:
		// Use ShellExecuteEx here with the undocumented runas verb
		// so that we can execute the installer executable and have it
		// properly do the UAC thing. Why isn't this in the API?
	
		// More ugliness: The path length for ShellExecuteEx is limited so just
		// pass a file name containing all the download jobs. :(
		string tempdir = FileUtils::GetTempDirectory();
		string jobsFile = FileUtils::Join(tempdir.c_str(), "jobs", NULL);
		if (jobs.size() > 0)
		{
			FileUtils::CreateDirectory(tempdir);
			std::ofstream outfile(jobsFile.c_str());
			for (size_t i = 0; i < jobs.size(); i++)
			{
				outfile << jobs[i] << "\n";
			}
			outfile.close();
			args.push_back(jobsFile);
		}
	
		string paramString = "";
		for (size_t i = 0; i < args.size(); i++)
		{
			paramString.append(" \"");
			paramString.append(args.at(i));
			paramString.append("\"");
		}
		printf("%s\n", paramString.c_str());
	
		SHELLEXECUTEINFOA ShExecInfo = {0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_DDEWAIT;
		ShExecInfo.hwnd = NULL;
		if (!IsWindowsXP()) {
			ShExecInfo.lpVerb = "runas";
		}
		ShExecInfo.lpFile = exec.c_str();
		ShExecInfo.lpParameters = paramString.c_str();
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_SHOW;
		ShExecInfo.hInstApp = NULL;	
		ShellExecuteExA(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
		DWORD returnCode;
		GetExitCodeProcess(ShExecInfo.hProcess, &returnCode);
		
		if (FileUtils::IsDirectory(tempdir))
		{
			FileUtils::DeleteDirectory(tempdir);
		}

		if (returnCode != 0) {
			return false;
		}
		return true;
	}