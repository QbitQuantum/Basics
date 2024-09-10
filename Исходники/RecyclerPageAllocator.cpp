bool
RecyclerPageAllocator::ResetWriteWatch()
{
    if (allocFlags != MEM_WRITE_WATCH)
    {
        return false;
    }

    GCETW(GC_RESETWRITEWATCH_START, (this));

    SuspendIdleDecommit();

    bool success = true;
    // Only reset write watch on allocated pages
    if (!ResetWriteWatch(&segments) ||
        !ResetWriteWatch(&decommitSegments) ||
        !ResetAllWriteWatch(&fullSegments) ||
        !ResetAllWriteWatch(&largeSegments))
    {
        allocFlags = 0;
        success = false;
    }

    ResumeIdleDecommit();

    GCETW(GC_RESETWRITEWATCH_STOP, (this));

    return success;
}