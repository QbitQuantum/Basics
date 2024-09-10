void Gamepad_detectDevices() {
	unsigned int numPadsSupported;
	unsigned int deviceIndex, deviceIndex2;
	JOYINFOEX info;
	JOYCAPS caps;
	bool duplicate;
	struct Gamepad_device * deviceRecord;
	struct Gamepad_devicePrivate * deviceRecordPrivate;
	UINT joystickID;
	int axisIndex;
	
	if (!inited) {
		return;
	}
	
	numPadsSupported = joyGetNumDevs();
	for (deviceIndex = 0; deviceIndex < numPadsSupported; deviceIndex++) {
		info.dwSize = sizeof(info);
		info.dwFlags = JOY_RETURNALL;
		joystickID = JOYSTICKID1 + deviceIndex;
		if (joyGetPosEx(joystickID, &info) == JOYERR_NOERROR &&
		    joyGetDevCaps(joystickID, &caps, sizeof(JOYCAPS)) == JOYERR_NOERROR) {
			
			duplicate = false;
			for (deviceIndex2 = 0; deviceIndex2 < numDevices; deviceIndex2++) {
				if (((struct Gamepad_devicePrivate *) devices[deviceIndex2]->privateData)->joystickID == joystickID) {
					duplicate = true;
					break;
				}
			}
			if (duplicate) {
				continue;
			}
			
			deviceRecord = malloc(sizeof(struct Gamepad_device));
			deviceRecord->deviceID = nextDeviceID++;
			deviceRecord->description = getDeviceDescription(joystickID, caps);
			deviceRecord->vendorID = caps.wMid;
			deviceRecord->productID = caps.wPid;
			deviceRecord->numAxes = caps.wNumAxes + ((caps.wCaps & JOYCAPS_HASPOV) ? 2 : 0);
			deviceRecord->numButtons = caps.wNumButtons;
			deviceRecord->axisStates = calloc(sizeof(float), deviceRecord->numAxes);
			deviceRecord->buttonStates = calloc(sizeof(bool), deviceRecord->numButtons);
			deviceRecord->eventDispatcher = EventDispatcher_create(deviceRecord);
			devices = realloc(devices, sizeof(struct Gamepad_device *) * (numDevices + 1));
			devices[numDevices++] = deviceRecord;
			
			deviceRecordPrivate = malloc(sizeof(struct Gamepad_devicePrivate));
			deviceRecordPrivate->joystickID = joystickID;
			deviceRecordPrivate->lastState = info;
			
			deviceRecordPrivate->xAxisIndex = 0;
			deviceRecordPrivate->yAxisIndex = 1;
			axisIndex = 2;
			deviceRecordPrivate->zAxisIndex = (caps.wCaps & JOYCAPS_HASZ) ? axisIndex++ : -1;
			deviceRecordPrivate->rAxisIndex = (caps.wCaps & JOYCAPS_HASR) ? axisIndex++ : -1;
			deviceRecordPrivate->uAxisIndex = (caps.wCaps & JOYCAPS_HASU) ? axisIndex++ : -1;
			deviceRecordPrivate->vAxisIndex = (caps.wCaps & JOYCAPS_HASV) ? axisIndex++ : -1;
			
			deviceRecordPrivate->axisRanges = malloc(sizeof(UINT[2]) * axisIndex);
			deviceRecordPrivate->axisRanges[0][0] = caps.wXmin;
			deviceRecordPrivate->axisRanges[0][1] = caps.wXmax;
			deviceRecordPrivate->axisRanges[1][0] = caps.wYmin;
			deviceRecordPrivate->axisRanges[1][1] = caps.wYmax;
			if (deviceRecordPrivate->zAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->zAxisIndex][0] = caps.wZmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->zAxisIndex][1] = caps.wZmax;
			}
			if (deviceRecordPrivate->rAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->rAxisIndex][0] = caps.wRmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->rAxisIndex][1] = caps.wRmax;
			}
			if (deviceRecordPrivate->uAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->uAxisIndex][0] = caps.wUmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->uAxisIndex][1] = caps.wUmax;
			}
			if (deviceRecordPrivate->vAxisIndex != -1) {
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->vAxisIndex][0] = caps.wVmin;
				deviceRecordPrivate->axisRanges[deviceRecordPrivate->vAxisIndex][1] = caps.wVmax;
			}
			
			deviceRecordPrivate->povXAxisIndex = (caps.wCaps & JOYCAPS_HASPOV) ? axisIndex++ : -1;
			deviceRecordPrivate->povYAxisIndex = (caps.wCaps & JOYCAPS_HASPOV) ? axisIndex++ : -1;
			
			deviceRecord->privateData = deviceRecordPrivate;
			
			Gamepad_eventDispatcher()->dispatchEvent(Gamepad_eventDispatcher(), Atom_fromString(GAMEPAD_EVENT_DEVICE_ATTACHED), deviceRecord);
		}
	}
}