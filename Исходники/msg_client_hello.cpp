/*
* Create a new Client Hello message
*/
Client_Hello::Client_Hello(Handshake_IO& io,
                           Handshake_Hash& hash,
                           const Policy& policy,
                           RandomNumberGenerator& rng,
                           const std::vector<uint8_t>& reneg_info,
                           const Client_Hello::Settings& client_settings,
                           const std::vector<std::string>& next_protocols) :
   m_version(client_settings.protocol_version()),
   m_random(make_hello_random(rng, policy)),
   m_suites(policy.ciphersuite_list(m_version, !client_settings.srp_identifier().empty())),
   m_comp_methods(policy.compression())
   {
   BOTAN_ASSERT(policy.acceptable_protocol_version(client_settings.protocol_version()),
                "Our policy accepts the version we are offering");

   /*
   * Place all empty extensions in front to avoid a bug in some systems
   * which reject hellos when the last extension in the list is empty.
   */
   m_extensions.add(new Extended_Master_Secret);
   m_extensions.add(new Session_Ticket());

   if(policy.negotiate_encrypt_then_mac())
      m_extensions.add(new Encrypt_then_MAC);

   m_extensions.add(new Renegotiation_Extension(reneg_info));
   m_extensions.add(new Server_Name_Indicator(client_settings.hostname()));

   if(policy.support_cert_status_message())
      m_extensions.add(new Certificate_Status_Request({}, {}));

   if(reneg_info.empty() && !next_protocols.empty())
      m_extensions.add(new Application_Layer_Protocol_Notification(next_protocols));

   if(m_version.supports_negotiable_signature_algorithms())
      m_extensions.add(new Signature_Algorithms(policy.allowed_signature_hashes(),
                                                policy.allowed_signature_methods()));

   if(m_version.is_datagram_protocol())
      m_extensions.add(new SRTP_Protection_Profiles(policy.srtp_profiles()));

#if defined(BOTAN_HAS_SRP6)
   m_extensions.add(new SRP_Identifier(client_settings.srp_identifier()));
#else
   if(!client_settings.srp_identifier().empty())
      {
      throw Invalid_State("Attempting to initiate SRP session but TLS-SRP support disabled");
      }
#endif

   Supported_Groups* supported_groups = new Supported_Groups(policy.allowed_groups());
   m_extensions.add(supported_groups);

   if(!supported_groups->curves().empty())
      {
      m_extensions.add(new Supported_Point_Formats(policy.use_ecc_point_compression()));
      }

   if(m_version.supports_negotiable_signature_algorithms())
      m_extensions.add(new Signature_Algorithms(policy.allowed_signature_hashes(),
                                                policy.allowed_signature_methods()));

   if(policy.send_fallback_scsv(client_settings.protocol_version()))
      m_suites.push_back(TLS_FALLBACK_SCSV);

   hash.update(io.send(*this));
   }