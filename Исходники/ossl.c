/*
 * OpenSSL provides SSL, TLS and general purpose cryptography.  It wraps the
 * OpenSSL[http://www.openssl.org/] library.
 *
 * = Examples
 *
 * All examples assume you have loaded OpenSSL with:
 *
 *   require 'openssl'
 *
 * These examples build atop each other.  For example the key created in the
 * next is used in throughout these examples.
 *
 * == Keys
 *
 * === Creating a Key
 *
 * This example creates a 2048 bit RSA keypair and writes it to the current
 * directory.
 *
 *   key = OpenSSL::PKey::RSA.new 2048
 *
 *   open 'private_key.pem', 'w' do |io| io.write key.to_pem end
 *   open 'public_key.pem', 'w' do |io| io.write key.public_key.to_pem end
 *
 * === Exporting a Key
 *
 * Keys saved to disk without encryption are not secure as anyone who gets
 * ahold of the key may use it unless it is encrypted.  In order to securely
 * export a key you may export it with a pass phrase.
 *
 *   cipher = OpenSSL::Cipher.new 'AES-128-CBC'
 *   pass_phrase = 'my secure pass phrase goes here'
 *
 *   key_secure = key.export cipher, pass_phrase
 *
 *   open 'private.secure.pem', 'w' do |io|
 *     io.write key_secure
 *   end
 *
 * OpenSSL::Cipher.ciphers returns a list of available ciphers.
 *
 * === Loading a Key
 *
 * A key can also be loaded from a file.
 *
 *   key2 = OpenSSL::PKey::RSA.new File.read 'private_key.pem'
 *   key2.public? # => true
 *
 * or
 *
 *   key3 = OpenSSL::PKey::RSA.new File.read 'public_key.pem'
 *   key3.private? # => false
 *
 * === Loading an Encrypted Key
 *
 * OpenSSL will prompt you for your pass phrase when loading an encrypted key.
 * If you will not be able to type in the pass phrase you may provide it when
 * loading the key:
 *
 *   key4_pem = File.read 'private.secure.pem'
 *   key4 = OpenSSL::PKey::RSA.new key4_pem, pass_phrase
 *
 * == RSA Encryption
 *
 * RSA provides encryption and decryption using the public and private keys.
 * You can use a variety of padding methods depending upon the intended use of
 * encrypted data.
 *
 * === Encryption & Decryption
 *
 * Asymmetric public/private key encryption is slow and victim to attack in
 * cases where it is used without padding or directly to encrypt larger chunks
 * of data. Typical use cases for RSA encryption involve "wrapping" a symmetric
 * key with the public key of the recipient who would "unwrap" that symmetric
 * key again using their private key.
 * The following illustrates a simplified example of such a key transport
 * scheme. It shouldn't be used in practice, though, standardized protocols
 * should always be preferred.
 *
 *   wrapped_key = key.public_encrypt key
 *
 * A symmetric key encrypted with the public key can only be decrypted with
 * the corresponding private key of the recipient.
 *
 *   original_key = key.private_decrypt wrapped_key
 *
 * By default PKCS#1 padding will be used, but it is also possible to use
 * other forms of padding, see PKey::RSA for further details.
 *
 * === Signatures
 *
 * Using "private_encrypt" to encrypt some data with the private key is
 * equivalent to applying a digital signature to the data. A verifying
 * party may validate the signature by comparing the result of decrypting
 * the signature with "public_decrypt" to the original data. However,
 * OpenSSL::PKey already has methods "sign" and "verify" that handle
 * digital signatures in a standardized way - "private_encrypt" and
 * "public_decrypt" shouldn't be used in practice.
 *
 * To sign a document, a cryptographically secure hash of the document is
 * computed first, which is then signed using the private key.
 *
 *   digest = OpenSSL::Digest::SHA256.new
 *   signature = key.sign digest, document
 *
 * To validate the signature, again a hash of the document is computed and
 * the signature is decrypted using the public key. The result is then
 * compared to the hash just computed, if they are equal the signature was
 * valid.
 *
 *   digest = OpenSSL::Digest::SHA256.new
 *   if key.verify digest, signature, document
 *     puts 'Valid'
 *   else
 *     puts 'Invalid'
 *   end
 *
 * == PBKDF2 Password-based Encryption
 *
 * If supported by the underlying OpenSSL version used, Password-based
 * Encryption should use the features of PKCS5. If not supported or if
 * required by legacy applications, the older, less secure methods specified
 * in RFC 2898 are also supported (see below).
 *
 * PKCS5 supports PBKDF2 as it was specified in PKCS#5
 * v2.0[http://www.rsa.com/rsalabs/node.asp?id=2127]. It still uses a
 * password, a salt, and additionally a number of iterations that will
 * slow the key derivation process down. The slower this is, the more work
 * it requires being able to brute-force the resulting key.
 *
 * === Encryption
 *
 * The strategy is to first instantiate a Cipher for encryption, and
 * then to generate a random IV plus a key derived from the password
 * using PBKDF2. PKCS #5 v2.0 recommends at least 8 bytes for the salt,
 * the number of iterations largely depends on the hardware being used.
 *
 *   cipher = OpenSSL::Cipher.new 'AES-128-CBC'
 *   cipher.encrypt
 *   iv = cipher.random_iv
 *
 *   pwd = 'some hopefully not to easily guessable password'
 *   salt = OpenSSL::Random.random_bytes 16
 *   iter = 20000
 *   key_len = cipher.key_len
 *   digest = OpenSSL::Digest::SHA256.new
 *
 *   key = OpenSSL::PKCS5.pbkdf2_hmac(pwd, salt, iter, key_len, digest)
 *   cipher.key = key
 *
 *   Now encrypt the data:
 *
 *   encrypted = cipher.update document
 *   encrypted << cipher.final
 *
 * === Decryption
 *
 * Use the same steps as before to derive the symmetric AES key, this time
 * setting the Cipher up for decryption.
 *
 *   cipher = OpenSSL::Cipher.new 'AES-128-CBC'
 *   cipher.decrypt
 *   cipher.iv = iv # the one generated with #random_iv
 *
 *   pwd = 'some hopefully not to easily guessable password'
 *   salt = ... # the one generated above
 *   iter = 20000
 *   key_len = cipher.key_len
 *   digest = OpenSSL::Digest::SHA256.new
 *
 *   key = OpenSSL::PKCS5.pbkdf2_hmac(pwd, salt, iter, key_len, digest)
 *   cipher.key = key
 *
 *   Now decrypt the data:
 *
 *   decrypted = cipher.update encrypted
 *   decrypted << cipher.final
 *
 * == PKCS #5 Password-based Encryption
 *
 * PKCS #5 is a password-based encryption standard documented at
 * RFC2898[http://www.ietf.org/rfc/rfc2898.txt].  It allows a short password or
 * passphrase to be used to create a secure encryption key. If possible, PBKDF2
 * as described above should be used if the circumstances allow it.
 *
 * PKCS #5 uses a Cipher, a pass phrase and a salt to generate an encryption
 * key.
 *
 *   pass_phrase = 'my secure pass phrase goes here'
 *   salt = '8 octets'
 *
 * === Encryption
 *
 * First set up the cipher for encryption
 *
 *   encrypter = OpenSSL::Cipher.new 'AES-128-CBC'
 *   encrypter.encrypt
 *   encrypter.pkcs5_keyivgen pass_phrase, salt
 *
 * Then pass the data you want to encrypt through
 *
 *   encrypted = encrypter.update 'top secret document'
 *   encrypted << encrypter.final
 *
 * === Decryption
 *
 * Use a new Cipher instance set up for decryption
 *
 *   decrypter = OpenSSL::Cipher.new 'AES-128-CBC'
 *   decrypter.decrypt
 *   decrypter.pkcs5_keyivgen pass_phrase, salt
 *
 * Then pass the data you want to decrypt through
 *
 *   plain = decrypter.update encrypted
 *   plain << decrypter.final
 *
 * == X509 Certificates
 *
 * === Creating a Certificate
 *
 * This example creates a self-signed certificate using an RSA key and a SHA1
 * signature.
 *
 *   name = OpenSSL::X509::Name.parse 'CN=nobody/DC=example'
 *
 *   cert = OpenSSL::X509::Certificate.new
 *   cert.version = 2
 *   cert.serial = 0
 *   cert.not_before = Time.now
 *   cert.not_after = Time.now + 3600
 *
 *   cert.public_key = key.public_key
 *   cert.subject = name
 *
 * === Certificate Extensions
 *
 * You can add extensions to the certificate with
 * OpenSSL::SSL::ExtensionFactory to indicate the purpose of the certificate.
 *
 *   extension_factory = OpenSSL::X509::ExtensionFactory.new nil, cert
 *
 *   cert.add_extension \
 *     extension_factory.create_extension('basicConstraints', 'CA:FALSE', true)
 *
 *   cert.add_extension \
 *     extension_factory.create_extension(
 *       'keyUsage', 'keyEncipherment,dataEncipherment,digitalSignature')
 *
 *   cert.add_extension \
 *     extension_factory.create_extension('subjectKeyIdentifier', 'hash')
 *
 * The list of supported extensions (and in some cases their possible values)
 * can be derived from the "objects.h" file in the OpenSSL source code.
 *
 * === Signing a Certificate
 *
 * To sign a certificate set the issuer and use OpenSSL::X509::Certificate#sign
 * with a digest algorithm.  This creates a self-signed cert because we're using
 * the same name and key to sign the certificate as was used to create the
 * certificate.
 *
 *   cert.issuer = name
 *   cert.sign key, OpenSSL::Digest::SHA1.new
 *
 *   open 'certificate.pem', 'w' do |io| io.write cert.to_pem end
 *
 * === Loading a Certificate
 *
 * Like a key, a cert can also be loaded from a file.
 *
 *   cert2 = OpenSSL::X509::Certificate.new File.read 'certificate.pem'
 *
 * === Verifying a Certificate
 *
 * Certificate#verify will return true when a certificate was signed with the
 * given public key.
 *
 *   raise 'certificate can not be verified' unless cert2.verify key
 *
 * == Certificate Authority
 *
 * A certificate authority (CA) is a trusted third party that allows you to
 * verify the ownership of unknown certificates.  The CA issues key signatures
 * that indicate it trusts the user of that key.  A user encountering the key
 * can verify the signature by using the CA's public key.
 *
 * === CA Key
 *
 * CA keys are valuable, so we encrypt and save it to disk and make sure it is
 * not readable by other users.
 *
 *   ca_key = OpenSSL::PKey::RSA.new 2048
 *
 *   cipher = OpenSSL::Cipher::Cipher.new 'AES-128-CBC'
 *
 *   open 'ca_key.pem', 'w', 0400 do |io|
 *     io.write key.export(cipher, pass_phrase)
 *   end
 *
 * === CA Certificate
 *
 * A CA certificate is created the same way we created a certificate above, but
 * with different extensions.
 *
 *   ca_name = OpenSSL::X509::Name.parse 'CN=ca/DC=example'
 *
 *   ca_cert = OpenSSL::X509::Certificate.new
 *   ca_cert.serial = 0
 *   ca_cert.version = 2
 *   ca_cert.not_before = Time.now
 *   ca_cert.not_after = Time.now + 86400
 *
 *   ca_cert.public_key = ca_key.public_key
 *   ca_cert.subject = ca_name
 *   ca_cert.issuer = ca_name
 *
 *   extension_factory = OpenSSL::X509::ExtensionFactory.new
 *   extension_factory.subject_certificate = ca_cert
 *   extension_factory.issuer_certificate = ca_cert
 *
 *   ca_cert.add_extension \
 *     extension_factory.create_extension('subjectKeyIdentifier', 'hash')
 *
 * This extension indicates the CA's key may be used as a CA.
 *
 *   ca_cert.add_extension \
 *     extension_factory.create_extension('basicConstraints', 'CA:TRUE', true)
 *
 * This extension indicates the CA's key may be used to verify signatures on
 * both certificates and certificate revocations.
 *
 *   ca_cert.add_extension \
 *     extension_factory.create_extension(
 *       'keyUsage', 'cRLSign,keyCertSign', true)
 *
 * Root CA certificates are self-signed.
 *
 *   ca_cert.sign ca_key, OpenSSL::Digest::SHA1.new
 *
 * The CA certificate is saved to disk so it may be distributed to all the
 * users of the keys this CA will sign.
 *
 *   open 'ca_cert.pem', 'w' do |io|
 *     io.write ca_cert.to_pem
 *   end
 *
 * === Certificate Signing Request
 *
 * The CA signs keys through a Certificate Signing Request (CSR).  The CSR
 * contains the information necessary to identify the key.
 *
 *   csr = OpenSSL::X509::Request.new
 *   csr.version = 0
 *   csr.subject = name
 *   csr.public_key = key.public_key
 *   csr.sign key, OpenSSL::Digest::SHA1.new
 *
 * A CSR is saved to disk and sent to the CA for signing.
 *
 *   open 'csr.pem', 'w' do |io|
 *     io.write csr.to_pem
 *   end
 *
 * === Creating a Certificate from a CSR
 *
 * Upon receiving a CSR the CA will verify it before signing it.  A minimal
 * verification would be to check the CSR's signature.
 *
 *   csr = OpenSSL::X509::Request.new File.read 'csr.pem'
 *
 *   raise 'CSR can not be verified' unless csr.verify csr.public_key
 *
 * After verification a certificate is created, marked for various usages,
 * signed with the CA key and returned to the requester.
 *
 *   csr_cert = OpenSSL::X509::Certificate.new
 *   csr_cert.serial = 0
 *   csr_cert.version = 2
 *   csr_cert.not_before = Time.now
 *   csr_cert.not_after = Time.now + 600
 *
 *   csr_cert.subject = csr.subject
 *   csr_cert.public_key = csr.public_key
 *   csr_cert.issuer = ca_cert.subject
 *
 *   extension_factory = OpenSSL::X509::ExtensionFactory.new
 *   extension_factory.subject_certificate = csr_cert
 *   extension_factory.issuer_certificate = ca_cert
 *
 *   csr_cert.add_extension \
 *     extension_factory.create_extension('basicConstraints', 'CA:FALSE')
 *
 *   csr_cert.add_extension \
 *     extension_factory.create_extension(
 *       'keyUsage', 'keyEncipherment,dataEncipherment,digitalSignature')
 *
 *   csr_cert.add_extension \
 *     extension_factory.create_extension('subjectKeyIdentifier', 'hash')
 *
 *   csr_cert.sign ca_key, OpenSSL::Digest::SHA1.new
 *
 *   open 'csr_cert.pem', 'w' do |io|
 *     io.write csr_cert.to_pem
 *   end
 *
 * == SSL and TLS Connections
 *
 * Using our created key and certificate we can create an SSL or TLS connection.
 * An SSLContext is used to set up an SSL session.
 *
 *   context = OpenSSL::SSL::SSLContext.new
 *
 * === SSL Server
 *
 * An SSL server requires the certificate and private key to communicate
 * securely with its clients:
 *
 *   context.cert = cert
 *   context.key = key
 *
 * Then create an SSLServer with a TCP server socket and the context.  Use the
 * SSLServer like an ordinary TCP server.
 *
 *   require 'socket'
 *
 *   tcp_server = TCPServer.new 5000
 *   ssl_server = OpenSSL::SSL::SSLServer.new tcp_server, context
 *
 *   loop do
 *     ssl_connection = ssl_server.accept
 *
 *     data = connection.gets
 *
 *     response = "I got #{data.dump}"
 *     puts response
 *
 *     connection.puts "I got #{data.dump}"
 *     connection.close
 *   end
 *
 * === SSL client
 *
 * An SSL client is created with a TCP socket and the context.
 * SSLSocket#connect must be called to initiate the SSL handshake and start
 * encryption.  A key and certificate are not required for the client socket.
 *
 *   require 'socket'
 *
 *   tcp_client = TCPSocket.new 'localhost', 5000
 *   ssl_client = OpenSSL::SSL::SSLSocket.new client_socket, context
 *   ssl_client.connect
 *
 *   ssl_client.puts "hello server!"
 *   puts ssl_client.gets
 *
 * === Peer Verification
 *
 * An unverified SSL connection does not provide much security.  For enhanced
 * security the client or server can verify the certificate of its peer.
 *
 * The client can be modified to verify the server's certificate against the
 * certificate authority's certificate:
 *
 *   context.ca_file = 'ca_cert.pem'
 *   context.verify_mode = OpenSSL::SSL::VERIFY_PEER
 *
 *   require 'socket'
 *
 *   tcp_client = TCPSocket.new 'localhost', 5000
 *   ssl_client = OpenSSL::SSL::SSLSocket.new client_socket, context
 *   ssl_client.connect
 *
 *   ssl_client.puts "hello server!"
 *   puts ssl_client.gets
 *
 * If the server certificate is invalid or <tt>context.ca_file</tt> is not set
 * when verifying peers an OpenSSL::SSL::SSLError will be raised.
 *
 */
