CSize SIconWnd::GetDesiredSize(LPCRECT pRcContainer)
{
    if(!m_theIcon) return CSize();
    ICONINFO iconInfo={0};
    GetIconInfo(m_theIcon,&iconInfo);
    if(iconInfo.hbmColor) DeleteObject(iconInfo.hbmColor);
    if(iconInfo.hbmMask) DeleteObject(iconInfo.hbmMask);

    return CSize(iconInfo.xHotspot*2,iconInfo.yHotspot*2);
}