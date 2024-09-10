void TestDocReader::TestGetMainDocText()
{
	DocReader dr;
	dr.OpenFile(TEST_HDRFTN_DOC);
	assertTest(dr.GetMainDocumentText() == L"A little\02 test.\r");
}