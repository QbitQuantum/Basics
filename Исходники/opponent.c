void opponentStoreMoveSequence( MoveInfo *theMoveInfo )
{
    MoveInfo *aMoveInfo;
    Move *aMove;

#ifdef DEBUG
    FPrintf( Output(), "Best sequence now: " );
    opponentPrintSequence( theMoveInfo );
#endif

    while( aMove = moveRemHead( MoveSequence ))
        moveFree( aMove );

    for( aMoveInfo = theMoveInfo; aMoveInfo->mi_Parent;
        aMoveInfo = aMoveInfo->mi_Parent )
    {
        if( aMove = moveAlloc( aMoveInfo->mi_SrcStack,
                              aMoveInfo->mi_DestStack ))
            moveAddHead( MoveSequence, aMove );
    }
}