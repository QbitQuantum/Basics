CRect CRevisionGraphWnd::GetViewRect()
{
    CRect result;
    result.UnionRect (GetClientRect(), GetGraphRect());
    return result;
}