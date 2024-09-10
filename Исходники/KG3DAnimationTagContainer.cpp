void KG3DAnimationTagContainer::Clear()
{
	OnExit();

	SAFE_RELEASE(m_pClip);
    for (size_t i = 0; i < m_vecTags.size(); i++)
    {
        SAFE_DELETE(m_vecTags[i].pTag)
    }

	m_vecTags.clear();
    m_szAnimationName[0] = '\0';
    m_bModifyFlag = FALSE;
	m_IsLoaded = FALSE;
}