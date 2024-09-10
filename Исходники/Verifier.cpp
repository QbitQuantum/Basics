bool
js::gc::GCRuntime::endVerifyPostBarriers()
{
    VerifyPostTracer* trc = (VerifyPostTracer*)verifyPostData;
    if (!trc)
        return false;

    VerifyPostTracer::EdgeSet edges;
    AutoPrepareForTracing prep(rt, SkipAtoms);

    /* Visit every entry in the store buffer and put the edges in a hash set. */
    trc->setTraceCallback(PostVerifierCollectStoreBufferEdges);
    if (!edges.init())
        goto oom;
    trc->edges = &edges;
    storeBuffer.markAll(trc);

    /* Walk the heap to find any edges not the the |edges| set. */
    trc->setTraceCallback(PostVerifierVisitEdge);
    for (GCZoneGroupIter zone(rt); !zone.done(); zone.next()) {
        for (auto kind : AllAllocKinds()) {
            for (ZoneCellIterUnderGC cells(zone, kind); !cells.done(); cells.next()) {
                Cell* src = cells.getCell();
                JS_TraceChildren(trc, src, MapAllocToTraceKind(kind));
            }
        }
    }

oom:
    js_delete(trc);
    verifyPostData = nullptr;
    return true;
}