int EDIT_TOOL::Properties( TOOL_EVENT& aEvent )
{
    const SELECTION& selection = m_selectionTool->GetSelection();
    PCB_BASE_EDIT_FRAME* editFrame = getEditFrame<PCB_BASE_EDIT_FRAME>();

    if( !makeSelection( selection ) )
    {
        setTransitions();

        return 0;
    }

    // Properties are displayed when there is only one item selected
    if( selection.Size() == 1 )
    {
        // Display properties dialog
        BOARD_ITEM* item = selection.Item<BOARD_ITEM>( 0 );

        // Check if user wants to edit pad or module properties
        if( item->Type() == PCB_MODULE_T )
        {
            VECTOR2D cursor = getViewControls()->GetCursorPosition();

            for( D_PAD* pad = static_cast<MODULE*>( item )->Pads(); pad; pad = pad->Next() )
            {
                if( pad->ViewBBox().Contains( cursor ) )
                {
                    // Turns out that user wants to edit a pad properties
                    item = pad;
                    break;
                }
            }
        }

        std::vector<PICKED_ITEMS_LIST*>& undoList = editFrame->GetScreen()->m_UndoList.m_CommandsList;

        // Some of properties dialogs alter pointers, so we should deselect them
        m_toolMgr->RunAction( COMMON_ACTIONS::selectionClear, true );
        STATUS_FLAGS flags = item->GetFlags();
        item->ClearFlags();

        // It is necessary to determine if anything has changed
        PICKED_ITEMS_LIST* lastChange = undoList.empty() ? NULL : undoList.back();

        // Display properties dialog
        editFrame->OnEditItemRequest( NULL, item );

        PICKED_ITEMS_LIST* currentChange = undoList.empty() ? NULL : undoList.back();

        if( lastChange != currentChange )        // Something has changed
        {
            processChanges( currentChange );

            updateRatsnest( true );
            getModel<BOARD>()->GetRatsnest()->Recalculate();
            item->ViewUpdate();

            m_toolMgr->RunAction( COMMON_ACTIONS::pointEditorUpdate, true );
        }

        item->SetFlags( flags );
    }

    setTransitions();

    return 0;
}