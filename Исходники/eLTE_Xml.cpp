bool CXml::MkAndFindElemEx(const char *pszElemPath)
{
	// 创建临时变量
	
	char* token;
	const char* seps = "/"; // 字符串分隔符
	bool returnFlag = true;

	// 检查传入的路径是否为空
	CHECK_POINTER(pszElemPath,true);

	// 将xml的指针指向根节点
	(void)this->GetBasePos();

	// 创建临时字符串
    unsigned int iNewStrLen = strlen(pszElemPath) + 1;
    char* pszPath = NULL;
    SAFE_NEW_A(pszPath, char, iNewStrLen);
    CHECK_POINTER(pszPath, false);
    memset(pszPath, 0, iNewStrLen);
    char* pszTmpPath = pszPath;    

	// 复制字符串
	strncpy(pszTmpPath, pszElemPath, iNewStrLen);
	//strcpy(pszTmpPath,pszElemPath);
    char *saveptr = NULL;
	token = STRTOK( pszTmpPath, seps, &saveptr);
	std::string pszParentNode = "";
	while( token != NULL )
	{
		// 当前指针指向的节点名称
		const char* curNodeName = this->GetElem();
		char* pszTmpNode = strstr(token,"[");
		if(NULL != pszTmpNode)
		{   
			// 处理多个同名节点的情况
			int index = atoi(pszTmpNode + 1);
			std::string  strTemp(token,static_cast<unsigned int>(pszTmpNode - token));
            if(NULL == curNodeName)
            {
                 (void)this->AddElem(strTemp.c_str());
            }
			if(!this->FindElem(strTemp.c_str()))
			{
				returnFlag = false;
				break;

				//// 如果发现没有此节点则创建该节点
    //            if(0 != strcmp(curNodeName,pszParentNode.c_str()))//lint !e527
				//{
    //                 (void)this->AddElem(strTemp.c_str());
				//}else
				//{
    //                 (void)this->AddChildElem(strTemp.c_str());
				//}
    //            (void)this->FindElem(strTemp.c_str());
			}

			if(!this->MkAndNextElemEx(index))
			{
				returnFlag = false;
				break;
			}
			// 记录当前节点为上一节点的父节点
		    pszParentNode = strTemp;
		}
		else
		{
            if(NULL == curNodeName)
            {
                (void)this->AddElem(token);
            }
			// 处理单节点的情况
			if(!this->FindElem(token))
			{
                if (NULL != curNodeName)
                {
				    if(0 != strcmp(curNodeName,pszParentNode.c_str()))
				    {
                         (void)this->AddElem(token);
				    }else
				    {
                         (void)this->AddChildElem(token);
				    }
                }
                (void)this->FindElem(token);
			}
			// 记录当前节点为上一节点的父节点
		    pszParentNode = token;
		}

		// 进入该节点
		(void)this->IntoElem();

		// Get next token: 
		token = STRTOK( NULL, seps, &saveptr ); 
	}
    SAFE_DELETE_A(pszPath);//lint !e424 !e774 !e1775
    return returnFlag;//lint !e438
  //return false;
}