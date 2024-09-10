bool CResourceMap::IsResourceCompatible(const ResourceBlob &resource)
{
    SCIVersion resourceVersion = resource.GetVersion();
    SCIVersion usVersion = GetSCIVersion();
    if (resourceVersion == usVersion)
    {
        return true;
    }

    if (resource.GetType() == ResourceType::View)
    {
        return resourceVersion.ViewFormat == usVersion.ViewFormat;
    }

    if (resource.GetType() == ResourceType::Pic)
    {
        return resourceVersion.PicFormat == usVersion.PicFormat;
    }

    if (resource.GetType() == ResourceType::Palette)
    {
        return usVersion.HasPalette;
    }

    if (resource.GetType() == ResourceType::Sound)
    {
        return resourceVersion.SoundFormat == usVersion.SoundFormat;
    }

    if (resource.GetType() == ResourceType::Script)
    {
        return resourceVersion.lofsaOpcodeIsAbsolute == usVersion.lofsaOpcodeIsAbsolute;
    }

    return true; // I guess?
}