void DesignerWindow::HighlightSelection( wxDC& dc )
{
    // do not highlight if AUI is used in floating mode
    VisualEditor *editor = wxDynamicCast( GetParent(), VisualEditor );
    if( editor && editor->m_auimgr )
    {
        wxWindow *windowItem =  wxDynamicCast( m_selItem, wxWindow );
        while( windowItem )
        {
            wxAuiPaneInfo info = editor->m_auimgr->GetPane( windowItem );
            if( info.IsOk() )
            {
                if( info.IsFloating() ) return;
                else break;
            }
            windowItem = windowItem->GetParent();
        }
    }

    wxSize size;
    PObjectBase object = m_selObj.lock();
    if ( m_selSizer )
    {
        wxPoint point = m_selSizer->GetPosition();
        size = m_selSizer->GetSize();
        wxPen bluePen( *wxBLUE, 1, wxSOLID );
        dc.SetPen( bluePen );
        dc.SetBrush( *wxTRANSPARENT_BRUSH );
        PObjectBase sizerParent = object->FindNearAncestorByBaseClass( wxT("sizer") );
        if( !sizerParent ) sizerParent = object->FindNearAncestorByBaseClass( wxT("gbsizer") );
        if ( sizerParent && sizerParent->GetParent() )
        {
            DrawRectangle( dc, point, size, sizerParent );
        }
    }

    if ( m_selItem )
    {
        wxPoint point;
        bool shown;

        wxWindow* windowItem = wxDynamicCast( m_selItem, wxWindow );
        wxSizer* sizerItem = wxDynamicCast( m_selItem, wxSizer );
        if ( NULL != windowItem )
        {
            point = windowItem->GetPosition();
            size = windowItem->GetSize();
            shown = windowItem->IsShown();
        }
        else if ( NULL != sizerItem )
        {
            point = sizerItem->GetPosition();
            size = sizerItem->GetSize();
            shown = true;
        }
        else
        {
            return;
        }

        if ( shown )
        {
            wxPen redPen( *wxRED, 1, wxSOLID );
            dc.SetPen( redPen );
            dc.SetBrush( *wxTRANSPARENT_BRUSH );
            DrawRectangle( dc, point, size, object );
        }
    }
}