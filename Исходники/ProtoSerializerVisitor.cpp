        void ProtoSerializerVisitor::write(const uint32_t &fourByteID, const uint8_t &oneByteID, const string &/*longName*/, const string &/*shortName*/, const float &v) {
            uint32_t key = getKey( (oneByteID > 0 ? oneByteID : fourByteID) , ProtoSerializerVisitor::FOUR_BYTES);
            m_size += encodeVarInt(m_buffer, key);

            float _v = htonf(v);
            m_buffer.write(reinterpret_cast<const char*>(&_v), sizeof(const float));
            m_size += sizeof(const float);
        }