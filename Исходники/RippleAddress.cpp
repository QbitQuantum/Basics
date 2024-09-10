    void run()
    {
		testBase58(RippleAddress::VER_NODE_PUBLIC, 'n');
		testBase58(RippleAddress::VER_NODE_PRIVATE, 'h');
		testBase58(RippleAddress::VER_ACCOUNT_PUBLIC, 'p');
		testBase58(RippleAddress::VER_ACCOUNT_PRIVATE, 'h');
		testBase58(RippleAddress::VER_SEED, 's');

		// check pass phrase
		std::string strPass("paysharesmaster");
		std::string strBase58Seed("s3q5ZGX2ScQK2rJ4JATp7rND6X5npG3De8jMbB7tuvm2HAVHcCN");
		std::string strBase58NodePublic("nfbbWHgJqzqfH1cfRpMdPRkJ19cxTsdHkBtz1SLJJQfyf9Ax6vd");
		std::string strBase58AccountPublic("pGreoXKYybde1keKZwDCv8m5V1kT6JH37pgnTUVzdMkdygTixG8");
			
		AccountPrivateKey accountPrivateKey;
		NodePrivateKey nodePrivateKey;

		accountPrivateKey.fromPassPhrase(strPass);
		nodePrivateKey.fromPassPhrase(strPass);

		expect(accountPrivateKey.base58Seed() == "s3q5ZGX2ScQK2rJ4JATp7rND6X5npG3De8jMbB7tuvm2HAVHcCN", accountPrivateKey.base58Seed());
		expect(accountPrivateKey.base58AccountID() == "ganVp9o5emfzpwrG5QVUXqMv8AgLcdvySb", accountPrivateKey.base58AccountID());
		expect(accountPrivateKey.base58PublicKey() == strBase58AccountPublic, accountPrivateKey.base58PublicKey());
		expect(nodePrivateKey.base58PublicKey() == strBase58NodePublic, nodePrivateKey.base58PublicKey());


		Blob sig;
		uint256 message;
		accountPrivateKey.sign(message, sig);

		PaysharesPublicKey publicKey(accountPrivateKey.getPublicKey(), RippleAddress::VER_NODE_PUBLIC);
		expect(publicKey.verifySignature(message, sig), "Signature didn't verify");
		expect(publicKey.getAccountID() == accountPrivateKey.getAccountID(), "Account Id's mis match");
		expect(publicKey.base58AccountID() == accountPrivateKey.base58AccountID(), "Account Id's mis match");

        Blob nonCanonicalSig(sig);
        add_l(nonCanonicalSig.data() + 32);
        expect(sig != nonCanonicalSig, "Non-canonical signature equal to canonical signature");
        expect(crypto_sign_verify_detached(nonCanonicalSig.data(),
                                           message.data(), message.bytes,
                                           publicKey.vchData.data()) == 0,
               "Non-canonical signature didn't verify (ignoring canonical-ness)");
        expect(!publicKey.verifySignature(message, nonCanonicalSig), "Non-canonical signature verified");
		
		AccountPrivateKey privateKey2;
		privateKey2.fromString(strBase58Seed); // key from base58seed
		expect(privateKey2.base58Seed() == "s3q5ZGX2ScQK2rJ4JATp7rND6X5npG3De8jMbB7tuvm2HAVHcCN", privateKey2.base58Seed());
		expect(privateKey2.base58AccountID() == "ganVp9o5emfzpwrG5QVUXqMv8AgLcdvySb", privateKey2.base58AccountID());
		expect(privateKey2.base58PublicKey() == strBase58AccountPublic, privateKey2.base58PublicKey());
		privateKey2.sign(message, sig);
		expect(publicKey.verifySignature(message, sig), "Signature didn't verify"); // check with the previous pubkey

		// check random

		/// ======= OLD ====

		// Construct a seed.
		RippleAddress naSeed;

		expect(naSeed.setSeedGeneric("masterpassphrase"));
		expect(naSeed.humanSeed() == "s3q5ZGX2ScQK2rJ4JATp7rND6X5npG3De8jMbB7tuvm2HAVHcCN", naSeed.humanSeed());

		// Create node public/private key pair
		RippleAddress naNodePublic = RippleAddress::createNodePublic(naSeed);
		expect(naNodePublic.verifySignature(message, sig), "Signature didn't verify");
		expect(naNodePublic.humanNodePublic() == strBase58NodePublic, naNodePublic.humanNodePublic());

		naNodePublic.setNodePublic(strBase58NodePublic);
		expect(naNodePublic.verifySignature(message, sig), "Signature didn't verify");
		expect(naNodePublic.humanNodePublic() == strBase58NodePublic, naNodePublic.humanNodePublic());

		RippleAddress naAccountPublic = RippleAddress::createAccountPublic(naSeed);
		expect(naAccountPublic.humanAccountID() == "ganVp9o5emfzpwrG5QVUXqMv8AgLcdvySb", naAccountPublic.humanAccountID());
		expect(naAccountPublic.verifySignature(message, sig), "Signature didn't verify");
		expect(naAccountPublic.humanAccountPublic() == strBase58AccountPublic, naAccountPublic.humanAccountPublic());

		naAccountPublic.setAccountPublic(strBase58AccountPublic);
		expect(naAccountPublic.humanAccountID() == "ganVp9o5emfzpwrG5QVUXqMv8AgLcdvySb", naAccountPublic.humanAccountID());
		expect(naAccountPublic.verifySignature(message, sig), "Signature didn't verify");
		expect(naAccountPublic.humanAccountPublic() == strBase58AccountPublic, naAccountPublic.humanAccountPublic());

		Blob rippleSig;
		RippleAddress naAccountPrivate = RippleAddress::createAccountPrivate(naSeed);
		naAccountPrivate.sign(message, rippleSig);
		expect(rippleSig==sig, "Signature don't match");

		RippleAddress naNodePrivate = RippleAddress::createNodePrivate(naSeed);
		naNodePrivate.sign(message, rippleSig);
		expect(rippleSig == sig, "Signature don't match");


		std::string strPrivateKey("ssQMHypYAPSPgniSyvJQccuL1dJUbXJWVgAPV5QcAuBVEWsZTVQwffsnwTY6Mivoy3NRSVR28ZaCW74F67VSq4VRC4zY1XR");
		expect(naNodePrivate.humanNodePrivate() == strPrivateKey, naNodePrivate.humanNodePrivate());
		
		expect(naNodePrivate.setNodePrivate(strPrivateKey),"couldn't create private node");
		expect(naNodePrivate.humanNodePrivate() == strPrivateKey, naNodePrivate.humanNodePrivate());
		naNodePrivate.sign(message, rippleSig);
		expect(rippleSig == sig, "Signature don't match");




		/*
		RippleAddress naNodePrivate = RippleAddress::createNodePrivate(naSeed);
		expect(naNodePrivate.humanNodePrivate() == "pnen77YEeUd4fFKG7iycBWcwKpTaeFRkW2WFostaATy1DSupwXe", naNodePrivate.humanNodePrivate());

		// Check node signing.
		Blob vucTextSrc = strCopy("Hello, nurse!");
		uint256 uHash = Serializer::getSHA512Half(vucTextSrc);
		Blob vucTextSig;

		naNodePrivate.signNodePrivate(uHash, vucTextSig);
		expect(naNodePublic.verifyNodePublic(uHash, vucTextSig, ECDSA::strict), "Verify failed.");
		*/


       
       
    }