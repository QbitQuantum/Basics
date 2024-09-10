	//add Id array to a document fragment node
	HRESULT AddIdsNode(
		    IXMLDOMDocument* pDOM, 
		    BSTR indentBstr,
		    const wchar_t* wszIdsNodeName, 
		    const wchar_t* wszIdsNodeAttribute,
		    const wchar_t* wszIdNode,
		    const std::vector<int>& ids, 
		    IXMLDOMDocumentFragment* pdf	// Release is completed outside
		)
	{
		VARIANT var;
		BSTR bstr = NULL;
		BSTR bstr_wst = SysAllocString(L"\t");
		IXMLDOMElement* pe = NULL;
		IXMLDOMDocumentFragment* pdfSub = NULL;
		IXMLDOMAttribute *pa = NULL;
		IXMLDOMAttribute *pa1 = NULL;

        HRESULT hr = S_OK;
		do
		{
			//create a Node to hold ids.
			bstr = SysAllocString(wszIdsNodeName);
			HR_SUCCESSCALL( pDOM->createElement(bstr, &pe), hr );
			SAFE_BSTR_RELEASE(bstr);

			//create a attribute for the <wszIdsNodeName> element, and
			//assign the element num as the attribute value.
			
			//get ids num string
			size_t idsNum = ids.size();
			const int radix = 10;
			const size_t sizeOfstr = 30;
			wchar_t wszIdsNumString[sizeOfstr] = {0};
			_ultow_s(static_cast<unsigned long>(idsNum), wszIdsNumString, sizeOfstr, radix);

			//put num string into attribute
			bstr = SysAllocString(wszIdsNodeAttribute);
			VariantInit(&var);
			V_BSTR(&var) = SysAllocString(wszIdsNumString);
			V_VT(&var) = VT_BSTR;

			HR_SUCCESSCALL( pDOM->createAttribute(bstr, &pa), hr );
			HR_SUCCESSCALL( pa->put_value(var), hr );
			HR_SUCCESSCALL( pe->setAttributeNode(pa, &pa1), hr );

			//create a document fragment to hold ids sub-elements.
			HR_SUCCESSCALL( pDOM->createDocumentFragment(&pdfSub), hr );

			//add ids to pdfSub
			for( size_t i=0; i < idsNum; ++i )
			{
				 int id = ids[i];
				 WCHAR wszIdString[sizeOfstr] = {0};
				 _itow_s(id, wszIdString, sizeOfstr, radix);

				 //add white space before <id>
				 HR_SUCCESSCALL( AddWhiteSpaceToNode(pDOM, indentBstr, pdfSub), hr );
				 HR_SUCCESSCALL( AddWhiteSpaceToNode(pDOM, bstr_wst, pdfSub), hr );
				 HR_SUCCESSCALL( AddSubNodeToDocumentFragment(pDOM, wszIdNode, wszIdString, pdfSub), hr );
			}

            //test whether it is successful in "add ids to pdfSub"
			HR_SUCCESSCALL( hr, hr );

			//add ids array to document fragment node
			HR_SUCCESSCALL( AppendChildToParent(pdfSub, pe), hr );
			HR_SUCCESSCALL( AddWhiteSpaceToNode(pDOM, indentBstr, pe), hr );
			HR_SUCCESSCALL( AppendChildToParent(pe, pdf), hr );
			
		}while(0);

        //release the com objects
		SAFE_COM_RELEASE(pa1);
		SAFE_COM_RELEASE(pa);
		SAFE_COM_RELEASE(pdfSub);
		SAFE_COM_RELEASE(pe);

		//release the bstr and variant
        SAFE_BSTR_RELEASE(bstr);
        SAFE_BSTR_RELEASE(bstr_wst);
        VariantClear(&var);

		return hr;
	}