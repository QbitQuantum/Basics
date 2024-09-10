void HTMLIFrameElement::goBack()
{
	ASSERT(0);
#if 0
	if (m_pFrameContent)
	{
		CComPtr<IHlink> pHlink;
		m_pFrameContent->m_hlinkBrowseContext->GetHlink(HLID_PREVIOUS, &pHlink);
		if (pHlink)
		{
		//	CComPtr<IBindCtx> bctx;
		//	CreateBindCtx(0, &bctx);
			ErrorCode hr = HlinkNavigate(pHlink, static_cast<IHlinkFrame*>(m_pFrameContent/*->m_pViewSite*/), HLNF_NAVIGATINGBACK, NULL/*bctx*/, NULL, m_pFrameContent->m_hlinkBrowseContext);
		}
		//ErrorCode hr = ::HlinkGoBack(m_spUnknown);
	}
#endif
}