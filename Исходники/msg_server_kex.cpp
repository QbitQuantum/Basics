/**
* Create a new Server Key Exchange message
*/
Server_Key_Exchange::Server_Key_Exchange(Handshake_IO& io,
                                         Handshake_State& state,
                                         const Policy& policy,
                                         Credentials_Manager& creds,
                                         RandomNumberGenerator& rng,
                                         const Private_Key* signing_key)
   {
   const std::string hostname = state.client_hello()->sni_hostname();
   const std::string kex_algo = state.ciphersuite().kex_algo();

   if(kex_algo == "PSK" || kex_algo == "DHE_PSK" || kex_algo == "ECDHE_PSK")
      {
      std::string identity_hint =
         creds.psk_identity_hint("tls-server", hostname);

      append_tls_length_value(m_params, identity_hint, 2);
      }

   if(kex_algo == "DH" || kex_algo == "DHE_PSK")
      {
      std::unique_ptr<DH_PrivateKey> dh(new DH_PrivateKey(rng, DL_Group(policy.dh_group())));

      append_tls_length_value(m_params, BigInt::encode(dh->get_domain().get_p()), 2);
      append_tls_length_value(m_params, BigInt::encode(dh->get_domain().get_g()), 2);
      append_tls_length_value(m_params, dh->public_value(), 2);
      m_kex_key.reset(dh.release());
      }
   else if(kex_algo == "ECDH" || kex_algo == "ECDHE_PSK")
      {
      const std::vector<std::string>& curves =
         state.client_hello()->supported_ecc_curves();

      if(curves.empty())
         throw Internal_Error("Client sent no ECC extension but we negotiated ECDH");

      const std::string curve_name = policy.choose_curve(curves);

      if(curve_name == "")
         throw TLS_Exception(Alert::HANDSHAKE_FAILURE,
                             "Could not agree on an ECC curve with the client");

      EC_Group ec_group(curve_name);

      std::unique_ptr<ECDH_PrivateKey> ecdh(new ECDH_PrivateKey(rng, ec_group));

      const std::string ecdh_domain_oid = ecdh->domain().get_oid();
      const std::string domain = OIDS::lookup(OID(ecdh_domain_oid));

      if(domain == "")
         throw Internal_Error("Could not find name of ECDH domain " + ecdh_domain_oid);

      const u16bit named_curve_id = Supported_Elliptic_Curves::name_to_curve_id(domain);

      m_params.push_back(3); // named curve
      m_params.push_back(get_byte(0, named_curve_id));
      m_params.push_back(get_byte(1, named_curve_id));

      append_tls_length_value(m_params, ecdh->public_value(), 1);

      m_kex_key.reset(ecdh.release());
      }
#if defined(BOTAN_HAS_SRP6)
   else if(kex_algo == "SRP_SHA")
      {
      const std::string srp_identifier = state.client_hello()->srp_identifier();

      std::string group_id;
      BigInt v;
      std::vector<byte> salt;

      const bool found = creds.srp_verifier("tls-server", hostname,
                                            srp_identifier,
                                            group_id, v, salt,
                                            policy.hide_unknown_users());

      if(!found)
         throw TLS_Exception(Alert::UNKNOWN_PSK_IDENTITY,
                             "Unknown SRP user " + srp_identifier);

      m_srp_params.reset(new SRP6_Server_Session);

      BigInt B = m_srp_params->step1(v, group_id,
                                     "SHA-1", rng);

      DL_Group group(group_id);

      append_tls_length_value(m_params, BigInt::encode(group.get_p()), 2);
      append_tls_length_value(m_params, BigInt::encode(group.get_g()), 2);
      append_tls_length_value(m_params, salt, 1);
      append_tls_length_value(m_params, BigInt::encode(B), 2);
      }
#endif
   else if(kex_algo != "PSK")
      throw Internal_Error("Server_Key_Exchange: Unknown kex type " + kex_algo);

   if(state.ciphersuite().sig_algo() != "")
      {
      BOTAN_ASSERT(signing_key, "Signing key was set");

      std::pair<std::string, Signature_Format> format =
         state.choose_sig_format(*signing_key, m_hash_algo, m_sig_algo, false, policy);

      PK_Signer signer(*signing_key, format.first, format.second);

      signer.update(state.client_hello()->random());
      signer.update(state.server_hello()->random());
      signer.update(params());
      m_signature = signer.signature(rng);
      }

   state.hash().update(io.send(*this));
   }