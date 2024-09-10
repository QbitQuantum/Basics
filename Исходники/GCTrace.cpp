void
js::gc::TraceTenuredFinalize(Cell *thing)
{
    if (!gcTraceFile)
        return;
    if (thing->tenuredGetAllocKind() == FINALIZE_OBJECT_GROUP)
        tracedGroups.remove(static_cast<const ObjectGroup *>(thing));
    TraceEvent(TraceEventTenuredFinalize, uint64_t(thing));
}