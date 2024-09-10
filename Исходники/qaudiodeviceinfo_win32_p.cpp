QList<QByteArray> QAudioDeviceInfoInternal::availableDevices(QAudio::Mode mode)
{
    Q_UNUSED(mode)

    QList<QByteArray> devices;

    if(mode == QAudio::AudioOutput) {
        WAVEOUTCAPS woc;
	unsigned long iNumDevs,i;
	iNumDevs = waveOutGetNumDevs();
	for(i=0;i<iNumDevs;i++) {
	    if(waveOutGetDevCaps(i, &woc, sizeof(WAVEOUTCAPS))
	        == MMSYSERR_NOERROR) {
	        devices.append(QString((const QChar *)woc.szPname).toLocal8Bit().constData());
	    }
	}
    } else {
        WAVEINCAPS woc;
	unsigned long iNumDevs,i;
	iNumDevs = waveInGetNumDevs();
	for(i=0;i<iNumDevs;i++) {
	    if(waveInGetDevCaps(i, &woc, sizeof(WAVEINCAPS))
	        == MMSYSERR_NOERROR) {
	        devices.append(QString((const QChar *)woc.szPname).toLocal8Bit().constData());
	    }
	}

    }
    if(devices.count() > 0)
        devices.append("default");

    return devices;
}