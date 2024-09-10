bool SIPAccount::hostnameMatch (const std::string& hostname) const
{
    return hostname == getHostname();
}