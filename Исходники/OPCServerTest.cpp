 void CaptureData(uint8_t command, const uint8_t *data, unsigned int length) {
   m_received_data.Set(data, length);
   m_command = command;
   m_ss.Terminate();
 }