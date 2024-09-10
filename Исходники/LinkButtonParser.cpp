void LinkButtonParser::RemoveLinkBtnFromWindow(CEGUI::Window *Wnd)
{
    mapLinkInfo::iterator iterInfo = LinkMap.begin();
    while(iterInfo != LinkMap.end())
    {
        CEGUI::Window *pChildWin = iterInfo->first;

        if (Wnd == pChildWin->getParent())
        {
            pChildWin->destroy();
            iterInfo = LinkMap.erase(iterInfo);
            continue;
        }
        ++iterInfo;
    }
}