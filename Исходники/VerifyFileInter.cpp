extern "C" DLL_EXPORT int getFileVerify(std::vector<std::string> &infile, std::vector<Result> &outre)
{
	__int64 finishedSize = 0;
	std::vector<__int64> fSizes(infile.size());
	std::string strFileSize;
	std::string strFileMD5;
	std::string strFileSHA1;
	std::string strFileSHA256;
	std::string strFileCRC32;

	//开始计算,循环处理每个文件
	for (int i = 0; i < infile.size(); i++)
	{
		// Declaration for calculator
		char* path = const_cast<char*>(infile[i].c_str());
		__int64 fsize = 0;
		finishedSize = 0;
		DataBuffer databuf;

		MD5_CTX mdContext; // MD5 context

		CSHA1 sha1; // SHA1 object
		char strSHA1[256];

		SHA256_CTX sha256Ctx; // SHA256 context
		std::string strSHA256 ="";

		unsigned long ulCRC32; // CRC32 context

		ResultData result;
		result.strPath = infile[i];
		//打开文件
		FILE *fp = fopen(infile[i].c_str(), "rb+");
		if (fp != NULL)
		{
			//成功打开文件
			MD5Init(&mdContext, 0); // MD5开始
			sha1.Reset(); // SHA1开始
			sha256_init(&sha256Ctx); // SHA256开始
			crc32Init(&ulCRC32); // CRC32开始

			//获取文件信息
			std::string lastModifiedTime;
			struct _stat64 info;
			_wstat64(AnsiToUnicode(infile[i].c_str()), &info);
			fsize = info.st_size;
			API_TimeToStringEX(lastModifiedTime, info.st_mtime);
			do
			{
				//读取文件
				databuf.datalen = fread(databuf.data, 1, DataBuffer::preflen, fp);

				MD5Update(&mdContext, databuf.data, databuf.datalen); // MD5更新
				sha1.Update(databuf.data, databuf.datalen); // SHA1更新
				sha256_update(&sha256Ctx, databuf.data, databuf.datalen); // SHA256更新
				crc32Update(&ulCRC32, databuf.data, databuf.datalen); // CRC32更新

				finishedSize += databuf.datalen;

				//设置偏移
				if (databuf.datalen >= DataBuffer::preflen)
					_fseeki64(fp, finishedSize, SEEK_SET);
			} while (databuf.datalen >= DataBuffer::preflen);
			fclose(fp);//关闭文件
			MD5Final(&mdContext); // MD5完成
			sha1.Final(); // SHA1完成
			sha256_final(&sha256Ctx); // SHA256完成
			crc32Finish(&ulCRC32); //CRC32完成

			//格式化校验码
			char _tempmd5[256] = { '\0' };
			sprintf(_tempmd5, "%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",
				mdContext.digest[0],
				mdContext.digest[1],
				mdContext.digest[2],
				mdContext.digest[3],
				mdContext.digest[4],
				mdContext.digest[5],
				mdContext.digest[6],
				mdContext.digest[7],
				mdContext.digest[8],
				mdContext.digest[9],
				mdContext.digest[10],
				mdContext.digest[11],
				mdContext.digest[12],
				mdContext.digest[13],
				mdContext.digest[14],
				mdContext.digest[15]);
			strFileMD5 = _tempmd5;
			sha1.ReportHash(strSHA1, CSHA1::REPORT_HEX);
			strFileSHA1 = (strSHA1);
			sha256_digest(&sha256Ctx, &strSHA256);
			strFileSHA256 = strSHA256;
			//strFileCRC32.Format(_T("%08X"), ulCRC32);
			char _tempcrc[128] = { '\0' };
			sprintf(_tempcrc, "%08X", ulCRC32);
			strFileCRC32 = _tempcrc;

			result.bDone = TRUE;
			result.strPath = infile[i];
			result.ulSize = fsize;
			result.strMDate = lastModifiedTime;
			// 在没做转换前，结果都是大写的
			result.strMD5 = strFileMD5;
			result.strSHA1 = strFileSHA1;
			result.strSHA256 = strFileSHA256;
			result.strCRC32 = strFileCRC32;
			//转换大小写
		}
		else
		{
			result.bDone = FALSE;
			result.strError = "Open file error";			
		}

		outre.push_back(result);
	}
	return 0;
}