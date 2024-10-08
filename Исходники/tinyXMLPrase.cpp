bool tinyXMLPrase()
{
	bool succeed = false;

	//×ª»»¿í×Ö½Úµ½char
	setlocale(LC_ALL, "zh-CN");
	size_t len = wcslen(strFile) + 1;
	size_t converted = 0;
	char *CStr;
	CStr = (char*)malloc(len*sizeof(char)*2);
	wcstombs_s(&converted, CStr, len*2, strFile, len*2);

	TiXmlDocument * myDocument = new TiXmlDocument(CStr);

	myDocument->LoadFile();

	if (myDocument->Error())
	{
		MessageBox(theHWND, L"XML¶ÁÈ¡Ê§°Ü", L"´íÎó", 0);
		return false;
	}
	
	try
	{
		TiXmlElement * RootElement = myDocument->RootElement();

		for (TiXmlElement * TestCase = RootElement->FirstChildElement();
				TestCase != NULL;
				TestCase = TestCase->NextSiblingElement())
		{
			int ID;
			TestCase->QueryIntAttribute("ID", &ID);
			if (ID != SETTING_XML_TESTCASE)
			{
				TestCase->Clear();
				continue;
			}
				

			succeed = true;

			for (TiXmlElement * DataNode = TestCase->FirstChildElement();
				DataNode != NULL;
				DataNode = DataNode->NextSiblingElement())
			{
				if (strcmp(DataNode->Value(), "Entity") == 0)
				{
					if (strcmp(DataNode->Attribute("Type"), "Line") == 0)
					{
						Line * line = (Line *)mempool->Alloc(sizeof(Line));

						for (TiXmlElement * pointNode = DataNode->FirstChildElement();
							pointNode != NULL;
							pointNode = pointNode->NextSiblingElement())
						{
							if (strcmp(pointNode->Value(), "StartPoint") == 0)
							{
								sscanf_s(pointNode->GetText(), "%hd,%hd", &line->x1, &line->y1);
							}
							else if (strcmp(pointNode->Value(), "EndPoint") == 0)
							{
								sscanf_s(pointNode->GetText(), "%hd,%hd", &line->x2, &line->y2);
							}
						}

						lineList.push_back(line);
					}
					else if (strcmp(DataNode->Attribute("Type"), "Circle") == 0)
					{
						Circle * circle = (Circle *)mempool->Alloc(sizeof(Circle));;

						for (TiXmlElement * pointNode = DataNode->FirstChildElement();
							pointNode != NULL;
							pointNode = pointNode->NextSiblingElement())
						{
							if (strcmp(pointNode->Value(), "CenterPoint") == 0)
							{
								sscanf_s(pointNode->GetText(), "%hd,%hd", &circle->x, &circle->y);
							}
							else if (strcmp(pointNode->Value(), "Radius") == 0)
							{
								sscanf_s(pointNode->GetText(), "%hd", &circle->r);
							}
						}

						circleList.push_back(circle);
					}
				}
				else if (strcmp(DataNode->Value(), "Boundary") == 0)
				{
					for (TiXmlElement * pointNode = DataNode->FirstChildElement();
						pointNode != NULL;
						pointNode = pointNode->NextSiblingElement())
					{
						if (strcmp(pointNode->Value(), "Vertex") != 0)
							continue;

						Point * point = (Point *)mempool->Alloc(sizeof(Point));
						sscanf_s(pointNode->GetText(), "%hd,%hd", &point->x, &point->y);
						
						polygonList.push_back(point);
					}
				}
				else
				{
					//Òì³££¬»¹ÊÇºöÂÔÁË°É
				}
			}
		}
	}
	catch (...)
	{
		myDocument->Clear();
		delete(myDocument);
		MessageBox(theHWND, L"Î´Öª´íÎó", L"´íÎó", 0);
		return false;
	}
	

	if (!succeed)
	{
		myDocument->Clear();
		delete(myDocument);
		MessageBox(theHWND, L"Ã»ÓÐÕÒµ½Êý¾Ý½Úµã", L"´íÎó", 0);
		return false;
	}
		
	myDocument->Clear();
	delete(myDocument);

	return true;
}