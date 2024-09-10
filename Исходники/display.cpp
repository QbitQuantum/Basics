void Display::terminate()
{
    makeCurrent(nullptr, nullptr, nullptr);

    while (!mContextSet.empty())
    {
        destroyContext(*mContextSet.begin());
    }

    while (!mImageSet.empty())
    {
        destroyImage(*mImageSet.begin());
    }

    mConfigSet.clear();

    mImplementation->terminate();

    mInitialized = false;

    // Never de-init default platform.. terminate is not that final.
}