void TestCOMLayer::TestSaveDocument()
{
	WSDocNonCom wsdDocIn;
	wsdDocIn.SetAuthor(CStdString(_T("Ted")));
	wsdDocIn.SetClass(CStdString(_T("Russell")));
	wsdDocIn.SetDescription(CStdString(_T("Mr Fluffy")));
	wsdDocIn.SetDocId(CStdString(_T("ECR")));
	wsdDocIn.SetExtension(CStdString(_T("Legs")));
	wsdDocIn.SetFileSizehigh(24);
	wsdDocIn.SetFileSizeLow(6);
	wsdDocIn.SetFlags(0x54408);
	wsdDocIn.SetLocalFile(CStdString(_T("Digger")));
	wsdDocIn.SetModifiedTime(20011109.072835);
	wsdDocIn.SetOperator(CStdString(_T("Guy")));
	wsdDocIn.SetType(CStdString(_T("Rascal")));
	LOCALFILESTORELib::tagWSDOCUMENT wsDoc;
	wsdDocIn.InitializeWSDOCUMENT((WSDOCUMENT*)&wsDoc);
	HRESULT hr = m_pLFS->raw_SaveDocument(&wsDoc, 111);
	assertTest(hr == S_TEST);
	assertTest(m_pWorker->m_sLastMethodCalled == _T("SaveDocument"));
	assertTest(wsdDocIn == m_pWorker->m_wsd);
	assertTest(m_pWorker->m_lFlags == 111);
}