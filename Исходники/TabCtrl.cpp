bool wxTabCtrl::MSWOnNotify(int idCtrl, WXLPARAM lParam, WXLPARAM *result)
{
    wxTabEvent event(wxEVT_NULL, m_windowId);
    wxEventType eventType wxDUMMY_INITIALIZE(wxEVT_NULL);
    NMHDR* hdr1 = (NMHDR*) lParam;
    switch ( hdr1->code )
    {
        case TCN_SELCHANGE:
            eventType = wxEVT_COMMAND_TAB_SEL_CHANGED;
            break;

        case TCN_SELCHANGING:
            eventType = wxEVT_COMMAND_TAB_SEL_CHANGING;
            break;

#ifndef __WXWINCE__
        case TTN_NEEDTEXT:
        {
            // TODO
//            if (!tool->m_shortHelpString.empty())
//                ttText->lpszText = (char *) (const char *)tool->m_shortHelpString;
        }
#endif
        default :
            return wxControl::MSWOnNotify(idCtrl, lParam, result);
    }

    event.SetEventObject( this );
    event.SetEventType(eventType);
    event.SetInt(idCtrl) ;
    event.SetSelection(idCtrl);

    return ProcessEvent(event);
}