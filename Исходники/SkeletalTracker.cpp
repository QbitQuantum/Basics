SkeletalTracker::~SkeletalTracker(void)
{
    if (m_pNuiImageDevice)
    {
        ShutDown();
    }
}