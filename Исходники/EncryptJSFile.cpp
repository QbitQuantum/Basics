// 遍历JS文件
void TraversalPath(const char* lpszPath,const char * lpszFilePath, FILE *fp)
{
	std::string dir = lpszPath;
	dir += "\\*.*";

	WIN32_FIND_DATAA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFileA(dir.c_str(), &FindFileData);

	if(hFind == INVALID_HANDLE_VALUE)
		return;
	do{
		std::string fn = FindFileData.cFileName;

		if ((strcmp(fn.c_str(), ".") != 0) && (strcmp(fn.c_str(), "..") != 0) && (strcmp(fn.c_str(), ".svn") != 0))
		{
			//为每个单独升级模块制作xxx.mchk完整性效验文件
			/*if( isSpecial(FindFileData.cFileName) )
				continue;*/

			// 子目录
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				std::string subDir = lpszPath;
				subDir = subDir + "\\" + fn;
				std::string filePath = lpszFilePath;
				filePath = filePath + "\\" + fn;

				// 迭代遍历子目录
				TraversalPath(subDir.c_str(),filePath.c_str(),fp);
			}
			else // 文件
			{
				// 如果是.mhs后缀的文件，进行加密
				if (fn.find(".mhs") == fn.length() - 4)
				{
					/*std::string subFile = lpszPath;
					subFile = subFile + "\\" + fn;*/
					std::string filePath = lpszPath;
					filePath = filePath + "\\" + fn;
					std::string strTemp = filePath + "tp";

					EncrypJsFile(filePath.c_str(), strTemp.c_str());
					DeleteFileA(filePath.c_str());
					MoveFileA(strTemp.c_str(), filePath.c_str());

					
				}

			}
		}
	}while (FindNextFileA(hFind, &FindFileData) != 0);


	FindClose(hFind);
}