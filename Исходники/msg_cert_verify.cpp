/*
* Create a new Certificate Verify message
*/
Certificate_Verify::Certificate_Verify(Handshake_IO& io,
                                       Handshake_State& state,
                                       const Policy& policy,
                                       RandomNumberGenerator& rng,
                                       const Private_Key* priv_key)
   {
   BOTAN_ASSERT_NONNULL(priv_key);

   std::pair<std::string, Signature_Format> format =
      state.choose_sig_format(*priv_key, m_hash_algo, m_sig_algo, true, policy);

   PK_Signer signer(*priv_key, rng, format.first, format.second);

   m_signature = signer.sign_message(state.hash().get_contents(), rng);

   state.hash().update(io.send(*this));
   }