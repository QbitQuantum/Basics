CIDataObject::~CIDataObject()
{
	for(int i = 0; i < m_StgMedium.GetSize(); ++i)
	{
		ReleaseStgMedium(m_StgMedium[i]);
		delete m_StgMedium[i];
	}
	for(int j = 0; j < m_ArrFormatEtc.GetSize(); ++j)
		delete m_ArrFormatEtc[j];
}