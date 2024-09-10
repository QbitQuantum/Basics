// Get network status
// static
MHInteractionChannel::EStatus MHInteractionChannel::status()
{
    if (!NetStream::isAvailable())
    {
        LOG(VB_MHEG, LOG_INFO, LOC + "WARN network is unavailable");
        return kInactive;
    }

    if (!gCoreContext->GetNumSetting("EnableMHEG", 0))
        return kDisabled;

    QStringList opts = QString(getenv("MYTHMHEG")).split(':');
    if (opts.contains("noice", Qt::CaseInsensitive))
        return kDisabled;
    else if (opts.contains("ice", Qt::CaseInsensitive))
        return kActive;

    return gCoreContext->GetNumSetting("EnableMHEGic", 1) ? kActive : kDisabled;
}