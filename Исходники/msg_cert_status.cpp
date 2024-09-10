Certificate_Status::Certificate_Status(Handshake_IO& io,
                                       Handshake_Hash& hash,
                                       const std::vector<uint8_t>& raw_response_bytes) :
   m_response(raw_response_bytes)
   {
   hash.update(io.send(*this));
   }