bool UiSystem::InitializeResources()
{
    mUiResources = std::make_unique<UiResources>(GfxRenderDevice::Instance(), FileSystem::Instance());
    if (!mUiResources->InitializeWithConfiguration("Configurations/Ui.json"))
    {
        Logf("Warning: Cannot load ui configuration");
        return false;
    }

    return true;
}