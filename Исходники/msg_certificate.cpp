/**
* Create a new Certificate message
*/
Certificate::Certificate(Handshake_IO& io,
                         Handshake_Hash& hash,
                         const std::vector<X509_Certificate>& cert_list) :
   m_certs(cert_list)
   {
   hash.update(io.send(*this));
   }