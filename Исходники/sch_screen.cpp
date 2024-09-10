int SCH_SCREEN::UpdatePickList()
{
    ITEM_PICKER picker;
    EDA_RECT area;
    unsigned count;

    area.SetOrigin( m_BlockLocate.GetOrigin() );
    area.SetSize( m_BlockLocate.GetSize() );
    area.Normalize();

    for( SCH_ITEM* item = m_drawList.begin(); item; item = item->Next() )
    {
        // An item is picked if its bounding box intersects the reference area.
        if( item->HitTest( area ) )
        {
            picker.SetItem( item );
            m_BlockLocate.PushItem( picker );
        }
    }

    // if the block is composed of one item,
    // select it as the current item
    count =  m_BlockLocate.GetCount();
    if( count == 1 )
    {
        SetCurItem( (SCH_ITEM*) m_BlockLocate.GetItem( 0 ) );
    }
    else
    {
        SetCurItem( NULL );
    }

    return count;
}