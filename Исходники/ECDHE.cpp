void ECDHEKeyExchange::exchange(bytes& o_exchange)
{
	if (!m_ephemeralSecret)
		// didn't agree on public remote
		BOOST_THROW_EXCEPTION(InvalidState());

	// The key exchange payload is in two parts and is encrypted
	// using ephemeral keypair.
	//
	// The first part is the 'prefix' which is a zero-knowledge proof
	// allowing the remote to resume or emplace a previous session.
	// If a session previously exists:
	//	prefix is sha3(token) // todo: ephemeral entropy from both sides
	// If a session doesn't exist:
	//	prefix is sha3(m_ephemeralSecret)
	//
	// The second part is encrypted using the public key which relates to the prefix.
	
	Public encpk = m_known.first ? m_known.first : m_remoteEphemeral;
	bytes exchange(encpk.asBytes());
	
	// This is the public key which we would like the remote to use,
	// which maybe different than the previously-known public key.
	//
	// Here we should pick an appropriate alias or generate a new one,
	// but for now, we use static alias passed to constructor.
	//
	Public p = toPublic(m_alias.m_secret);
	exchange.resize(exchange.size() + sizeof(p));
	memcpy(&exchange[exchange.size() - sizeof(p)], p.data(), sizeof(p));
	
	// protocol parameters; should be fixed size
	bytes v(1, 0x80);
	exchange.resize(exchange.size() + v.size());
	memcpy(&exchange[exchange.size() - v.size()], v.data(), v.size());
	
	h256 auth;
	sha3mac(m_alias.m_secret.ref(), m_ephemeralSecret.ref(), auth.ref());
	Signature sig = s_secp256k1.sign(m_alias.m_secret, auth);
	exchange.resize(exchange.size() + sizeof(sig));
	memcpy(&exchange[exchange.size() - sizeof(sig)], sig.data(), sizeof(sig));
	
	aes::AuthenticatedStream aes(aes::Encrypt, m_ephemeralSecret, 0);
	h256 prefix(sha3(m_known.second ? m_known.second : (h256)m_remoteEphemeral));
	aes.update(prefix.ref());
	
	s_secp256k1.encrypt(encpk, exchange);
	aes.update(&exchange);

	aes.streamOut(o_exchange);
}