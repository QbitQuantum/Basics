int main(int argc, const char* argv[])
{
	if (argc < 1)
	{
		showUseage();
		return 0;
	}
	const char* pszInputFileName = NULL;
	const char* pszOutputFileName = NULL;
	
	for (int i=1; i<argc; i++)
	{
		if (_stricmp(argv[i], "-i")==0 && i+1<argc)
		{
			pszInputFileName = argv[i+1];
			i++;
		}
		else if (_stricmp(argv[i], "-o")==0 && i+1<argc)
		{
			pszOutputFileName = argv[i+1];
			i++;
		}		
	}
	
	if (pszInputFileName==NULL || pszOutputFileName==NULL)
	{
		showUseage();
		return 0;	
	}
	
	std::ifstream fin(pszInputFileName);
	std::ofstream fout(pszOutputFileName);
	if (!fin.is_open())
	{
		std::cout << "Error(" << errno << 
			") can't open " << pszInputFileName << std::endl;
		return -1;
	}
	
	if (!fout.is_open())
	{
		std::cout << "Error(" << errno << 
			") can't open " << pszOutputFileName << std::endl;
		return -2;
	}
	
	time_t tBegin = time(NULL);
	
	std::string line;
	unsigned long long idx = 0;
	while ( getline( fin, line))
	{
		MD5_CTX ctx = {0};
		MD5_Init(&ctx);
		MD5_Update(&ctx, line.c_str(), line.size());
		unsigned char digest[16] = {0};
		MD5_Final(digest, &ctx);
		
		char szMd5[32] = {0};
		digest2String(digest, szMd5);
	#if 0
		std::cout << "[" << idx << "]";
		std::cout << " MD5(";
		std::cout << line.c_str();
		std::cout << ")= " << szMd5 << std::endl;
	#endif
		fout << line << "\t\t" << szMd5 << std::endl;
		idx++;
	}
	fin.close();
	fout.close();
	
	time_t tEnd = time(NULL);
	unsigned int tCost = tEnd - tBegin;
	
	std::cout << "cal " << idx << "md5s cost" << tCost
		<< " seconds" << std::endl; 
	
    return 0;
}