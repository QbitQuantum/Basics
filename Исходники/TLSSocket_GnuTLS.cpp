void TLSSocket_GnuTLS::handshake() {

	shared_ptr <timeoutHandler> toHandler = m_wrapped->getTimeoutHandler();

	if (toHandler) {
		toHandler->resetTimeOut();
	}

	if (getTracer()) {
		getTracer()->traceSend("Beginning SSL/TLS handshake");
	}

	// Start handshaking process
	try {

		while (true) {

			resetException();

			const int ret = gnutls_handshake(*m_session->m_gnutlsSession);

			throwException();

			if (ret < 0) {

				if (ret == GNUTLS_E_AGAIN) {

					if (gnutls_record_get_direction(*m_session->m_gnutlsSession) == 0) {
						m_wrapped->waitForRead();
					} else {
						m_wrapped->waitForWrite();
					}

				} else if (ret == GNUTLS_E_INTERRUPTED) {

					// Non-fatal error

				} else {

					TLSSession_GnuTLS::throwTLSException("gnutls_handshake", ret);
				}

			} else {

				// Successful handshake
				break;
			}
		}

	} catch (...) {

		throw;
	}

	// Verify server's certificate(s)
	shared_ptr <security::cert::certificateChain> certs = getPeerCertificates();

	if (certs == NULL) {
		throw exceptions::tls_exception("No peer certificate.");
	}

	m_session->getCertificateVerifier()->verify(certs, getPeerName());

	m_connected = true;
}