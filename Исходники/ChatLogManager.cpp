//-----------------------------------------------------------------------------
void ChatLogManager::getReportHeader(Unicode::String & header, std::string const &reportingPlayer, NetworkId const &reportingPlayerNetworkId, std::string const &reportingPlayerStationName, uint32 reportingPlayerStationId, std::string const &harassingPlayer, NetworkId const &harassingPlayerNetworkId, std::string const &harassingPlayerStationName, uint32 harassingPlayerStationId)
{
    header.clear();
    header.append(Unicode::narrowToWide("\n\n//--------------------------------------------------------\n"));

    FormattedString<512> fs;

    // Reporting

    header.append(Unicode::narrowToWide(fs.sprintf("Reporting: %s (%s)", reportingPlayer.c_str(), reportingPlayerNetworkId.getValueString().c_str())));

    if (!reportingPlayerStationName.empty() || (reportingPlayerStationId > 0))
    {
        header.append(Unicode::narrowToWide(" Station ID:"));
        if (!reportingPlayerStationName.empty())
            header.append(Unicode::narrowToWide(fs.sprintf(" %s", reportingPlayerStationName.c_str())));
        if (reportingPlayerStationId > 0)
            header.append(Unicode::narrowToWide(fs.sprintf(" (%lu)", reportingPlayerStationId)));
    }

    header.append(Unicode::narrowToWide("\n"));

    // Harassing

    header.append(Unicode::narrowToWide(fs.sprintf("Harassing: %s (%s)", harassingPlayer.c_str(), harassingPlayerNetworkId.getValueString().c_str())));

    if (!harassingPlayerStationName.empty() || (harassingPlayerStationId > 0))
    {
        header.append(Unicode::narrowToWide(" Station ID:"));
        if (!harassingPlayerStationName.empty())
            header.append(Unicode::narrowToWide(fs.sprintf(" %s", harassingPlayerStationName.c_str())));
        if (harassingPlayerStationId > 0)
            header.append(Unicode::narrowToWide(fs.sprintf(" (%lu)", harassingPlayerStationId)));
    }

    header.append(Unicode::narrowToWide("\n"));

    // Creation time

    header.append(Unicode::narrowToWide(fs.sprintf("Log Creation Time: %s\n", getTimeString(Os::getRealSystemTime()).c_str())));

    // Time length

    header.append(Unicode::narrowToWide(fs.sprintf("Log Time Length: %d minutes\n", ConfigServerUtility::getChatLogMinutes())));
}