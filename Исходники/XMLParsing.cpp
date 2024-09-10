void queryNodes()
{
    HRESULT hr = S_OK;
    IXMLDOMDocument *pXMLDom = NULL;
    IXMLDOMNodeList *pNodes = NULL;
    IXMLDOMNode *pNode = NULL;

    BSTR bstrQuery1 = NULL;
    BSTR bstrQuery2 = NULL;
    BSTR bstrNodeName = NULL;
    BSTR bstrNodeValue = NULL;
    VARIANT_BOOL varStatus;
    VARIANT varFileName;
    VariantInit(&varFileName);

    CHK_HR(CreateAndInitDOM(&pXMLDom));

    CHK_HR(VariantFromString(L"stocks.xml", varFileName));
    CHK_HR(pXMLDom->load(varFileName, &varStatus));
    if (varStatus != VARIANT_TRUE)
    {
        CHK_HR(ReportParseError(pXMLDom, "Failed to load DOM from stocks.xml."));
    }

    // Query a single node.
    bstrQuery1 = SysAllocString(L"//stock[1]/*");
    CHK_ALLOC(bstrQuery1);
    CHK_HR(pXMLDom->selectSingleNode(bstrQuery1, &pNode));
    if (pNode)
    {
        printf("Result from selectSingleNode:\n");
        CHK_HR(pNode->get_nodeName(&bstrNodeName));
        printf("Node, <%S>:\n", bstrNodeName);
        SysFreeString(bstrNodeName);

        CHK_HR(pNode->get_xml(&bstrNodeValue));
        printf("\t%S\n\n", bstrNodeValue);
        SysFreeString(bstrNodeValue);
        SAFE_RELEASE(pNode);
    }
    else
    {
        CHK_HR(ReportParseError(pXMLDom, "Error while calling selectSingleNode."));
    }

    // Query a node-set.
    bstrQuery2 = SysAllocString(L"//stock[1]/*");
    CHK_ALLOC(bstrQuery2);
    CHK_HR(pXMLDom->selectNodes(bstrQuery2, &pNodes));
    if(pNodes)
    {
        printf("Results from selectNodes:\n");
        //get the length of node-set
        long length;
        CHK_HR(pNodes->get_length(&length));
        for (long i = 0; i < length; i++)
        {
            CHK_HR(pNodes->get_item(i, &pNode));
            CHK_HR(pNode->get_nodeName(&bstrNodeName));
			/*if(0== wcscmp(bstrNodeValue, L"symbol"))
			{
				 
			}
           */
			printf("Node (%d), <%S>:\n", i, bstrNodeName);
            SysFreeString(bstrNodeName);

            CHK_HR(pNode->get_xml(&bstrNodeValue));
			
            printf("\t%S\n", bstrNodeValue);
            SysFreeString(bstrNodeValue);
            SAFE_RELEASE(pNode);
        }
    }
    else
    {
        CHK_HR(ReportParseError(pXMLDom, "Error while calling selectNodes."));
    }

CleanUp:
    SAFE_RELEASE(pXMLDom);
    SAFE_RELEASE(pNodes);
    SAFE_RELEASE(pNode);
    SysFreeString(bstrQuery1);
    SysFreeString(bstrQuery2);
    SysFreeString(bstrNodeName);
    SysFreeString(bstrNodeValue);
    VariantClear(&varFileName);
}