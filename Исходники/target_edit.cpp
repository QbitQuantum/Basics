PCB_TARGET* PCB_EDIT_FRAME::CreateTarget( wxDC* DC )
{
    PCB_TARGET* target = new PCB_TARGET( GetBoard() );

    target->SetFlags( IS_NEW );

    GetBoard()->Add( target );

    target->SetLayer( Edge_Cuts );
    target->SetWidth( GetDesignSettings().m_EdgeSegmentWidth );
    target->SetSize( MireDefaultSize );
    target->SetPosition( GetCrossHairPosition() );

    PlaceTarget( target, DC );

    return target;
}