/*
* Create a new Client Key Exchange message
*/
Client_Key_Exchange::Client_Key_Exchange(Handshake_IO& io,
                                         Handshake_State& state,
                                         const Policy& policy,
                                         Credentials_Manager& creds,
                                         const Public_Key* server_public_key,
                                         const std::string& hostname,
                                         RandomNumberGenerator& rng)
   {
   const std::string kex_algo = state.ciphersuite().kex_algo();

   if(kex_algo == "PSK")
      {
      std::string identity_hint = "";

      if(state.server_kex())
         {
         TLS_Data_Reader reader("ClientKeyExchange", state.server_kex()->params());
         identity_hint = reader.get_string(2, 0, 65535);
         }

      const std::string psk_identity = creds.psk_identity("tls-client",
                                                          hostname,
                                                          identity_hint);

      append_tls_length_value(m_key_material, psk_identity, 2);

      SymmetricKey psk = creds.psk("tls-client", hostname, psk_identity);

      std::vector<byte> zeros(psk.length());

      append_tls_length_value(m_pre_master, zeros, 2);
      append_tls_length_value(m_pre_master, psk.bits_of(), 2);
      }
   else if(state.server_kex())
      {
      TLS_Data_Reader reader("ClientKeyExchange", state.server_kex()->params());

      SymmetricKey psk;

      if(kex_algo == "DHE_PSK" || kex_algo == "ECDHE_PSK")
         {
         std::string identity_hint = reader.get_string(2, 0, 65535);

         const std::string psk_identity = creds.psk_identity("tls-client",
                                                             hostname,
                                                             identity_hint);

         append_tls_length_value(m_key_material, psk_identity, 2);

         psk = creds.psk("tls-client", hostname, psk_identity);
         }

      if(kex_algo == "DH" || kex_algo == "DHE_PSK")
         {
         BigInt p = BigInt::decode(reader.get_range<byte>(2, 1, 65535));
         BigInt g = BigInt::decode(reader.get_range<byte>(2, 1, 65535));
         BigInt Y = BigInt::decode(reader.get_range<byte>(2, 1, 65535));

         if(reader.remaining_bytes())
            throw Decoding_Error("Bad params size for DH key exchange");

         if(p.bits() < policy.minimum_dh_group_size())
            throw TLS_Exception(Alert::INSUFFICIENT_SECURITY,
                                "Server sent DH group of " +
                                std::to_string(p.bits()) +
                                " bits, policy requires at least " +
                                std::to_string(policy.minimum_dh_group_size()));

         /*
         * A basic check for key validity. As we do not know q here we
         * cannot check that Y is in the right subgroup. However since
         * our key is ephemeral there does not seem to be any
         * advantage to bogus keys anyway.
         */
         if(Y <= 1 || Y >= p - 1)
            throw TLS_Exception(Alert::INSUFFICIENT_SECURITY,
                                "Server sent bad DH key for DHE exchange");

         DL_Group group(p, g);

         if(!group.verify_group(rng, false))
            throw TLS_Exception(Alert::INSUFFICIENT_SECURITY,
                                "DH group validation failed");

         DH_PublicKey counterparty_key(group, Y);

         DH_PrivateKey priv_key(rng, group);

         PK_Key_Agreement ka(priv_key, "Raw");

         secure_vector<byte> dh_secret = CT::strip_leading_zeros(
            ka.derive_key(0, counterparty_key.public_value()).bits_of());

         if(kex_algo == "DH")
            m_pre_master = dh_secret;
         else
            {
            append_tls_length_value(m_pre_master, dh_secret, 2);
            append_tls_length_value(m_pre_master, psk.bits_of(), 2);
            }

         append_tls_length_value(m_key_material, priv_key.public_value(), 2);
         }
      else if(kex_algo == "ECDH" || kex_algo == "ECDHE_PSK")
         {
         const byte curve_type = reader.get_byte();

         if(curve_type != 3)
            throw Decoding_Error("Server sent non-named ECC curve");

         const u16bit curve_id = reader.get_u16bit();

         const std::string name = Supported_Elliptic_Curves::curve_id_to_name(curve_id);

         if(name == "")
            throw Decoding_Error("Server sent unknown named curve " + std::to_string(curve_id));

         EC_Group group(name);

         std::vector<byte> ecdh_key = reader.get_range<byte>(1, 1, 255);

         ECDH_PublicKey counterparty_key(group, OS2ECP(ecdh_key, group.get_curve()));

         ECDH_PrivateKey priv_key(rng, group);

         PK_Key_Agreement ka(priv_key, "Raw");

         secure_vector<byte> ecdh_secret =
            ka.derive_key(0, counterparty_key.public_value()).bits_of();

         if(kex_algo == "ECDH")
            m_pre_master = ecdh_secret;
         else
            {
            append_tls_length_value(m_pre_master, ecdh_secret, 2);
            append_tls_length_value(m_pre_master, psk.bits_of(), 2);
            }

         append_tls_length_value(m_key_material, priv_key.public_value(), 1);
         }
#if defined(BOTAN_HAS_SRP6)
      else if(kex_algo == "SRP_SHA")
         {
         const BigInt N = BigInt::decode(reader.get_range<byte>(2, 1, 65535));
         const BigInt g = BigInt::decode(reader.get_range<byte>(2, 1, 65535));
         std::vector<byte> salt = reader.get_range<byte>(1, 1, 255);
         const BigInt B = BigInt::decode(reader.get_range<byte>(2, 1, 65535));

         const std::string srp_group = srp6_group_identifier(N, g);

         const std::string srp_identifier =
            creds.srp_identifier("tls-client", hostname);

         const std::string srp_password =
            creds.srp_password("tls-client", hostname, srp_identifier);

         std::pair<BigInt, SymmetricKey> srp_vals =
            srp6_client_agree(srp_identifier,
                              srp_password,
                              srp_group,
                              "SHA-1",
                              salt,
                              B,
                              rng);

         append_tls_length_value(m_key_material, BigInt::encode(srp_vals.first), 2);
         m_pre_master = srp_vals.second.bits_of();
         }
#endif
      else
         {
         throw Internal_Error("Client_Key_Exchange: Unknown kex " +
                              kex_algo);
         }

      reader.assert_done();
      }
   else
      {
      // No server key exchange msg better mean RSA kex + RSA key in cert

      if(kex_algo != "RSA")
         throw Unexpected_Message("No server kex but negotiated kex " + kex_algo);

      if(!server_public_key)
         throw Internal_Error("No server public key for RSA exchange");

      if(auto rsa_pub = dynamic_cast<const RSA_PublicKey*>(server_public_key))
         {
         const Protocol_Version offered_version = state.client_hello()->version();

         m_pre_master = rng.random_vec(48);
         m_pre_master[0] = offered_version.major_version();
         m_pre_master[1] = offered_version.minor_version();

         PK_Encryptor_EME encryptor(*rsa_pub, "PKCS1v15");

         const std::vector<byte> encrypted_key = encryptor.encrypt(m_pre_master, rng);

         append_tls_length_value(m_key_material, encrypted_key, 2);
         }
      else
         throw TLS_Exception(Alert::HANDSHAKE_FAILURE,
                             "Expected a RSA key in server cert but got " +
                             server_public_key->algo_name());
      }

   state.hash().update(io.send(*this));
   }