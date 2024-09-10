void moveInfoApplyCriterion( MoveInfo *theMoveInfo,
                            SourceCriterionFunc theSourceCriterion,
                            CriterionFunc theCriterion )
{
    Stack *sourceStack, *destStack;
    Move *theMove;
    int i, j;

#ifdef DEBUG
    FPrintf( Output(), "0x%lx: ", theMoveInfo );
#endif
    for( i = 0; i < boardNumStacks(); i++ )
    {
        if( !theSourceCriterion( sourceStack = &theMoveInfo->mi_Stacks[i] ))
            continue;
        for( j = 0; j < boardNumStacks(); j++ )
        {
            if( i == j )
                continue;
            destStack = &theMoveInfo->mi_Stacks[j];
            if(( theCriterion( sourceStack, destStack ))&&
               ( theMove = moveAlloc( i, j )))
            {
                moveAddTail( &theMoveInfo->mi_Moves, theMove );
#ifdef DEBUG
                FPrintf( Output(), "(%ld->%ld)", i, j );
#endif
            }
        }
    }
#ifdef DEBUG
    FPrintf( Output(), "\n" );
#endif
}