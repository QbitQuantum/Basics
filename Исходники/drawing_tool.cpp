int DRAWING_TOOL::DrawCircle( const TOOL_EVENT& aEvent )
{
    if( m_editModules )
    {
        m_frame->SetToolID( ID_MODEDIT_CIRCLE_TOOL, wxCURSOR_PENCIL, _( "Add graphic circle" ) );

        EDGE_MODULE* circle = new EDGE_MODULE( m_board->m_Modules );

        while( drawSegment( S_CIRCLE, reinterpret_cast<DRAWSEGMENT*&>( circle ) ) )
        {
            if( circle )
            {
                m_frame->OnModify();
                m_frame->SaveCopyInUndoList( m_board->m_Modules, UR_MODEDIT );
                circle->SetParent( m_board->m_Modules );
                circle->SetLocalCoord();
                m_board->m_Modules->GraphicalItems().PushFront( circle );
            }

            circle = new EDGE_MODULE( m_board->m_Modules );
        }
    }
    else // !m_editModules case
    {
        m_frame->SetToolID( ID_PCB_CIRCLE_BUTT, wxCURSOR_PENCIL, _( "Add graphic circle" ) );

        DRAWSEGMENT* circle = new DRAWSEGMENT;

        while( drawSegment( S_CIRCLE, circle ) )
        {
            if( circle )
            {
                m_board->Add( circle );
                m_frame->OnModify();
                m_frame->SaveCopyInUndoList( circle, UR_NEW );
            }

            circle = new DRAWSEGMENT;
        }
    }

    m_frame->SetToolID( ID_NO_TOOL_SELECTED, wxCURSOR_DEFAULT, wxEmptyString );

    return 0;
}