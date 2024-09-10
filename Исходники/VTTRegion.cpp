VTTRegion::RegionSetting VTTRegion::scanSettingName(VTTScanner& input)
{
    if (input.scan("id"))
        return Id;
    if (input.scan("height"))
        return Height;
    if (input.scan("width"))
        return Width;
    if (input.scan("viewportanchor"))
        return ViewportAnchor;
    if (input.scan("regionanchor"))
        return RegionAnchor;
    if (input.scan("scroll"))
        return Scroll;

    return None;
}