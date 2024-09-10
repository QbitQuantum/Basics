void IOMapper::waitForSystemMapper()
{
    sMapperLock.lock();
    while ((uintptr_t) IOMapper::gSystem & kWaitMask)
    {
		OSReportWithBacktrace("waitForSystemMapper");
        sMapperLock.sleep(&IOMapper::gSystem);
    }
    sMapperLock.unlock();
}