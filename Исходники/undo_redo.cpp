void PCB_BASE_EDIT_FRAME::SaveCopyInUndoList( const PICKED_ITEMS_LIST& aItemsList,
                                         UNDO_REDO_T aTypeCommand, const wxPoint& aTransformPoint )
{
    PICKED_ITEMS_LIST* commandToUndo = new PICKED_ITEMS_LIST();

    commandToUndo->m_TransformPoint = aTransformPoint;

    // First, filter unnecessary stuff from the list (i.e. for multiple pads / labels modified),
    // take the first occurence of the module (we save copies of modules when one of its subitems
    // is changed).
    for( unsigned ii = 0; ii < aItemsList.GetCount(); ii++ )
    {
        ITEM_PICKER curr_picker = aItemsList.GetItemWrapper(ii);
        BOARD_ITEM* item    = (BOARD_ITEM*) aItemsList.GetPickedItem( ii );

        // For items belonging to modules, we need to save state of the parent module
        if( item->Type() == PCB_MODULE_TEXT_T || item->Type() == PCB_MODULE_EDGE_T
                || item->Type() == PCB_PAD_T )
        {
            // Item to be stored in the undo buffer is the parent module
            item = item->GetParent();
            wxASSERT( item && item->Type() == PCB_MODULE_T );

            if( item == NULL )
                continue;

            // Check if the parent module has already been saved in another entry
            bool found = false;

            for( unsigned j = 0; j < commandToUndo->GetCount(); j++ )
            {
                if( commandToUndo->GetPickedItem( j ) == item && commandToUndo->GetPickedItemStatus( j ) == UR_CHANGED )
                {
                    found = true;
                    break;
                }
            }

            if( !found )
            {
                // Create a clean copy of the parent module
                MODULE* orig = static_cast<MODULE*>( item );
                MODULE* clone = new MODULE( *orig );
                clone->SetParent( GetBoard() );

                // Clear current flags (which can be temporary set by a current edit command)
                for( EDA_ITEM* loc_item = clone->GraphicalItemsList(); loc_item;
                        loc_item = loc_item->Next() )
                    loc_item->ClearFlags();

                for( D_PAD* pad = clone->PadsList(); pad; pad = pad->Next() )
                    pad->ClearFlags();

                clone->Reference().ClearFlags();
                clone->Value().ClearFlags();

                ITEM_PICKER picker( item, UR_CHANGED );
                picker.SetLink( clone );
                commandToUndo->PushItem( picker );

                orig->SetLastEditTime();
            }
            else
            {
                continue;
            }
        }
        else
        {
            // Normal case: all other BOARD_ITEMs, are simply copied to the new list
            commandToUndo->PushItem( curr_picker );
        }
    }

    for( unsigned ii = 0; ii < commandToUndo->GetCount(); ii++ )
    {
        BOARD_ITEM* item    = (BOARD_ITEM*) commandToUndo->GetPickedItem( ii );
        UNDO_REDO_T command = commandToUndo->GetPickedItemStatus( ii );

        if( command == UR_UNSPECIFIED )
        {
            command = aTypeCommand;
            commandToUndo->SetPickedItemStatus( command, ii );
        }

        wxASSERT( item );

        switch( command )
        {
        case UR_CHANGED:
        case UR_DRILLORIGIN:
        case UR_GRIDORIGIN:

            /* If needed, create a copy of item, and put in undo list
             * in the picker, as link
             * If this link is not null, the copy is already done
             */
            if( commandToUndo->GetPickedItemLink( ii ) == NULL )
            {
                EDA_ITEM* cloned = item->Clone();
                commandToUndo->SetPickedItemLink( cloned, ii );
            }
            break;

        case UR_MOVED:
        case UR_ROTATED:
        case UR_ROTATED_CLOCKWISE:
        case UR_FLIPPED:
        case UR_NEW:
        case UR_DELETED:
            break;

        default:
        {
            wxLogDebug( wxT( "SaveCopyInUndoList() error (unknown code %X)" ), command );
        }
        break;

        }
    }

    if( commandToUndo->GetCount() )
    {
        /* Save the copy in undo list */
        GetScreen()->PushCommandToUndoList( commandToUndo );

        /* Clear redo list, because after a new command one cannot redo a command */
        GetScreen()->ClearUndoORRedoList( GetScreen()->m_RedoList );
    }
    else
    {
        // Should not occur
        wxASSERT( false );
        delete commandToUndo;
    }
}