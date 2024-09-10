EndPoint::~EndPoint()
{
    // No network thread if networking isn't enabled.
    if (mContext->Enabled())
    {
        // Kill the network thread and wait for it to terminate.
        mRunning = false;
        mNetworkThread.Join();
    }

    // Release the per-process context.
    ReleaseContext();
}