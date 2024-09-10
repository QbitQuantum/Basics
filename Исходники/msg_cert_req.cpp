/**
* Create a new Certificate Request message
*/
Certificate_Req::Certificate_Req(Handshake_IO& io,
                                 Handshake_Hash& hash,
                                 const Policy& policy,
                                 const std::vector<X509_DN>& ca_certs,
                                 Protocol_Version version) :
   m_names(ca_certs),
   m_cert_key_types({ "RSA", "DSA", "ECDSA" })
   {
   if(version.supports_negotiable_signature_algorithms())
      {
      std::vector<std::string> hashes = policy.allowed_signature_hashes();
      std::vector<std::string> sigs = policy.allowed_signature_methods();

      for(size_t i = 0; i != hashes.size(); ++i)
         for(size_t j = 0; j != sigs.size(); ++j)
            m_supported_algos.push_back(std::make_pair(hashes[i], sigs[j]));
      }

   hash.update(io.send(*this));
   }