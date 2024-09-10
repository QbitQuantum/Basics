 void LCMDeserializerVisitor::read(const uint32_t &/*id*/, const string &/*longName*/, const string &/*shortName*/, double &v) {
     double _v = 0;
     m_buffer.read(reinterpret_cast<char *>(&_v), sizeof(double));
     v = ntohd(_v);
 }