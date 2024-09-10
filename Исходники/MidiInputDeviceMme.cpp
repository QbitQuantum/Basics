 MidiInputDeviceMme::MidiInputDeviceMme(std::map<String,DeviceCreationParameter*> Parameters, void* pSampler) : MidiInputDevice(Parameters, pSampler) {
     AcquirePorts(((DeviceCreationParameterInt*)Parameters["PORTS"])->ValueAsInt());
     if (((DeviceCreationParameterBool*)Parameters["ACTIVE"])->ValueAsBool()) {
         Listen();
     }
 }