void RtMidiDriver::start(const QList<bool> &deviceStatuses){
    setInputDevicesStatus(deviceStatuses);

    if(!hasInputDevices()){
        return;
    }
    stop();

    for(int deviceIndex=0; deviceIndex < inputDevicesEnabledStatuses.size(); deviceIndex++) {
        if(deviceIndex < midiStreams.size()){
            RtMidiIn* stream = midiStreams.at(deviceIndex);
            if(stream && inputDevicesEnabledStatuses.at(deviceIndex)){//device is globally enabled?
                if(!stream->isPortOpen()){
                    try{
                        qCInfo(jtMidi) << "Starting MIDI in " << QString::fromStdString(stream->getPortName(deviceIndex));
                        stream->openPort(deviceIndex);
                    }
                    catch(RtMidiError e){
                        qCCritical(jtMidi) << "Error opening midi port " << QString::fromStdString(e.getMessage());
                    }
                }
                else{
                    qCCritical(jtMidi) << "Port " << QString::fromStdString(stream->getPortName(deviceIndex)) << " already opened!";
                }
            }
        }
    }
}