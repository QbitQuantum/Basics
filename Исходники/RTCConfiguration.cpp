RefPtr<RTCConfiguration> RTCConfiguration::create(const Dictionary& configuration, ExceptionCode& ec)
{
    if (configuration.isUndefinedOrNull())
        return nullptr;

    RefPtr<RTCConfiguration> rtcConfiguration = adoptRef(new RTCConfiguration());
    rtcConfiguration->initialize(configuration, ec);
    if (ec)
        return nullptr;

    return rtcConfiguration;
}