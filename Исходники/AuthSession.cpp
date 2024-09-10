// Logon Proof command handler
bool AuthSession::HandleLogonProof()
{
    TC_LOG_DEBUG("server.authserver", "Entering _HandleLogonProof");
    _status = STATUS_CLOSED;

    // Read the packet
    sAuthLogonProof_C *logonProof = reinterpret_cast<sAuthLogonProof_C*>(GetReadBuffer().GetReadPointer());

    // If the client has no valid version
    if (_expversion == NO_VALID_EXP_FLAG)
    {
        // Check if we have the appropriate patch on the disk
        TC_LOG_DEBUG("network", "Client with invalid version, patching is not implemented");
        return false;
    }

    // Continue the SRP6 calculation based on data received from the client
    BigNumber A;

    A.SetBinary(logonProof->A, 32);

    // SRP safeguard: abort if A == 0
    if ((A % N).IsZero())
        return false;

    SHA1Hash sha;
    sha.UpdateBigNumbers(&A, &B, nullptr);
    sha.Finalize();
    BigNumber u;
    u.SetBinary(sha.GetDigest(), 20);
    BigNumber S = (A * (v.ModExp(u, N))).ModExp(b, N);

    uint8 t[32];
    uint8 t1[16];
    uint8 vK[40];
    memcpy(t, S.AsByteArray(32).get(), 32);

    for (int i = 0; i < 16; ++i)
        t1[i] = t[i * 2];

    sha.Initialize();
    sha.UpdateData(t1, 16);
    sha.Finalize();

    for (int i = 0; i < 20; ++i)
        vK[i * 2] = sha.GetDigest()[i];

    for (int i = 0; i < 16; ++i)
        t1[i] = t[i * 2 + 1];

    sha.Initialize();
    sha.UpdateData(t1, 16);
    sha.Finalize();

    for (int i = 0; i < 20; ++i)
        vK[i * 2 + 1] = sha.GetDigest()[i];

    K.SetBinary(vK, 40);

    uint8 hash[20];

    sha.Initialize();
    sha.UpdateBigNumbers(&N, nullptr);
    sha.Finalize();
    memcpy(hash, sha.GetDigest(), 20);
    sha.Initialize();
    sha.UpdateBigNumbers(&g, nullptr);
    sha.Finalize();

    for (int i = 0; i < 20; ++i)
        hash[i] ^= sha.GetDigest()[i];

    BigNumber t3;
    t3.SetBinary(hash, 20);

    sha.Initialize();
    sha.UpdateData(_accountInfo.Login);
    sha.Finalize();
    uint8 t4[SHA_DIGEST_LENGTH];
    memcpy(t4, sha.GetDigest(), SHA_DIGEST_LENGTH);

    sha.Initialize();
    sha.UpdateBigNumbers(&t3, nullptr);
    sha.UpdateData(t4, SHA_DIGEST_LENGTH);
    sha.UpdateBigNumbers(&s, &A, &B, &K, nullptr);
    sha.Finalize();
    BigNumber M;
    M.SetBinary(sha.GetDigest(), sha.GetLength());

    // Check if SRP6 results match (password is correct), else send an error
    if (!memcmp(M.AsByteArray(sha.GetLength()).get(), logonProof->M1, 20))
    {
        // Check auth token
        if ((logonProof->securityFlags & 0x04) || !_tokenKey.empty())
        {
            uint8 size = *(GetReadBuffer().GetReadPointer() + sizeof(sAuthLogonProof_C));
            std::string token(reinterpret_cast<char*>(GetReadBuffer().GetReadPointer() + sizeof(sAuthLogonProof_C) + sizeof(size)), size);
            GetReadBuffer().ReadCompleted(sizeof(size) + size);
            uint32 validToken = TOTP::GenerateToken(_tokenKey.c_str());
            _tokenKey.clear();
            uint32 incomingToken = atoi(token.c_str());
            if (validToken != incomingToken)
            {
                ByteBuffer packet;
                packet << uint8(AUTH_LOGON_PROOF);
                packet << uint8(WOW_FAIL_UNKNOWN_ACCOUNT);
                packet << uint8(3);
                packet << uint8(0);
                SendPacket(packet);
                return true;
            }
        }

        TC_LOG_DEBUG("server.authserver", "'%s:%d' User '%s' successfully authenticated", GetRemoteIpAddress().to_string().c_str(), GetRemotePort(), _accountInfo.Login.c_str());

        // Update the sessionkey, last_ip, last login time and reset number of failed logins in the account table for this account
        // No SQL injection (escaped user name) and IP address as received by socket

        PreparedStatement *stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_LOGONPROOF);
        stmt->setString(0, K.AsHexStr());
        stmt->setString(1, GetRemoteIpAddress().to_string());
        stmt->setUInt32(2, GetLocaleByName(_localizationName));
        stmt->setString(3, _os);
        stmt->setString(4, _accountInfo.Login);
        LoginDatabase.DirectExecute(stmt);

        // Finish SRP6 and send the final result to the client
        sha.Initialize();
        sha.UpdateBigNumbers(&A, &M, &K, nullptr);
        sha.Finalize();

        ByteBuffer packet;
        if (_expversion & POST_BC_EXP_FLAG)                 // 2.x and 3.x clients
        {
            sAuthLogonProof_S proof;
            memcpy(proof.M2, sha.GetDigest(), 20);
            proof.cmd = AUTH_LOGON_PROOF;
            proof.error = 0;
            proof.AccountFlags = 0x00800000;    // 0x01 = GM, 0x08 = Trial, 0x00800000 = Pro pass (arena tournament)
            proof.SurveyId = 0;
            proof.unk3 = 0;

            packet.resize(sizeof(proof));
            std::memcpy(packet.contents(), &proof, sizeof(proof));
        }
        else
        {
            sAuthLogonProof_S_Old proof;
            memcpy(proof.M2, sha.GetDigest(), 20);
            proof.cmd = AUTH_LOGON_PROOF;
            proof.error = 0;
            proof.unk2 = 0x00;

            packet.resize(sizeof(proof));
            std::memcpy(packet.contents(), &proof, sizeof(proof));
        }

        SendPacket(packet);
        _status = STATUS_AUTHED;
    }
    else
    {
        ByteBuffer packet;
        packet << uint8(AUTH_LOGON_PROOF);
        packet << uint8(WOW_FAIL_UNKNOWN_ACCOUNT);
        packet << uint8(3);
        packet << uint8(0);
        SendPacket(packet);

        TC_LOG_INFO("server.authserver.hack", "'%s:%d' [AuthChallenge] account %s tried to login with invalid password!",
            GetRemoteIpAddress().to_string().c_str(), GetRemotePort(), _accountInfo.Login.c_str());

        uint32 MaxWrongPassCount = sConfigMgr->GetIntDefault("WrongPass.MaxCount", 0);

        // We can not include the failed account login hook. However, this is a workaround to still log this.
        if (sConfigMgr->GetBoolDefault("WrongPass.Logging", false))
        {
            PreparedStatement* logstmt = LoginDatabase.GetPreparedStatement(LOGIN_INS_FALP_IP_LOGGING);
            logstmt->setUInt32(0, _accountInfo.Id);
            logstmt->setString(1, GetRemoteIpAddress().to_string());
            logstmt->setString(2, "Logged on failed AccountLogin due wrong password");

            LoginDatabase.Execute(logstmt);
        }

        if (MaxWrongPassCount > 0)
        {
            //Increment number of failed logins by one and if it reaches the limit temporarily ban that account or IP
            PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_FAILEDLOGINS);
            stmt->setString(0, _accountInfo.Login);
            LoginDatabase.Execute(stmt);

            if (++_accountInfo.FailedLogins >= MaxWrongPassCount)
            {
                uint32 WrongPassBanTime = sConfigMgr->GetIntDefault("WrongPass.BanTime", 600);
                bool WrongPassBanType = sConfigMgr->GetBoolDefault("WrongPass.BanType", false);

                if (WrongPassBanType)
                {
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_INS_ACCOUNT_AUTO_BANNED);
                    stmt->setUInt32(0, _accountInfo.Id);
                    stmt->setUInt32(1, WrongPassBanTime);
                    LoginDatabase.Execute(stmt);

                    TC_LOG_DEBUG("server.authserver", "'%s:%d' [AuthChallenge] account %s got banned for '%u' seconds because it failed to authenticate '%u' times",
                        GetRemoteIpAddress().to_string().c_str(), GetRemotePort(), _accountInfo.Login.c_str(), WrongPassBanTime, _accountInfo.FailedLogins);
                }
                else
                {
                    stmt = LoginDatabase.GetPreparedStatement(LOGIN_INS_IP_AUTO_BANNED);
                    stmt->setString(0, GetRemoteIpAddress().to_string());
                    stmt->setUInt32(1, WrongPassBanTime);
                    LoginDatabase.Execute(stmt);

                    TC_LOG_DEBUG("server.authserver", "'%s:%d' [AuthChallenge] IP got banned for '%u' seconds because account %s failed to authenticate '%u' times",
                        GetRemoteIpAddress().to_string().c_str(), GetRemotePort(), WrongPassBanTime, _accountInfo.Login.c_str(), _accountInfo.FailedLogins);
                }
            }
        }
    }

    return true;
}