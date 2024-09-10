TcpPacket::TcpPacket(
  unsigned int sequence_number,
  unsigned int ack_number,
  bool flags[],
  unsigned int window_size,
  unsigned long long int timestamp,
  unsigned int data_size,
  char * content) {
  if (data_size == 0) {
    buf = (char *) malloc(sizeof(char) * PACKET_SIZE - HEADER_SIZE);
  } else {
    buf = (char *) malloc(sizeof(char) * PACKET_SIZE);
  }
  memset(buf, 0, PACKET_SIZE);
  char unsigned_int_buffer[SEQUENCE_SIZE];
  int current_bit = 0;

  _itoa_s(sequence_number, unsigned_int_buffer, 10);
  setBufferValues(buf, current_bit, SEQUENCE_SIZE, unsigned_int_buffer);
  current_bit += SEQUENCE_SIZE;

  _itoa_s(ack_number, unsigned_int_buffer, 10);
  setBufferValues(buf, current_bit, ACK_SIZE, unsigned_int_buffer);
  current_bit += ACK_SIZE;

  char bool_buffer[9];
  for (int i = 0; i < 9; i++) {
    if (flags[i]) {
      bool_buffer[i] = '1';
    } else {
      bool_buffer[i] = '0';
    }
  }
  setBufferValues(buf, current_bit, FLAG_SIZE, bool_buffer);
  current_bit += FLAG_SIZE;

  _itoa_s(window_size, unsigned_int_buffer, 10);
  setBufferValues(buf, current_bit, WINDOW_SIZE_SIZE, unsigned_int_buffer);
  current_bit += WINDOW_SIZE_SIZE;

  // Leave space for checksum
  current_bit += CHECKSUM_SIZE;

  char timestamp_buffer[TIMESTAMP_SIZE];
  _i64toa_s(timestamp, timestamp_buffer, TIMESTAMP_SIZE, 10);
  setBufferValues(buf, current_bit, TIMESTAMP_SIZE, timestamp_buffer);
  current_bit += TIMESTAMP_SIZE;

  _itoa_s(data_size, unsigned_int_buffer, 10);
  setBufferValues(buf, current_bit, DATA_SIZE_SIZE, unsigned_int_buffer);
  current_bit += DATA_SIZE_SIZE;

  if (data_size != 0) {
    setBufferValues(buf, current_bit, data_size, content);
  }

  // Calculate checksum and set it
  char* csum = calculateCsum(buf);
  setCsum(buf, csum);
  free(csum);
}