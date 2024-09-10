void FB_Frame::OnMenuOpen ( wxMenuEvent& event )
{
    if ( event.GetMenu() == m_EditMenu )
    {
        FB_STC * stc = 0;
        if( m_Code_areaTab != 0 )
            stc = reinterpret_cast<FB_STC *>( m_Code_areaTab->GetCurrentPage() );

        #define _ENABLE( id, func ) m_EditMenu->Enable( id, ( stc != 0 ) ? stc -> func : false )
            _ENABLE( wxID_UNDO,                 CanUndo() );
            _ENABLE( wxID_REDO,                 CanRedo() );
            _ENABLE( wxID_COPY,                 HasSelection() );
            _ENABLE( wxID_CUT,                  HasSelection() );
            _ENABLE( wxID_PASTE,                CanPaste() );
            _ENABLE( wxID_SELECTALL,            GetLength() );
            _ENABLE( fbideID_SelectLine,        GetLength() );
            _ENABLE( fbideID_CommentBlock,      CanComment() );
            _ENABLE( fbideID_UncommentBlock,    CanComment() );
        #undef _ENABLE
        m_EditMenu->Enable(wxID_JUSTIFY_RIGHT,    ( stc ) ? true : false );
        m_EditMenu->Enable(wxID_JUSTIFY_LEFT,     ( stc ) ? true : false );
    }
}