void
groupDequeueMoveNotifies (CompScreen *s)
{
    GroupPendingMoves *move;
    GroupPendingSyncs *syncs = NULL, *sync;

    GROUP_SCREEN (s);

    gs->queued = TRUE;

    while (gs->pendingMoves)
    {
	move = gs->pendingMoves;
	gs->pendingMoves = move->next;

	moveWindow (move->w, move->dx, move->dy, TRUE, move->immediate);
	if (move->sync)
	{
	    sync = malloc (sizeof (GroupPendingSyncs));
	    if (sync)
	    {
		GROUP_WINDOW (move->w);

		gw->needsPosSync = TRUE;
		sync->w          = move->w;
		sync->next       = syncs;
		syncs            = sync;
	    }
	}
	free (move);
    }

    if (syncs)
	groupDequeueSyncs (syncs);

    gs->queued = FALSE;
}