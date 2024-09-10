BExtractorDoc::~BExtractorDoc()
{
	if (m_hdd)
	{
		DrawDibClose(m_hdd);
		m_hdd = NULL;
	}
	DeleteContents();
}