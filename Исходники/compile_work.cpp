int CompileWork::ResponseNotFound(string &respMsg)
{
	char bf;
	string compileworkdir = Config::GetInstance()->GetValue("COMPILEWOKRDIR");
	if(compileworkdir.empty())
		compileworkdir = COMPILEWOKRDIR;
	string dir = compileworkdir + "404.html";
	responseHttp->SetStatus("404 Not Found");
	respMsg = "404 not Found";
	fstream tmpFile(dir.c_str(),ios::in | ios::_Nocreate);
	if(tmpFile.is_open())
	{
		respMsg = "";
		while(tmpFile.get(bf))
		{
			respMsg += bf;
		}
	}
	tmpFile.close();

	return RT_OK;
}