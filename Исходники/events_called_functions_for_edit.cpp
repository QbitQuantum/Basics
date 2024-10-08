void SCH_EDIT_FRAME::OnCopySchematicItemRequest( wxCommandEvent& event )
{
    SCH_ITEM * curr_item = GetScreen()->GetCurItem();

    if( !curr_item || curr_item->GetFlags() )
        return;

    INSTALL_UNBUFFERED_DC( dc, m_canvas );

    switch( curr_item->Type() )
    {
    case SCH_COMPONENT_T:
    {
        SCH_COMPONENT* newitem;
        newitem = new SCH_COMPONENT( *( (SCH_COMPONENT*) curr_item ) );
        newitem->SetTimeStamp( GetNewTimeStamp() );
        newitem->ClearAnnotation( NULL );
        newitem->SetFlags( IS_NEW );
        // Draw the new part, MoveItem() expects it to be already on screen.
        newitem->Draw( m_canvas, &dc, wxPoint( 0, 0 ), g_XorMode );
        PrepareMoveItem( newitem, &dc );
    }
    break;

    case SCH_TEXT_T:
    case SCH_LABEL_T:
    case SCH_GLOBAL_LABEL_T:
    case SCH_HIERARCHICAL_LABEL_T:
    {
        SCH_TEXT* newitem = (SCH_TEXT*) curr_item->Clone();
        newitem->SetFlags( IS_NEW );
        // Draw the new item, MoveItem() expects it to be already on screen.
        newitem->Draw( m_canvas, &dc, wxPoint( 0, 0 ), g_XorMode );
        PrepareMoveItem( newitem, &dc );
    }
        break;

    default:
        break;
    }
}