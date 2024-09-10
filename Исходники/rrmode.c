int
ProcRRCreateMode(ClientPtr client)
{
    REQUEST(xRRCreateModeReq);
    xRRCreateModeReply rep;
    WindowPtr pWin;
    ScreenPtr pScreen;
    xRRModeInfo *modeInfo;
    long units_after;
    char *name;
    int error, rc;
    RRModePtr mode;

    REQUEST_AT_LEAST_SIZE(xRRCreateModeReq);
    rc = dixLookupWindow(&pWin, stuff->window, client, DixGetAttrAccess);
    if (rc != Success)
        return rc;

    pScreen = pWin->drawable.pScreen;

    modeInfo = &stuff->modeInfo;
    name = (char *) (stuff + 1);
    units_after = (stuff->length - bytes_to_int32(sizeof(xRRCreateModeReq)));

    /* check to make sure requested name fits within the data provided */
    if (bytes_to_int32(modeInfo->nameLength) > units_after)
        return BadLength;

    mode = RRModeCreateUser(pScreen, modeInfo, name, &error);
    if (!mode)
        return error;

    rep = (xRRCreateModeReply) {
        .type = X_Reply,
        .sequenceNumber = client->sequence,
        .length = 0,
        .mode = mode->mode.id
	};
    if (client->swapped) {
        swaps(&rep.sequenceNumber);
        swapl(&rep.length);
        swapl(&rep.mode);
    }
    WriteToClient(client, sizeof(xRRCreateModeReply), &rep);
    /* Drop out reference to this mode */
    RRModeDestroy(mode);
    return Success;
}

int
ProcRRDestroyMode(ClientPtr client)
{
    REQUEST(xRRDestroyModeReq);
    RRModePtr mode;

    REQUEST_SIZE_MATCH(xRRDestroyModeReq);
    VERIFY_RR_MODE(stuff->mode, mode, DixDestroyAccess);

    if (!mode->userScreen)
        return BadMatch;
    if (mode->refcnt > 1)
        return BadAccess;
    FreeResource(stuff->mode, 0);
    return Success;
}