CMFCDCView::~CMFCDCView()
{
	if (m_hMetaFile)
	{
		//5 删除MetaFile
		DeleteMetaFile(m_hMetaFile);
	}
}