CComBSTR CIbnCommandWnd::BuildContactListXml()
{
    USES_CONVERSION;

    CUserCollection	UsersContactList;
    pMessenger->GetCopyContactList(UsersContactList);

    CComPtr<IXMLDOMDocument>	pTreeItemDoc	=	NULL;

    pTreeItemDoc.CoCreateInstance(CLSID_DOMDocument40, NULL, CLSCTX_INPROC_SERVER);

    VARIANT_BOOL	varSuc	=	VARIANT_FALSE;
    CComBSTR	bsDefaultXML	= L"<contactList><response></response></contactList>";

    pTreeItemDoc->loadXML(bsDefaultXML,&varSuc);

    CComPtr<IXMLDOMNode>	pRootNode;
    pTreeItemDoc->selectSingleNode(CComBSTR(L"contactList/response"),&pRootNode);

    int CLMode  = GetOptionInt(IDS_OFSMESSENGER,IDS_CLMODE,2);

    CUser* pUser=NULL;

    int GroupGlobalId = -1;
    if(POSITION pos = UsersContactList.InitIteration())
    {
        for(int i=0; UsersContactList.GetNext(pos, pUser); i++)
        {
            // Step 1. Проверить создавали ли мы группу???
            CComBSTR	GroupName =	pUser->m_strType;

            if(CLMode==2)
            {
                if(pUser->m_iStatus==S_OFFLINE||pUser->m_iStatus==S_INVISIBLE)
                {
                    GroupName	=  GetString(IDS_OFFLINE);
                }
            }

            BOOL isCheck = FALSE;

            CComBSTR bsGroupPath = L"contactList/response/group[@name='";
            bsGroupPath += GroupName;
            bsGroupPath += L"']";

            CComPtr<IXMLDOMNode>	pGroupNode;

            pTreeItemDoc->selectSingleNode(bsGroupPath,&pGroupNode);

            if(pGroupNode==NULL)
            {
                CComPtr<IXMLDOMNode>	pTmpGroupNode;

                pTreeItemDoc->createNode(CComVariant(NODE_ELEMENT),CComBSTR(L"group"),NULL,&pTmpGroupNode);

                SetAttribute(pTmpGroupNode,CComBSTR(L"name"),CComVariant(GroupName));

                pGroupNode = AppendWithSort(pRootNode, pTmpGroupNode, CComBSTR(L"text"));
            }

            // Step 3. добавить пользователя [1/28/2002]
            CComPtr<IXMLDOMNode> pUserNode;

            insertSingleNode(pGroupNode, CComBSTR(L"user"), NULL, NULL, &pUserNode);

            WCHAR buffUserId[20]	=	L"";
            _ltow(pUser->GetGlobalID(),buffUserId,10);

            WCHAR buffUserStatus[20]	=	L"";
            _ltow(pUser-> GetStatus(),buffUserStatus,10);

            insertSingleNode(pUserNode, CComBSTR(L"id"), NULL, CComBSTR(buffUserId));
            insertSingleNode(pUserNode, CComBSTR(L"login"), NULL, CComBSTR((LPCTSTR)pUser->m_strLogin));
            insertSingleNode(pUserNode, CComBSTR(L"firstName"), NULL, CComBSTR((LPCTSTR)pUser->m_strFirstName));
            insertSingleNode(pUserNode, CComBSTR(L"lastName"), NULL, CComBSTR((LPCTSTR)pUser->m_strLastName));
            insertSingleNode(pUserNode, CComBSTR(L"email"), NULL, CComBSTR((LPCTSTR)pUser->m_strEMail));
            insertSingleNode(pUserNode, CComBSTR(L"status"), NULL, CComBSTR(buffUserStatus));
        }
    }

    CComBSTR bsRetVal;
    pTreeItemDoc->get_xml(&bsRetVal);

    return bsRetVal;
}