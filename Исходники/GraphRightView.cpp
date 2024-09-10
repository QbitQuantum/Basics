/*******************************************************************************
  Function Name  : pomGetParentWindow
  Input(s)       : -
  Output         : CWnd * - Pointer to CGraphChildFrame
  Functionality  : This Function will return parent window pointer. That is
                   pointer to CGraphChildFrame. This will return nullptr incase of
                   failure
  Member of      : CGraphRightView
  Author(s)      : ArunKumar K
  Date Created   : 08.11.2010
  Modifications  :
*******************************************************************************/
CWnd* CGraphRightView::pomGetParentWindow() const
{
    CWnd* pWnd = nullptr;
    // Get Splitter window pointer
    pWnd = GetParent();
    // Get CGraphChildFrame pointer from Splitter window pointer
    if( pWnd != nullptr )
    {
        pWnd = pWnd->GetParent();
    }
    if( pWnd != nullptr )
    {
        pWnd = pWnd->GetParent();
    }

    // Return CGraphChildFrame pointer or nullptr incase of failure
    return pWnd;
}