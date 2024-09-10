tagSIZE ILayoutItem::GetRootOffset()
{
    CSize szOffset(0, 0);
    ILayout* pLayout = GetLayout();
    while (pLayout != NULL) {
        CRect rc = pLayout->GetRect();
        szOffset.cx += rc.left;
        szOffset.cy += rc.top;
    }

    return szOffset;
}