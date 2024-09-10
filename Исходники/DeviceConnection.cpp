void DeviceConnection::send(Command cmd, bool complete){
	if(!conn || processing) return;

	long values[] = {cmd.type, cmd.id, cmd.deviceID, cmd.value};

	conn->write(START_BIT);
	char vbuffer[3];
	for (int i = 0; i < 4; ++i) {
		ltoa(values[i], vbuffer, 10);
		conn->write(vbuffer);
		if(complete && i == 3){
			conn->write(ACK_BIT);
		}else{
			conn->write(SEPARATOR);
		}
	}
}