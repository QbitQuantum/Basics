void PCB_BASE_FRAME::StartMoveTexteModule( TEXTE_MODULE* Text, wxDC* DC )
{
    if( Text == NULL )
        return;

    MODULE *Module = static_cast<MODULE*>( Text->GetParent() );

    Text->SetFlags( IS_MOVED );
    Module->SetFlags( IN_EDIT );

    MoveVector.x = MoveVector.y = 0;

    TextInitialPosition    = Text->GetTextPos();
    TextInitialOrientation = Text->GetTextAngle();

    // Center cursor on initial position of text
    SetCrossHairPosition( TextInitialPosition );
    m_canvas->MoveCursorToCrossHair();

    SetMsgPanel( Text );
    SetCurItem( Text );
    m_canvas->SetMouseCapture( Show_MoveTexte_Module, AbortMoveTextModule );
    m_canvas->CallMouseCapture( DC, wxDefaultPosition, true );
}