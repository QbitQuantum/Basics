void PmInput::run() {
	QFile device(devicename);

	if(!device.open(QIODevice::ReadOnly | QIODevice::Unbuffered)) {
		qDebug() << "Error opening device " << device.fileName()
			<< ": " << device.error();
		return;
	}

	struct input_event iev;
	while(1) {
		int r = device.read((char*)&iev, sizeof(struct input_event));
		if(r==0) break;
		if(r!=sizeof(struct input_event)) {
			qDebug() << "read only " << r << "bytes, expected " << sizeof(struct input_event);
		} else {
			processEvent(iev);
		}
	}
}