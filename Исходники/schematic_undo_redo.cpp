void SCH_EDIT_FRAME::PutDataInPreviousState( PICKED_ITEMS_LIST* aList, bool aRedoCommand )
{
    SCH_ITEM* item;
    SCH_ITEM* alt_item;

    // Exchange the current wires, buses, and junctions with the copy save by the last edit.
    if( aList->m_Status == UR_WIRE_IMAGE )
    {
        DLIST< SCH_ITEM > oldWires;

        // Prevent items from being deleted when the DLIST goes out of scope.
        oldWires.SetOwnership( false );

        // Remove all of the wires, buses, and junctions from the current screen.
        GetScreen()->ExtractWires( oldWires, false );

        // Copy the saved wires, buses, and junctions to the current screen.
        for( unsigned int i = 0;  i < aList->GetCount();  i++ )
            GetScreen()->Append( (SCH_ITEM*) aList->GetPickedItem( i ) );

        aList->ClearItemsList();

        // Copy the previous wires, buses, and junctions to the picked item list for the
        // redo operation.
        while( oldWires.GetCount() != 0 )
        {
            ITEM_PICKER picker = ITEM_PICKER( oldWires.PopFront(), UR_WIRE_IMAGE );
            aList->PushItem( picker );
        }

        return;
    }

    // Undo in the reverse order of list creation: (this can allow stacked changes like the
    // same item can be changes and deleted in the same complex command.
    for( int ii = aList->GetCount() - 1; ii >= 0; ii--  )
    {
        item = (SCH_ITEM*) aList->GetPickedItem( ii );
        wxASSERT( item );

        item->ClearFlags();

        SCH_ITEM* image = (SCH_ITEM*) aList->GetPickedItemLink( ii );

        switch( aList->GetPickedItemStatus( ii ) )
        {
        case UR_CHANGED: /* Exchange old and new data for each item */
            item->SwapData( image );
            break;

        case UR_NEW:     /* new items are deleted */
            aList->SetPickedItemStatus( UR_DELETED, ii );
            GetScreen()->Remove( item );
            break;

        case UR_DELETED: /* deleted items are put in the draw item list, as new items */
            aList->SetPickedItemStatus( UR_NEW, ii );
            GetScreen()->Append( item );
            break;

        case UR_MOVED:
            item->ClearFlags();
            item->SetFlags( aList->GetPickerFlags( ii ) );
            item->Move( aRedoCommand ? aList->m_TransformPoint : -aList->m_TransformPoint );
            item->ClearFlags();
            break;

        case UR_MIRRORED_Y:
            item->MirrorY( aList->m_TransformPoint.x );
            break;

        case UR_MIRRORED_X:
            item->MirrorX( aList->m_TransformPoint.y );
            break;

        case UR_ROTATED:
            // To undo a rotate 90 deg transform we must rotate 270 deg to undo
            // and 90 deg to redo:
            item->Rotate( aList->m_TransformPoint );

            if( aRedoCommand )
                break;  // A only one rotate transform is OK

            // Make 3 rotate 90 deg transforms is this is actually an undo command
            item->Rotate( aList->m_TransformPoint );
            item->Rotate( aList->m_TransformPoint );
            break;

        case UR_EXCHANGE_T:
            alt_item = (SCH_ITEM*) aList->GetPickedItemLink( ii );
            alt_item->SetNext( NULL );
            alt_item->SetBack( NULL );
            GetScreen()->Remove( item );
            GetScreen()->Append( alt_item );
            aList->SetPickedItem( alt_item, ii );
            aList->SetPickedItemLink( item, ii );
            break;

        default:
            wxFAIL_MSG( wxString::Format( wxT( "Unknown undo/redo command %d" ),
                                          aList->GetPickedItemStatus( ii ) ) );
            break;
        }
    }
}