void SysEventMonitor::onTimeout() {
#ifdef _WIN32
    LASTINPUTINFO li;
    li.cbSize = sizeof(LASTINPUTINFO);
    if (!GetLastInputInfo(&li)) {
        qDebug() << "SysEventMonitor::something wrong with GetLastInputInfo()";
    }

    DWORD timeDiffMs = GetTickCount() - li.dwTime;
    DWORD inactThreshMs = settings_.value(SettingInactivityThreshold, SettingInactivityThresholdDefVal).toUInt();
    Q_ASSERT(inactThreshMs > 0);

    if (timeDiffMs < inactThreshMs) {
        if (!activeState_) {
            activeState_ = true;
            Logger::logEvent(Logger::UserStateActive);
            emit userStateActive();
        }
    } else {
        if (activeState_) {
            activeState_ = false;
            Logger::logEvent(Logger::UserStateInactive);
            emit userStateInactive();
        }
    }
#endif
}