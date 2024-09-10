static void
cm_MarkServerDown(cm_server_t *tsp, afs_int32 code, int wasDown)
{

    /* mark server as down */
    if (!(tsp->flags & CM_SERVERFLAG_DOWN)) {
	_InterlockedOr(&tsp->flags, CM_SERVERFLAG_DOWN);
	tsp->downTime = time(NULL);
    }
    if (code != VRESTARTING) {
	lock_ReleaseMutex(&tsp->mx);
	cm_ForceNewConnections(tsp);
	lock_ObtainMutex(&tsp->mx);
    }
    /* Now update the volume status if necessary */
    if (!wasDown) {
	if (tsp->type == CM_SERVER_FILE) {
	    cm_server_vols_t * tsrvp;
	    cm_volume_t * volp;
	    int i;
	    cm_req_t req;

	    for (tsrvp = tsp->vols; tsrvp; tsrvp = tsrvp->nextp) {
		for (i=0; i<NUM_SERVER_VOLS; i++) {
		    if (tsrvp->ids[i] != 0) {
			cm_InitReq(&req);

			lock_ReleaseMutex(&tsp->mx);
			code = cm_FindVolumeByID(tsp->cellp, tsrvp->ids[i],
						 cm_rootUserp, &req,
						 CM_GETVOL_FLAG_NO_LRU_UPDATE,
						 &volp);
			lock_ObtainMutex(&tsp->mx);
			if (code == 0) {
			    cm_UpdateVolumeStatus(volp, tsrvp->ids[i]);
			    cm_PutVolume(volp);
			}
		    }
		}
	    }
	}
	cm_RankServer(tsp);
    }
}