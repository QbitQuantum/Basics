void DVBSignalMonitor::GetRotorStatus(bool &was_moving, bool &is_moving)
{
    DVBChannel *dvbchannel = GetDVBChannel();
    if (!dvbchannel)
        return;

    const DiSEqCDevRotor *rotor = dvbchannel->GetRotor();
    if (!rotor)
        return;

    QMutexLocker locker(&statusLock);
    was_moving = rotorPosition.GetValue() < 100;
    int pos    = (int)truncf(rotor->GetProgress() * 100);
    rotorPosition.SetValue(pos);
    is_moving  = rotorPosition.GetValue() < 100;
}