LPMONIKER COleDocument::GetMoniker(OLEGETMONIKER /*nAssign*/)
{
	USES_CONVERSION;

	ASSERT_VALID(this);

	// no moniker for untitled documents
	if (m_strPathName.IsEmpty())
		return NULL;

	// return file moniker based on current path name
	LPMONIKER lpMoniker;
	CreateFileMoniker(T2COLE(m_strPathName), &lpMoniker);
	return lpMoniker;
}