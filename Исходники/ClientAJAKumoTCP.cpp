void ClientAJAKumoTCP::transmitPacket(char* data) {
    uint8_t len = strlen(data);
    uint8_t *_buffer = (uint8_t*)malloc(6 + len);
    // Prepare packet
    _buffer[0] = 0x01; // SOH
    _buffer[1] = 'N'; // Protocol ID
    _buffer[2] = toASCII(_sessionID & 0xF);

    for(uint8_t i = 0; i < len; i++) {
        if(data[i] == ',') {
            _buffer[3+i] = 0x09; // HT
        } else {
            _buffer[3+i] = data[i];
        }
    }

    uint16_t checksum = calculateChecksum(_buffer, 3+len);

    _buffer[3+len] = checksum >> 8;
    _buffer[4+len] = checksum & 0xFF;

    _buffer[5+len] = 0x04; // EOT

    if(_client.connected()) {
        if(_serialOutput > 1) {
            for(uint8_t j=0; j<6+len; j++) {
                Serial << _HEXPADL(_buffer[j], 2, "0") << ":";
            }
            Serial << "\n";
        }

        _client.write(_buffer, 6 + len);
    }

    free(_buffer);
}