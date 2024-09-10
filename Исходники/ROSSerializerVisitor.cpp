 void ROSSerializerVisitor::write(const uint32_t &/*id*/, const float &v) {
     m_size += sizeof(const float);
     float _v = htonf(v);
     m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
 }