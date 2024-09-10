// helper
void TestEMFDecoding::CellTesting(RTFTable* pTable, int iIndex, int iRows, int iCols, const CStdString& sText, int iText/*==1*/)
{
	RTFCell* pCell =(RTFCell *)GetNthObject(pTable, rotCellcontent, iIndex);
	
	NUnit::Framework::Assert::IsTrue(pCell->GetColsSpanned() == iCols, "Spans incorrect cells");
	NUnit::Framework::Assert::IsTrue(pCell->GetRowsSpanned() == iRows, "Spans bad rows");
	if (sText.length() != 0)
	{
		RTFPCData* pData =(RTFPCData*)GetNthObject(pCell, rotPcdata, iText);
		CWideString s = pData->GetContent();
		NUnit::Framework::Assert::IsTrue(s == sText, "Should have the given Text");
	}
}