VTTCue::CueSetting VTTCue::settingName(VTTScanner& input)
{
    CueSetting parsedSetting = None;
    if (input.scan("vertical"))
        parsedSetting = Vertical;
    else if (input.scan("line"))
        parsedSetting = Line;
    else if (input.scan("position"))
        parsedSetting = Position;
    else if (input.scan("size"))
        parsedSetting = Size;
    else if (input.scan("align"))
        parsedSetting = Align;
#if ENABLE(WEBVTT_REGIONS)
    else if (input.scan("region"))
        parsedSetting = RegionId;
#endif
    // Verify that a ':' follows.
    if (parsedSetting != None && input.scan(':'))
        return parsedSetting;

    return None;
}