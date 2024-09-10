	void readTriangles(MSXML2::IXMLDOMNodePtr mesh, geometry_t &geometry)
	{
		MSXML2::IXMLDOMNodeListPtr polyLists = mesh->selectNodes("r:polylist"); // blender
		MSXML2::IXMLDOMNodePtr p;

		if (polyLists->length == 0)
			polyLists = mesh->selectNodes("r:triangles"); // 3dsmax

		for (int i = 0; i < polyLists->length; i++)
		{
			MSXML2::IXMLDOMNodePtr polylist = polyLists->item[i];
			MSXML2::IXMLDOMNodePtr p = polylist->selectSingleNode("r:p");
			if (p == NULL) continue;

			geometry.vertexOffset.push_back(-1);
			geometry.normalOffset.push_back(-1);
			geometry.texcoordOffset.push_back(-1);

			MSXML2::IXMLDOMNodeListPtr inputList = polylist->selectNodes("r:input");
			for (int j = 0; j < inputList->length; j++)
			{
				MSXML2::IXMLDOMNodePtr input = inputList->Getitem(j);
				MSXML2::IXMLDOMNamedNodeMapPtr attributes = input->attributes;

				string semantic = (_bstr_t)_wcslwr((wchar_t *)attributes->getNamedItem("semantic")->text);
				int offset = _wtoi(attributes->getNamedItem("offset")->text);

				if (semantic == "vertex")
					geometry.vertexOffset[geometry.vertexOffset.size() - 1] = offset;
				else if (semantic == "normal")
					geometry.normalOffset[geometry.normalOffset.size() - 1] = offset;
				else if (semantic == "texcoord")
					geometry.texcoordOffset[geometry.texcoordOffset.size() - 1] = offset;
			}

			vector<int> v = readValues<int>(p);
			geometry.triangles.push_back(v);
		}
	}