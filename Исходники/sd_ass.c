static long long find_timestamp(struct sd *sd, double pts)
{
    struct sd_ass_priv *priv = sd->priv;
    if (pts == MP_NOPTS_VALUE)
        return 0;

    pts /= priv->sub_speed;

    long long ts = llrint(pts * 1000);

    if (!sd->opts->sub_fix_timing)
        return ts;

    // Try to fix small gaps and overlaps.
    ASS_Track *track = priv->ass_track;
    int threshold = SUB_GAP_THRESHOLD * 1000;
    int keep = SUB_GAP_KEEP * 1000;

    // Find the "current" event.
    ASS_Event *ev[2] = {0};
    int n_ev = 0;
    for (int n = 0; n < track->n_events; n++) {
        ASS_Event *event = &track->events[n];
        if (ts >= event->Start - threshold && ts <= END(event) + threshold) {
            if (n_ev >= MP_ARRAY_SIZE(ev))
                return ts; // multiple overlaps - give up (probably complex subs)
            ev[n_ev++] = event;
        }
    }

    if (n_ev != 2)
        return ts;

    // Simple/minor heuristic against destroying typesetting.
    if (ev[0]->Style != ev[1]->Style || has_overrides(ev[0]->Text) ||
        has_overrides(ev[1]->Text))
        return ts;

    // Sort by start timestamps.
    if (ev[0]->Start > ev[1]->Start)
        MPSWAP(ASS_Event*, ev[0], ev[1]);

    // We want to fix partial overlaps only.
    if (END(ev[0]) >= END(ev[1]))
        return ts;

    if (ev[0]->Duration < keep || ev[1]->Duration < keep)
        return ts;

    // Gap between the events -> move ts to show the end of the first event.
    if (ts >= END(ev[0]) && ts < ev[1]->Start && END(ev[0]) < ev[1]->Start &&
        END(ev[0]) + threshold >= ev[1]->Start)
        return END(ev[0]) - 1;

    // Overlap -> move ts to the (exclusive) end of the first event.
    // Relies on the fact that the ASS_Renderer has no overlap registered, even
    // if there is one. This happens to work because we never render the
    // overlapped state, and libass never resolves a collision.
    if (ts >= ev[1]->Start && ts <= END(ev[0]) && END(ev[0]) > ev[1]->Start &&
        END(ev[0]) <= ev[1]->Start + threshold)
        return END(ev[0]);

    return ts;
}