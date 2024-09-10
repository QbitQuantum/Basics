bool getIniValue(string filename,string section,string key,string defultValue,string& value){
	

	char lpBuffer[PATH_BUFFER_LENGTH];
	ZeroMemory(lpBuffer,PATH_BUFFER_LENGTH);

	DWORD nBufferLength = GetCurrentDirectoryA(
									PATH_BUFFER_LENGTH,
									lpBuffer
								);
	string path = ""; 
	if (!nBufferLength) return false;

	path=lpBuffer;
	path+="\\";
	path+=filename;
	

	ZeroMemory(lpBuffer,PATH_BUFFER_LENGTH);

	nBufferLength=  GetPrivateProfileStringA(						  
						  section.c_str(),
						  key.c_str(),
						  defultValue.c_str(),
						  lpBuffer,
						  PATH_BUFFER_LENGTH,
						  path.c_str()
						);

	if (!nBufferLength) return false;

	value = lpBuffer;
	return true;

}