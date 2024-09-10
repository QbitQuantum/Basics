ULONG 	CSignalGeneratorDlg::Release()
{
	ULONG newRefValue = _InterlockedDecrement((volatile long*)&m_refCount);

	if (newRefValue == 0)
		delete this;
	return newRefValue;
}