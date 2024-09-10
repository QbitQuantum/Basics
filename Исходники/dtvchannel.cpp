void DTVChannel::SetTuningMode(const QString &tuning_mode)
{
    QMutexLocker locker(&dtvinfo_lock);
    tuningMode = tuning_mode.toLower();
    tuningMode.detach();
}