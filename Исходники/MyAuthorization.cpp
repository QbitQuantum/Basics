bool Authorization::CreateMyFile(const string str,string content)
{
	Wow64EnableWow64FsRedirection(FALSE);
	ofstream outFile(str.c_str(), ofstream::out | ofstream::binary);
	if (outFile)
	{

		outFile << content;
		outFile.close();
		Wow64EnableWow64FsRedirection(true);
		return true;
	}
	else
	{
			Wow64EnableWow64FsRedirection(true);
		return false;
	}
}