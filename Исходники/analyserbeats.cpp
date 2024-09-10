// TODO(XXX): Get rid of the horrible duplication here between initialise and
// loadStored.
bool AnalyserBeats::loadStored(TrackPointer tio) const {
    int iMinBpm;
    int iMaxBpm;

    bool allow_above = static_cast<bool>(m_pConfig->getValueString(
        ConfigKey(BPM_CONFIG_KEY, BPM_ABOVE_RANGE_ENABLED)).toInt());
    if (allow_above) {
        iMinBpm = 0;
        iMaxBpm = 9999;
    } else {
        iMinBpm = m_pConfig->getValueString(ConfigKey(BPM_CONFIG_KEY, BPM_RANGE_START)).toInt();
        iMaxBpm = m_pConfig->getValueString(ConfigKey(BPM_CONFIG_KEY, BPM_RANGE_END)).toInt();
    }

    bool bPreferencesFixedTempo = static_cast<bool>(
        m_pConfig->getValueString(
            ConfigKey(BPM_CONFIG_KEY, BPM_FIXED_TEMPO_ASSUMPTION)).toInt());
    bool bPreferencesOffsetCorrection = static_cast<bool>(
        m_pConfig->getValueString(
            ConfigKey(BPM_CONFIG_KEY, BPM_FIXED_TEMPO_OFFSET_CORRECTION)).toInt());
    bool bPreferencesReanalyzeOldBpm = static_cast<bool>(
        m_pConfig->getValueString(
            ConfigKey(BPM_CONFIG_KEY, BPM_REANALYZE_WHEN_SETTINGS_CHANGE)).toInt());
    bool bPreferencesFastAnalysis = static_cast<bool>(
        m_pConfig->getValueString(
            ConfigKey(BPM_CONFIG_KEY, BPM_FAST_ANALYSIS_ENABLED)).toInt());

    bool bpmLock = tio->hasBpmLock();
    if (bpmLock) {
        qDebug() << "Track is BpmLocked: Beat calculation will not start";
        return true;
    }

    QString library = m_pConfig->getValueString(
        ConfigKey(VAMP_CONFIG_KEY, VAMP_ANALYSER_BEAT_LIBRARY));
    QString pluginID = m_pConfig->getValueString(
        ConfigKey(VAMP_CONFIG_KEY, VAMP_ANALYSER_BEAT_PLUGIN_ID));

    // At first start config for QM and Vamp does not exist --> set default
    // TODO(XXX): This is no longer present in initialise. Remove?
    if (library.isEmpty() || library.isNull())
        library = "libmixxxminimal";
    if (pluginID.isEmpty() || pluginID.isNull())
        pluginID="qm-tempotracker:0";

    // If the track already has a Beats object then we need to decide whether to
    // analyze this track or not.
    BeatsPointer pBeats = tio->getBeats();
    if (pBeats) {
        QString version = pBeats->getVersion();
        QString subVersion = pBeats->getSubVersion();

        QHash<QString, QString> extraVersionInfo = getExtraVersionInfo(
            pluginID, bPreferencesFastAnalysis);
        QString newVersion = BeatFactory::getPreferredVersion(
            bPreferencesOffsetCorrection);
        QString newSubVersion = BeatFactory::getPreferredSubVersion(
            bPreferencesFixedTempo, bPreferencesOffsetCorrection,
            iMinBpm, iMaxBpm, extraVersionInfo);

        if (version == newVersion && subVersion == newSubVersion) {
            // If the version and settings have not changed then if the world is
            // sane, re-analyzing will do nothing.
            qDebug() << "Beat sub-version has not changed since previous analysis so not analyzing.";
            return true;
        } else if (bPreferencesReanalyzeOldBpm) {
            return false;
        } else if (pBeats->getBpm() == 0.0) {
            qDebug() << "BPM is 0 for track so re-analyzing despite preference settings.";
            return false;
        } else if (pBeats->findNextBeat(0) <= 0.0) {
            qDebug() << "First beat is 0 for grid so analyzing track to find first beat.";
            return false;
        } else {
            qDebug() << "Beat calculation skips analyzing because the track has"
                     << "a BPM computed by a previous Mixxx version and user"
                     << "preferences indicate we should not change it.";
            return true;
        }
    } else {
        // If we got here, we want to analyze this track.
        return false;
    }
}