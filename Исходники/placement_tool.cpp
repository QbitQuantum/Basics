void ALIGN_DISTRIBUTE_TOOL::doDistributeGapsVertically( ALIGNMENT_RECTS& itemsToDistribute,
                                                        const BOARD_ITEM* lastItem, int totalGap ) const
{
    const auto itemGap = totalGap / ( itemsToDistribute.size() - 1 );
    auto targetY = itemsToDistribute.begin()->second.GetY();

    for( auto& i : itemsToDistribute )
    {
        BOARD_ITEM* item = i.first;

        // cover the corner case where the last item is wider than the previous item and gap
        if( lastItem == item )
            continue;

        // Don't move a pad by itself unless editing the footprint
        if( item->Type() == PCB_PAD_T && m_frame->IsType( FRAME_PCB ) )
            item = item->GetParent();

        int difference = targetY - i.second.GetY();
        i.first->Move( wxPoint( 0, difference ) );
        targetY += ( i.second.GetHeight() + itemGap );
    }
}