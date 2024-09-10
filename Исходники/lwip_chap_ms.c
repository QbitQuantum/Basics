static void ChallengeResponse(const u_char *challenge,
		  const u_char PasswordHash[MD4_SIGNATURE_SIZE],
		  u_char response[24]) {
    u_char    ZPasswordHash[21];
    lwip_des_context des;
    u_char des_key[8];

    BZERO(ZPasswordHash, sizeof(ZPasswordHash));
    MEMCPY(ZPasswordHash, PasswordHash, MD4_SIGNATURE_SIZE);

#if 0
    dbglog("ChallengeResponse - ZPasswordHash %.*B",
	   sizeof(ZPasswordHash), ZPasswordHash);
#endif

    pppcrypt_56_to_64_bit_key(ZPasswordHash + 0, des_key);
    lwip_des_init(&des);
    lwip_des_setkey_enc(&des, des_key);
    lwip_des_crypt_ecb(&des, challenge, response +0);
    lwip_des_free(&des);

    pppcrypt_56_to_64_bit_key(ZPasswordHash + 7, des_key);
    lwip_des_init(&des);
    lwip_des_setkey_enc(&des, des_key);
    lwip_des_crypt_ecb(&des, challenge, response +8);
    lwip_des_free(&des);

    pppcrypt_56_to_64_bit_key(ZPasswordHash + 14, des_key);
    lwip_des_init(&des);
    lwip_des_setkey_enc(&des, des_key);
    lwip_des_crypt_ecb(&des, challenge, response +16);
    lwip_des_free(&des);

#if 0
    dbglog("ChallengeResponse - response %.24B", response);
#endif
}