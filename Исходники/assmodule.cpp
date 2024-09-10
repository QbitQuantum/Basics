void AssUnitRlsBase::behavior (dd dt)
{
    int bufid = -1;
    for (int i = 0; i < visible.size (); i++){
        bufid = world->getId (this, visible[i]);
        if (bufid > 0)
            trace[bufid].push(visible[i]);
    }
    PointTrace *buftrace;
    for (traceIter i = trace.begin (); i != trace.end (); i++){
        buftrace = &(i->second);
        if (buftrace->updated ()) processTrace (*buftrace, dt);
        else{
            buftrace = 0;
            trace.erase (i);
            i--;
        }
    }
    dd maxdanger = 0;
    pnt bufdanger;
    for (traceIter i = trace.begin (); i != trace.end (); i++){
        buftrace = &(i->second);
        if (buftrace->dangerValue > maxdanger){
            maxdanger = buftrace->dangerValue;
            lastDanger = buftrace;
            bufdanger = buftrace->last ();
        }
    }
    delete parent->danger;
    lastDanger = 0;
    if (maxdanger)
        parent->danger = new pnt(bufdanger);
}