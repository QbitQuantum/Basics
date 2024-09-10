void TestCloseDocument::TestFailIfLockedByOther()
{
	DocProviderWorker	objWorker;
	WSDocNonCom			wsDoc;
	DocumentID			docTarget(DocumentID::GenerateIdFromFilePath(sTestOriginalFileName));
	
	wsDoc.SetDescription(docTarget.GetDescription());
	wsDoc.SetLocalFile(docTarget.GetWorkingFile());
	assertTest(objWorker.ImportDocument(wsDoc, false) == S_OK);
	m_wsImportedDoc = wsDoc;

	LockManager lckMngr;
	assertTest(lckMngr.CreateLock(wsDoc.GetDocId(),_T("poptart")) == S_OK);

	assertTest(objWorker.CloseDocument(wsDoc,0) == S_OK);

	wsDoc.SetFlags(wsDoc.GetFlags()|DOCUMENT_LOCKED_BY_US);
	
	assertTest(objWorker.CloseDocument(wsDoc,0) == E_DOCUMENT_LOCKED_BY_ANOTHER);

	lckMngr.RemoveLock(wsDoc.GetDocId(),_T("poptart"));
}