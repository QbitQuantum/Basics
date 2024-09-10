PNS_ITEM* PNS_ROUTER::syncVia( VIA* aVia )
{
    LAYER_ID top, bottom;
    aVia->LayerPair( &top, &bottom );
    PNS_VIA* v = new PNS_VIA(
            aVia->GetPosition(),
            PNS_LAYERSET( top, bottom ),
            aVia->GetWidth(),
            aVia->GetDrillValue(),
            aVia->GetNetCode(),
            (PNS_VIA_TYPE)aVia->GetViaType() );

    v->SetParent( aVia );

    return v;
}