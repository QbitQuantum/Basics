 void LCMSerializerVisitor::write(const uint32_t &/*fourByteID*/, const uint8_t &/*oneByteID*/, const string &/*longName*/, const string &/*shortName*/, const double &v) {
     double _v = htond(v);
     m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const double));
 }