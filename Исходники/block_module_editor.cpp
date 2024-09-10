/* Copy marked items, at new position = old position + offset
 */
void CopyMarkedItems( MODULE* module, wxPoint offset, bool aIncrement )
{
    if( module == NULL )
        return;

    // Reference and value cannot be copied, they are unique.
    // Ensure they are not selected
    module->Reference().ClearFlags();
    module->Value().ClearFlags();

    for( D_PAD* pad = module->Pads();  pad;  pad = pad->Next() )
    {
        if( !pad->IsSelected() )
            continue;

        pad->ClearFlags( SELECTED );
        D_PAD* NewPad = new D_PAD( *pad );
        NewPad->SetParent( module );
        NewPad->SetFlags( SELECTED );
        module->Pads().PushFront( NewPad );

        if( aIncrement )
            NewPad->IncrementPadName( true, true );
    }

    BOARD_ITEM* newItem;

    for( BOARD_ITEM* item = module->GraphicalItems();  item;  item = item->Next() )
    {
        if( !item->IsSelected() )
            continue;

        item->ClearFlags( SELECTED );

        newItem = (BOARD_ITEM*)item->Clone();
        newItem->SetParent( module );
        newItem->SetFlags( SELECTED );
        module->GraphicalItems().PushFront( newItem );
    }

    MoveMarkedItems( module, offset );
}