void
Init_openssl()
{
    /*
     * Init timezone info
     */
#if 0
    tzset();
#endif

    /*
     * Init all digests, ciphers
     */
    /* CRYPTO_malloc_init(); */
    /* ENGINE_load_builtin_engines(); */
    OpenSSL_add_ssl_algorithms();
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();
    SSL_load_error_strings();

    /*
     * FIXME:
     * On unload do:
     */
#if 0
    CONF_modules_unload(1);
    destroy_ui_method();
    EVP_cleanup();
    ENGINE_cleanup();
    CRYPTO_cleanup_all_ex_data();
    ERR_remove_state(0);
    ERR_free_strings();
#endif

    /*
     * Init main module
     */
    mOSSL = rb_define_module("OpenSSL");

    /*
     * OpenSSL ruby extension version
     */
    rb_define_const(mOSSL, "VERSION", rb_str_new2(OSSL_VERSION));

    /*
     * Version of OpenSSL the ruby OpenSSL extension was built with
     */
    rb_define_const(mOSSL, "OPENSSL_VERSION", rb_str_new2(OPENSSL_VERSION_TEXT));

    /*
     * Version of OpenSSL the ruby OpenSSL extension is running with
     */
    rb_define_const(mOSSL, "OPENSSL_LIBRARY_VERSION", rb_str_new2(SSLeay_version(SSLEAY_VERSION)));

    /*
     * Version number of OpenSSL the ruby OpenSSL extension was built with
     * (base 16)
     */
    rb_define_const(mOSSL, "OPENSSL_VERSION_NUMBER", INT2NUM(OPENSSL_VERSION_NUMBER));

    /*
     * Boolean indicating whether OpenSSL is FIPS-enabled or not
     */
#ifdef HAVE_OPENSSL_FIPS
    rb_define_const(mOSSL, "OPENSSL_FIPS", Qtrue);
#else
    rb_define_const(mOSSL, "OPENSSL_FIPS", Qfalse);
#endif
    rb_define_module_function(mOSSL, "fips_mode=", ossl_fips_mode_set, 1);

    /*
     * Generic error,
     * common for all classes under OpenSSL module
     */
    eOSSLError = rb_define_class_under(mOSSL,"OpenSSLError",rb_eStandardError);

    /*
     * Verify callback Proc index for ext-data
     */
    if ((ossl_verify_cb_idx = X509_STORE_CTX_get_ex_new_index(0, (void *)"ossl_verify_cb_idx", 0, 0, 0)) < 0)
        ossl_raise(eOSSLError, "X509_STORE_CTX_get_ex_new_index");

    /*
     * Init debug core
     */
    dOSSL = Qfalse;
    rb_define_module_function(mOSSL, "debug", ossl_debug_get, 0);
    rb_define_module_function(mOSSL, "debug=", ossl_debug_set, 1);
    rb_define_module_function(mOSSL, "errors", ossl_get_errors, 0);

    /*
     * Get ID of to_der
     */
    ossl_s_to_der = rb_intern("to_der");

    /*
     * Init components
     */
    Init_ossl_bn();
    Init_ossl_cipher();
    Init_ossl_config();
    Init_ossl_digest();
    Init_ossl_hmac();
    Init_ossl_ns_spki();
    Init_ossl_pkcs12();
    Init_ossl_pkcs7();
    Init_ossl_pkcs5();
    Init_ossl_pkey();
    Init_ossl_rand();
    Init_ossl_ssl();
    Init_ossl_x509();
    Init_ossl_ocsp();
    Init_ossl_engine();
    Init_ossl_asn1();
}