// Returns an index into m_rendererArray for this renderer.
// -1 is returned if it cannot be found
int CMenuDisplay::GetRendererIndex(RMode *pMode)
{
	assert(pMode);
	if (!pMode)
	{
		return -1;
	}

	// Find out if this renderer already exists in the array
	int nRenderIndex=-1;

	unsigned int i;
	for (i=0; i < m_rendererArray.GetSize(); i++)
	{
		if (_mbsicmp((const unsigned char*)m_rendererArray[i].m_description, (const unsigned char*)pMode->m_Description) == 0 &&
			_mbsicmp((const unsigned char*)m_rendererArray[i].m_renderDll, (const unsigned char*)pMode->m_RenderDLL) == 0)
		{
			nRenderIndex=i;
			break;
		}
	}

	return nRenderIndex;
}