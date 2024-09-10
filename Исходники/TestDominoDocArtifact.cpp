void TestDominoDocArtifact::TestName()
{
	DomDocHelper domDocHelper(TEST_ARTIFACT_FILE);   
	DominoDocArtifact validArtifact(m_spLibrary, domDocHelper.DocumentId, domDocHelper.GetVersionLabel());
	wchar_t fileName[_MAX_PATH] = {0};
	lstrcpynW(fileName, PathFindFileNameW(TEST_ARTIFACT_FILE), _MAX_PATH);
	PathRemoveExtensionW(fileName);   

	assertEquals(domDocHelper.GetFileNameWithoutExtension(), validArtifact.Name);
}