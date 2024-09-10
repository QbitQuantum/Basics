void AuthSocket::HandleProof()
{
	if(readBuffer.GetSize() < sizeof(sAuthLogonProof_C))
	{
		LOG_ERROR("[AuthLogonProof] The packet received is larger than expected, refusing to handle it!");
		return ;
	}

	// patch
	if(m_patch && !m_account)
	{
		//RemoveReadBufferBytes(75,false);
		readBuffer.Remove(75);
		LOG_DEBUG("[AuthLogonProof] Intitiating PatchJob");
		uint8 bytes[2] = {0x01, 0x0a};
		Send(bytes, 2);
		PatchMgr::getSingleton().InitiatePatch(m_patch, this);
		return;
	}

	if(!m_account)
		return;

	LOG_DEBUG("[AuthLogonProof] Interleaving and checking proof...");

	sAuthLogonProof_C lp;
	//Read(sizeof(sAuthLogonProof_C), (uint8*)&lp);
	readBuffer.Read(&lp, sizeof(sAuthLogonProof_C));


	////////////////////////////////////////////////////// SRP6 ///////////////////////////////////////////////
	//Now comes the famous secret Xi Chi fraternity handshake ( http://www.youtube.com/watch?v=jJSYBoI2si0 ),
	//generating a session key
	//
	// A = g^a % N
	// u = SHA1( A | B )
	//
	//

	BigNumber A;
	A.SetBinary(lp.A, 32);

	Sha1Hash sha;
	sha.UpdateBigNumbers(&A, &B, 0);
	sha.Finalize();

	BigNumber u;
	u.SetBinary(sha.GetDigest(), 20);

	// S session key key, S = ( A * v^u ) ^ b
	BigNumber S = (A * (v.ModExp(u, N))).ModExp(b, N);


	// Generate M
	// M = H(H(N) xor H(g), H(I), s, A, B, K) according to http://srp.stanford.edu/design.html
	uint8 t[32];
	uint8 t1[16];
	uint8 vK[40];
	memcpy(t, S.AsByteArray(), 32);
	for(int i = 0; i < 16; i++)
	{
		t1[i] = t[i * 2];
	}
	sha.Initialize();
	sha.UpdateData(t1, 16);
	sha.Finalize();
	for(int i = 0; i < 20; i++)
	{
		vK[i * 2] = sha.GetDigest()[i];
	}
	for(int i = 0; i < 16; i++)
	{
		t1[i] = t[i * 2 + 1];
	}
	sha.Initialize();
	sha.UpdateData(t1, 16);
	sha.Finalize();
	for(int i = 0; i < 20; i++)
	{
		vK[i * 2 + 1] = sha.GetDigest()[i];
	}
	m_sessionkey.SetBinary(vK, 40);

	uint8 hash[20];

	sha.Initialize();
	sha.UpdateBigNumbers(&N, NULL);
	sha.Finalize();
	memcpy(hash, sha.GetDigest(), 20);
	sha.Initialize();
	sha.UpdateBigNumbers(&g, NULL);
	sha.Finalize();
	for(int i = 0; i < 20; i++)
	{
		hash[i] ^= sha.GetDigest()[i];
	}
	BigNumber t3;
	t3.SetBinary(hash, 20);

	sha.Initialize();
	sha.UpdateData((const uint8*)m_account->UsernamePtr->c_str(), (int)m_account->UsernamePtr->size());
	sha.Finalize();

	BigNumber t4;
	t4.SetBinary(sha.GetDigest(), 20);

	sha.Initialize();
	sha.UpdateBigNumbers(&t3, &t4, &s, &A, &B, &m_sessionkey, NULL);
	sha.Finalize();

	BigNumber M;
	M.SetBinary(sha.GetDigest(), 20);

	// Compare the M value the client sent us to the one we generated, this proves we both have the same values
	// which proves we have the same username-password pairs
	if(memcmp(lp.M1, M.AsByteArray(), 20) != 0)
	{
		// Authentication failed.
		//SendProofError(4, 0);
		SendChallengeError(CE_NO_ACCOUNT);
		LOG_DEBUG("[AuthLogonProof] M values don't match. ( Either invalid password or the logon server is bugged. )");
		return;
	}

	// Store sessionkey
	m_account->SetSessionKey(m_sessionkey.AsByteArray());

	// let the client know
	sha.Initialize();
	sha.UpdateBigNumbers(&A, &M, &m_sessionkey, 0);
	sha.Finalize();

	SendProofError(0, sha.GetDigest());
	LOG_DEBUG("[AuthLogonProof] Authentication Success.");

	// we're authenticated now :)
	m_authenticated = true;

	// Don't update when IP banned, but update anyway if it's an account ban
	sLogonSQL->Execute("UPDATE accounts SET lastlogin=NOW(), lastip='%s' WHERE acct=%u;", GetRemoteIP().c_str(), m_account->AccountId);
}