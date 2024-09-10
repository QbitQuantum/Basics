/*******************************************************************************
  Function Name  : pomGetParentWindow
  Input(s)       : -
  Output         : CWnd * - Pointer to CGraphChildFrame
  Functionality  : This Function will return parent window pointer. That is
                   pointer to CGraphChildFrame. This will return NULL incase of
                   failure
  Member of      : CGraphBottomView
  Author(s)      : ArunKumar K
  Date Created   : 04.11.2010
  Modifications  :
*******************************************************************************/
CWnd* CGraphBottomView::pomGetParentWindow() const
{
    CWnd* pWnd = NULL;
    // Get Splitter window pointer
    pWnd = GetParent();
    // Get CGraphChildFrame pointer from Splitter window pointer
    if( pWnd != NULL )
    {
        pWnd = pWnd->GetParent();
    }
    if( pWnd != NULL )
    {
        pWnd = pWnd->GetParent();
    }

    // Return CGraphChildFrame pointer or NULL incase of failure
    return pWnd;
}