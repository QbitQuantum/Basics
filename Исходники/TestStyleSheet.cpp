void TestStyleSheet::TestReadFromFile()
{
	DocReader dr;
	dr.OpenFile(TEST_WORD_DOC);

	StyleSheet ss(dr.GetStyleSheetLocation());

	assertTest(ss.m_STSHI.cstd == 15);

	assertTest(ss.m_styles.size() == 15);
	assertTest(ss.m_styles[0].m_sName == L"Normal");

	Style& firstStyle = ss.m_styles[0];

	assertTest(firstStyle.m_StdBase.cupx == 2);
	assertTest(firstStyle.m_vupx.size() == 2);

	UnivPropEx& firstPropEx = firstStyle.m_vupx[0];
	assertTest(firstPropEx.m_vData.size()==2);
	assertTest(firstPropEx.m_vData[0]==0);
	assertTest(firstPropEx.m_vData[1]==0);
}