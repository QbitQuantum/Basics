/* configure a sensors stream */
extern int32_t irobotSensorStreamConfigure(
    const irobotUARTPort_t			port,			/* (in)		irobot UART port */
    const irobotSensorCode * const	sensorCodes,	/* (in)		array of sensor codes (must be nSensorCodes in size) */
    const uint8_t					nSensorCodes	/* (in)		number of sensors in each stream packet */
) {													/* (ret)	error / success code */
    uint8_t packet[OP_SENSOR_STREAM_MAX_SIZE];
    uint8_t packetIndex = 0;
    uint8_t sensorCodeIndex = 0;

    /* check for NULL pointers */
    if(nSensorCodes && !sensorCodes) {
        return ERROR_INVALID_PARAMETER;
    }

    packet[packetIndex++] = OP_STREAM;
    packet[packetIndex++] =  fminl(nSensorCodes, OP_SENSOR_STREAM_MAX_CODES);
    for(sensorCodeIndex = 0; sensorCodeIndex < fminl(nSensorCodes, OP_SENSOR_STREAM_MAX_CODES); sensorCodeIndex++) {
        packet[packetIndex++] = sensorCodes[sensorCodeIndex];
    }

    return irobotUARTWriteRaw(port, packet, packetIndex);
}