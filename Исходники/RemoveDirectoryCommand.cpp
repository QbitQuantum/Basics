void RemoveDirectoryCommand::execute(VirtualMachine& vm, AbstractFunctionCall& node)
{
	vector<string>& parameters = node.getContentArrayNonConstant();
	string file = vm.getVariable(parameters[1])->getValue();
	file.erase(remove(file.begin(), file.end(), '\"'), file.end());

	if (getExtension(file) != "") 
	{
        shared_ptr<Token> tempToken = node.getToken();
		throwCustomError("Cannot remove files, only directories (use removeFile to delete a file)", vm, tempToken);

		return;
	}
	int result = -1;

	#ifdef _WIN32
		if (fs::exists(file.c_str()))
		{
			fs::remove_all(file.c_str());
			result = 0;
		}
	#else
		result = UnixRemoveDirectoryRecursive(file.c_str());
	#endif

	if (result == 0) 
	{
		cout << "Directory " << file << " and its contents were removed." << endl;
	}
	else 
	{
		char buff[256];
        
        #ifdef _WIN32
            strerror_s(buff, 100, errno);
        #else
            strerror_r(100, buff, errno);
        #endif
                
        shared_ptr<Token> tempToken = node.getToken();
		throwCustomError("Error: " + file + ": " + buff, vm, tempToken);
	}
}