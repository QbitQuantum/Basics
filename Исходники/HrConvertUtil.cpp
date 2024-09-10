void HrConvertUtil::FlushDataToFile(const std::string& strOutputFile, rapidjson::Document& doc)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	doc.Accept(writer);
	std::string strJsonContent = std::string(buffer.GetString());
	strJsonContent = FormatJsonData(strJsonContent);
	
	std::string strRootPath = HrFileUtils::Instance()->GetFilePath(strOutputFile);
	std::string strFileName = HrFileUtils::Instance()->GetFileName(strOutputFile);
	std::string strSuffix = HrFileUtils::Instance()->GetFileSuffix(strOutputFile);
	filesystem::path filePath(strRootPath);
	//filePath = filePath / strFileName;
	//if (!filesystem::exists(filePath))
	//{
	//	filesystem::create_directories(filePath);
	//}
	//auto outputFilePath = filePath / (strFileName + "." + strSuffix);
	std::string strRealOutputFilePath = strOutputFile;//outputFilePath.string();
	HrFileUtils::Instance()->WriteDataToFile(strRealOutputFilePath, strJsonContent);


	auto fileTexturePath = filePath / "Texture\\";
	if (!filesystem::exists(fileTexturePath))
	{
		filesystem::create_directories(fileTexturePath);
	}
	//拷贝图片到Texture文件夹
	for (size_t nMatIndex = 0; nMatIndex < m_modelDesc.vecMaterialDataInfo.size(); ++nMatIndex)
	{
		for (int nTexIndex = 0; nTexIndex < HrModelDataInfo::HrMaterialDataInfo::TS_NUMTEXTURESLOTS; ++nTexIndex)
		{
			if (filesystem::exists(m_modelDesc.vecMaterialDataInfo[nMatIndex].m_arrTexNames[nTexIndex]))
			{
				std::string strFileName = HrFileUtils::Instance()->GetFileNameWithSuffix(m_modelDesc.vecMaterialDataInfo[nMatIndex].m_arrTexNames[nTexIndex]);
				filesystem::path dstFilePath = fileTexturePath / strFileName;
				if (filesystem::exists(dstFilePath))
					filesystem::remove(dstFilePath);
				filesystem::copy_file(m_modelDesc.vecMaterialDataInfo[nMatIndex].m_arrTexNames[nTexIndex], dstFilePath);
			}
		}
	}
}