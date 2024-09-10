void KPAOS4Checker::check()
{
    QString inPort(Settings::get().getMidiInPort());
    QString outPort(Settings::get().getMidiOutPort());

    if(inPort.isEmpty() || outPort.isEmpty())
    {
        SettingsDialog settingsDialog(nullptr);
        settingsDialog.exec();
        inPort = Settings::get().getMidiInPort();
        outPort = Settings::get().getMidiOutPort();
    }

    if(Midi::get().openPorts(inPort, outPort))
    {
        QEventLoop el;
        el.connect(this, &KPAOS4Checker::stopLoop, &el, &QEventLoop::quit);
        el.connect(&stompDelayObj, &Stomp::onOffReceived, this, &KPAOS4Checker::onOfReceived);
        el.connect(mTimer, &QTimer::timeout, this, &KPAOS4Checker::timerTimeout);
        mTimer->start(500);
        stompDelayObj.requestOnOff();
        el.exec();
        el.disconnect(this, &KPAOS4Checker::stopLoop, &el, &QEventLoop::quit);
        el.disconnect(&stompDelayObj, &Stomp::onOffReceived, this, &KPAOS4Checker::onOfReceived);
        el.disconnect(mTimer, &QTimer::timeout, this, &KPAOS4Checker::timerTimeout);
    }
}