bool wxTextCtrl::SetForegroundColour( const wxColour& rColour )
{
    if (m_bIsMLE)
        ::WinSendMsg(GetHwnd(), MLM_SETTEXTCOLOR, (MPARAM)rColour.GetPixel(), MLE_INDEX);
    return true;
} // end of wxTextCtrl::SetForegroundColour