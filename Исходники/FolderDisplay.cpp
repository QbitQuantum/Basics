// Returns TRUE if two renderers are the same
LTBOOL CFolderDisplay::IsRendererEqual(RMode *pRenderer1, RMode *pRenderer2)
{
	_ASSERT(pRenderer1);
	_ASSERT(pRenderer2);

	if (_mbsicmp((const unsigned char*)pRenderer1->m_RenderDLL, (const unsigned char*)pRenderer2->m_RenderDLL) != 0)
	{
        return LTFALSE;
	}

	if (_mbsicmp((const unsigned char*)pRenderer1->m_InternalName, (const unsigned char*)pRenderer2->m_InternalName) != 0)
	{
        return LTFALSE;
	}

	if (_mbsicmp((const unsigned char*)pRenderer1->m_Description, (const unsigned char*)pRenderer2->m_Description) != 0)
	{
        return LTFALSE;
	}

	if (pRenderer1->m_Width != pRenderer2->m_Width)
	{
        return LTFALSE;
	}

	if (pRenderer1->m_Height != pRenderer2->m_Height)
	{
        return LTFALSE;
	}

	if (pRenderer1->m_BitDepth != pRenderer2->m_BitDepth)
	{
        return LTFALSE;
	}

    return LTTRUE;
}