//--------------------------------------------------------------
void ofxCLEye::setDeviceGUID(GUID deviceGUID){
	int id = getDeviceID(deviceGUID);

	if(id < 0){
		ofLogWarning(OFX_CLEYE_MODULE_NAME) << "setdeviceGUID(): can't find device with this GUID.";
		return;
	}

	if(initialized){
		ofLogWarning(OFX_CLEYE_MODULE_NAME) << "setdeviceGUID(): can't set device while grabber is running.";
		return;
	}

	requestedDeviceID = id;
}