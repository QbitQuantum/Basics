void QMidi::closeMidiOut()
{
#if defined(Q_OS_WIN)
    midiOutClose(midiOutPtr);
#elif defined(Q_OS_LINUX)
    QStringList l = myOutDeviceId.split(":");
    int client = l.at(0).toInt();
    int port = l.at(1).toInt();

    snd_seq_disconnect_from(midiOutPtr, 0, client,port);
#elif defined(Q_OS_HAIKU)
	midiOutLocProd->Disconnect(midiOutConsumer);
	midiOutConsumer->Release();
	midiOutLocProd->Unregister();
	midiOutLocProd->Release();
#endif
}