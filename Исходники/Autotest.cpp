HRESULT CAutotest::GetAutotestStatus(PVOID* ppvOutBuf, DWORD* pdwOutSize)
{
#define HV_XML_CMD_VERSION_NO "3.0"
	
	
#define HVXML_VER 					"Ver"
#define HVXML_HVCMD					"HvCmd"
#define HVXML_HVCMDRESPOND 			"HvCmdRespond"
#define HVXML_RETCODE 				"RetCode"
#define HVXML_RETMSG 				"RetMsg"
#define HVXML_CMDNAME				"CmdName"
#define HVXML_RETURNLEN				"RetLen"

	
	if (NULL == ppvOutBuf || NULL == pdwOutSize)
	{
		SW_TRACE_DEBUG("Err: NULL == ppvOutBuf || NULL == pdwOutSize\n");
		return E_INVALIDARG;
	}
	
	if (!m_fInited)
	{
		SW_TRACE_DEBUG("Err: not inited yet!\n");
		return E_NOTIMPL;
	}

	TiXmlDocument xmlOutDoc;	
	TiXmlDeclaration *pDeclaration = NULL;
	TiXmlElement *pRootEle = NULL;

	pDeclaration = new TiXmlDeclaration("1.0","GB2312","yes");
	if (NULL == pDeclaration)
	{
		SW_TRACE_DEBUG("Err: no memory for pDeclaration\n");
		return E_OUTOFMEMORY;
	}
	xmlOutDoc.LinkEndChild(pDeclaration);

	pRootEle = new TiXmlElement(HVXML_HVCMDRESPOND);
	if (NULL == pRootEle)
	{	
		SW_TRACE_DEBUG("Err: no memory for pRootEle\n");
		return E_OUTOFMEMORY;
	}
	xmlOutDoc.LinkEndChild(pRootEle);
	
	pRootEle->SetAttribute(HVXML_VER, HV_XML_CMD_VERSION_NO);

	TiXmlElement *pReplyEle =  new TiXmlElement(HVXML_CMDNAME);
	if (NULL == pReplyEle)
	{	
		SW_TRACE_DEBUG("Err: no memory for pReplyEle\n");
		return E_OUTOFMEMORY;
	}
	pRootEle->LinkEndChild(pReplyEle);

	
	TiXmlText * pReplyText = new TiXmlText("GetAutotestProgress");
	if (NULL == pReplyText)
	{	
		SW_TRACE_DEBUG("Err: no memory for pReplyText\n");
		return E_OUTOFMEMORY;
	}
	pReplyEle->LinkEndChild(pReplyText);	


	if (0 == m_dwTestProgress)
	{	
		pReplyEle->SetAttribute(HVXML_RETCODE, 0);
		pReplyEle->SetAttribute(HVXML_RETMSG, "TestOK");
	}
	else if (1 == m_dwTestProgress)
	{
		pReplyEle->SetAttribute(HVXML_RETCODE, 0);
		pReplyEle->SetAttribute(HVXML_RETMSG, "Testing");
	}
	else if (2 == m_dwTestProgress)
	{
		pReplyEle->SetAttribute(HVXML_RETCODE, 0);
		pReplyEle->SetAttribute(HVXML_RETMSG, "TestFailed");
	}
	else
	{
		pReplyEle->SetAttribute(HVXML_RETCODE, -1);
		pReplyEle->SetAttribute(HVXML_RETMSG, "GetAutotestProgress Failed");
	}
	
	TiXmlPrinter xmlPrinter;

	xmlOutDoc.Accept(&xmlPrinter);

	*pdwOutSize = xmlPrinter.Size()+1;
	*ppvOutBuf = swpa_mem_alloc(*pdwOutSize);
	if (NULL == *ppvOutBuf)
	{
		SW_TRACE_DEBUG("Err: no memory for *ppvOutBuf!\n");
		return E_OUTOFMEMORY;
	}
	swpa_memset(*ppvOutBuf, 0, *pdwOutSize);

	swpa_strncpy((CHAR*)*ppvOutBuf, xmlPrinter.CStr(), xmlPrinter.Size());
	
	return S_OK;	
}