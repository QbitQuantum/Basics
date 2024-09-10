int main(void)
{   int     i, k, err, blocks, len, len2;
    double  a0, av, sig, td;
    unsigned char   buf1[BUFLEN];
    unsigned char   buf2[BUFLEN];
    unsigned char   iv1[AES_BLOCK_SIZE];
    unsigned char   iv2[AES_BLOCK_SIZE];
    unsigned char   key[32];
    f_ectx ecx1[1];
    f_dctx dcx1[1];
    aligned_auto(unsigned char, buf3, BUFLEN, 16);
    aligned_auto(unsigned char, iv3, AES_BLOCK_SIZE, 16);
    aligned_auto(f_ectx, ecx2, 1, 16);
    aligned_auto(f_dctx, dcx2, 1, 16);

#if defined( DLL_IMPORT ) && defined( DYNAMIC_LINK )
    HINSTANCE   h_dll;
#endif

#if defined( DUAL_CORE ) && defined( _WIN32 )
    // we need to constrain the process to one core in order to
    // obtain meaningful timing data
    HANDLE ph;
    DWORD_PTR afp;
    DWORD_PTR afs;
    ph = GetCurrentProcess();
    if(GetProcessAffinityMask(ph, &afp, &afs))
    {
        afp &= (GetCurrentProcessorNumber() + 1);
        if(!SetProcessAffinityMask(ph, afp))
        {
            printf("Couldn't set Process Affinity Mask\n\n"); return -1;
        }
    }
    else
    {
        printf("Couldn't get Process Affinity Mask\n\n"); return -1;
    }
#endif

#if defined( DLL_IMPORT ) && defined( DYNAMIC_LINK )
    if(!(h_dll = init_dll(&fn)))
        return -1;
#elif !defined(STATIC_TABLES)
    aes_init();
#endif

    if(f_talign(0,16) != EXIT_SUCCESS)
        return -1;

    printf("\nRun tests for the AES algorithm");
#if defined( DLL_IMPORT )
    printf(" (DLL Version)");
#endif
#if defined( __cplusplus )
    printf(" (CPP Version)");
#endif

    for(k = 128; k <= 256; k += 64)
    {
        printf("\n\n%03i Bit Keys", k);
#ifdef TEST_ECB
        err = 0;
        for(i = 0; i < 100; ++i)
        {
            block_rndfill(key, 2 * AES_BLOCK_SIZE);
            f_enc_key(ecx1, key, k);
            f_enc_key(ecx2, key, k);
            f_dec_key(dcx1, key, k);
            f_dec_key(dcx2, key, k);

            block_rndfill(buf1, BUFLEN);
            memcpy(buf2, buf1, BUFLEN);
            memcpy(buf3, buf1, BUFLEN);

            td = rand32() / (65536.0 * 65536.0);
            len = (unsigned int)(0.5 * BUFLEN * (1.0 + td));
            len = AES_BLOCK_SIZE * (len / AES_BLOCK_SIZE);

            ECBenc(buf2, len, ecx1);
            f_ecb_enc(ecx2, buf3, buf3, len);

            if(memcmp(buf2, buf3, len)) err |= 1;
            if((err & 1) && !(err & 256))
                printf("\nECB encryption FAILURE");

            ECBdec(buf2, len, dcx1);
            f_ecb_dec(dcx2, buf3, buf3, len);

            if(memcmp(buf1, buf2, len)) err |= 2;
            if(memcmp(buf1, buf3, len)) err |= 4;
            if((err & 4) && !(err & 512))
                printf("\nECB decryption FAILURE");
            if(err & 1)
                err |= 256;
            if(err & 4)
                err |= 512;
        }
        if(!err)
            printf("\nECB encrypt and decrypt of data correct");
#endif

#ifdef TEST_CBC
        err = 0;
        for(i = 0; i < 100; ++i)
        {
            block_rndfill(key, 2 * AES_BLOCK_SIZE);
            f_enc_key(ecx1, key, k);
            f_enc_key(ecx2, key, k);
            f_dec_key(dcx1, key, k);
            f_dec_key(dcx2, key, k);

            block_rndfill(iv1, AES_BLOCK_SIZE);
            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            block_rndfill(buf1, BUFLEN);
            memcpy(buf2, buf1, BUFLEN);
            memcpy(buf3, buf1, BUFLEN);

            td = rand32() / (65536.0 * 65536.0);
            len = (unsigned int)(0.5 * BUFLEN * (1.0 + td));
            len = AES_BLOCK_SIZE * (len / AES_BLOCK_SIZE);

            CBCenc(buf2, len, iv2, ecx1);
            f_cbc_enc(ecx2, buf3, buf3, len, iv3);

            if(memcmp(buf2, buf3, len)) err |= 1;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 2;
            if((err & 1) && !(err & 256))
                printf("\nCBC encryption FAILURE");

            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);
            CBCdec(buf2, len, iv2, dcx1);
            f_cbc_dec(dcx2, buf3, buf3, len, iv3);

            if(memcmp(buf1, buf2, len)) err |= 4;
            if(memcmp(buf1, buf3, len)) err |= 8;
            if(memcmp(buf2, buf3, len)) err |= 16;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 32;
            if((err & 16) && !(err & 512))
                printf("\nCBC decryption FAILURE");
            if(err & 1)
                err |= 256;
            if(err & 16)
                err |= 512;
        }
        if(!(err & ~(2 | 4 | 16 | 32)))
            printf("\nCBC encrypt and decrypt of data correct");
        if(err & (2 | 32))
        {
            printf(" (mismatch of final IV on ");
            if(err & 2)
                printf("encrypt");
            if((err & (2 | 32)) == 34)
                printf(" and ");
            if(err & 32)
                printf("decrypt");
            printf(")");
        }
#endif

#ifdef TEST_CFB
        err = 0;
        for(i = 0; i < 100; ++i)
        {
            block_rndfill(key, 2 * AES_BLOCK_SIZE);
            f_enc_key(ecx1, key, k);
            f_enc_key(ecx2, key, k);
            f_dec_key(dcx1, key, k);
            f_dec_key(dcx2, key, k);

            block_rndfill(iv1, AES_BLOCK_SIZE);
            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            block_rndfill(buf1, BUFLEN);
            memcpy(buf2, buf1, BUFLEN);
            memcpy(buf3, buf1, BUFLEN);

            f_info(ecx1) = 0;
            f_mode_reset(ecx2);
            td = rand32() / (65536.0 * 65536.0);
            len = (unsigned int)(0.5 * BUFLEN * (1.0 + td));
            td = rand32() / (65536.0 * 65536.0);
            len2 = (unsigned int)(td * len);
#ifdef WHOLE_BLOCKS
            len = AES_BLOCK_SIZE * (len / AES_BLOCK_SIZE);
            len2 = AES_BLOCK_SIZE * (len2 / AES_BLOCK_SIZE);
#endif
            f_cfb_enc(ecx2, buf3, buf3, len2, iv3);
            f_cfb_enc(ecx2, buf3 + len2, buf3 + len2, len - len2, iv3);

            CFBenc(buf2, len, iv2, ecx1);
            if(memcmp(buf2, buf3, len)) err |= 1;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 2;
            if((err & 1) && !(err & 256))
                printf("\nCFB encryption FAILURE");

            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            f_info(ecx1) = 0;
            f_mode_reset(ecx2);
            CFBdec(buf2, len, iv2, ecx1);
            td = rand32() / (65536.0 * 65536.0);
            len2 = (unsigned int)(td * len);
#ifdef WHOLE_BLOCKS
            len2 = AES_BLOCK_SIZE * (len2 / AES_BLOCK_SIZE);
#endif
            f_cfb_dec(ecx2, buf3, buf3, len2, iv3);
            f_cfb_dec(ecx2, buf3 + len2, buf3 + len2, len - len2, iv3);

            if(memcmp(buf1, buf2, len)) err |= 4;
            if(memcmp(buf1, buf3, len)) err |= 8;
            if(memcmp(buf2, buf3, len)) err |= 16;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 32;
            if((err & 16) && !(err & 512))
                printf("\nCFB decryption FAILURE");
            if(err & 1)
                err |= 256;
            if(err & 16)
                err |= 512;
        }
        if(!(err & ~(2 | 4 | 16 | 32)))
            printf("\nCFB encrypt and decrypt of data correct");
        if(err & (2 | 32))
        {
            printf(" (mismatch of final IV on ");
            if(err & 2)
                printf("encrypt");
            if((err & (2 | 32)) == 34)
                printf(" and ");
            if(err & 32)
                printf("decrypt");
            printf(")");
        }
#endif

#ifdef TEST_OFB
        err = 0;
        for(i = 0; i < 100; ++i)
        {
            block_rndfill(key, 2 * AES_BLOCK_SIZE);
            f_enc_key(ecx1, key, k);
            f_enc_key(ecx2, key, k);
            f_dec_key(dcx1, key, k);
            f_dec_key(dcx2, key, k);

            block_rndfill(iv1, AES_BLOCK_SIZE);
            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            block_rndfill(buf1, BUFLEN);
            memcpy(buf2, buf1, BUFLEN);
            memcpy(buf3, buf1, BUFLEN);

            f_info(ecx1) = 0;
            f_mode_reset(ecx2);
            td = rand32() / (65536.0 * 65536.0);
            len = (unsigned int)(0.5 * BUFLEN * (1.0 + td));
            td = rand32() / (65536.0 * 65536.0);
            len2 = (unsigned int)(td * len);
#ifdef WHOLE_BLOCKS
            len = AES_BLOCK_SIZE * (len / AES_BLOCK_SIZE);
            len2 = AES_BLOCK_SIZE * (len2 / AES_BLOCK_SIZE);
#endif
            f_ofb_cry(ecx2, buf3, buf3, len2, iv3);
            f_ofb_cry(ecx2, buf3 + len2, buf3 + len2, len - len2, iv3);

            OFBenc(buf2, len, iv2, ecx1);
            if(memcmp(buf2, buf3, len)) err |= 1;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 2;
            if((err & 1) && !(err & 256))
                printf("\nOFB encryption FAILURE");

            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            f_info(ecx1) = 0;
            f_mode_reset(ecx2);
            OFBdec(buf2, len, iv2, ecx1);
            td = rand32() / (65536.0 * 65536.0);
            len2 = (unsigned int)(td * len);
#ifdef WHOLE_BLOCKS
            len2 = AES_BLOCK_SIZE * (len2 / AES_BLOCK_SIZE);
#endif
            f_ofb_cry(ecx2, buf3, buf3, len2, iv3);
            f_ofb_cry(ecx2, buf3 + len2, buf3 + len2, len - len2, iv3);

            if(memcmp(buf1, buf2, len)) err |= 4;
            if(memcmp(buf1, buf3, len)) err |= 8;
            if(memcmp(buf2, buf3, len)) err |= 16;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 32;
            if((err & 16) && !(err & 512))
                printf("\nOFB decryption FAILURE");
            if(err & 1)
                err |= 256;
            if(err & 16)
                err |= 512;
        }
        if(!(err & ~(2 | 4 | 16 | 32)))
            printf("\nOFB encrypt and decrypt of data correct");
        if(err & (2 | 32))
        {
            printf(" (mismatch of final IV on ");
            if(err & 2)
                printf("encrypt");
            if((err & (2 | 32)) == 34)
                printf(" and ");
            if(err & 32)
                printf("decrypt");
            printf(")");
        }
#endif

#ifdef TEST_CTR
        err = 0;
        for(i = 0; i < 100; ++i)
        {
            block_rndfill(key, 2 * AES_BLOCK_SIZE);
            f_enc_key(ecx1, key, k);
            f_enc_key(ecx2, key, k);
            f_dec_key(dcx1, key, k);
            f_dec_key(dcx2, key, k);

            block_rndfill(iv1, AES_BLOCK_SIZE);
            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            block_rndfill(buf1, BUFLEN);
            memcpy(buf2, buf1, BUFLEN);
            memcpy(buf3, buf1, BUFLEN);

            f_info(ecx1) = 0;
            f_mode_reset(ecx2);
            td = rand32() / (65536.0 * 65536.0);
            len = (unsigned int)(0.5 * BUFLEN * (1.0 + td));
            td = rand32() / (65536.0 * 65536.0);
            len2 = (unsigned int)(td * len);
#ifdef WHOLE_BLOCKS
            len = AES_BLOCK_SIZE * (len / AES_BLOCK_SIZE);
            len2 = AES_BLOCK_SIZE * (len2 / AES_BLOCK_SIZE);
#endif
            f_ctr_cry(ecx2, buf3, buf3, len2, iv3, ctr_inc);
            f_ctr_cry(ecx2, buf3 + len2, buf3 + len2, len - len2, iv3, ctr_inc);

            CTRcry(buf2, len, iv2, ctr_inc, ecx1);
            if(memcmp(buf2, buf3, len)) err |= 1;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 2;
            if((err & 1) && !(err & 256))
                printf("\nCTR encryption FAILURE");

            memcpy(iv2, iv1, AES_BLOCK_SIZE);
            memcpy(iv3, iv1, AES_BLOCK_SIZE);

            f_info(ecx1) = 0;
            f_mode_reset(ecx2);
            td = rand32() / (65536.0 * 65536.0);
            len2 = (unsigned int)(td * len);
            CTRcry(buf2, len, iv2, ctr_inc, ecx1);
#ifdef WHOLE_BLOCKS
            len2 = AES_BLOCK_SIZE * (len2 / AES_BLOCK_SIZE);
#endif
            f_ctr_cry(ecx2, buf3, buf3, len2, iv3, ctr_inc);
            f_ctr_cry(ecx2, buf3 + len2, buf3 + len2, len - len2, iv3, ctr_inc);

            if(memcmp(buf1, buf2, len)) err |= 4;
            if(memcmp(buf1, buf3, len)) err |= 8;
            if(memcmp(buf2, buf3, len)) err |= 16;
            if(memcmp(iv2, iv3, AES_BLOCK_SIZE)) err |= 32;
            if((err & 16) && !(err & 512))
                printf("\nCTR decryption FAILURE");
            if(err & 1)
                err |= 256;
            if(err & 16)
                err |= 512;
        }
        if(!(err & ~(2 | 4 | 16 | 32)))
            printf("\nCTR encrypt and decrypt of data correct");
        if(err & (2 | 32))
        {
            printf(" (mismatch of final IV on ");
            if(err & 2)
                printf("encrypt");
            if((err & (2 | 32)) == 34)
                printf(" and ");
            if(err & 32)
                printf("decrypt");
            printf(")");
        }
#endif
    }

#if defined( USE_VIA_ACE_IF_PRESENT )
    if(VIA_ACE_AVAILABLE)
        printf("\n\nAES Timing (Cycles/Byte) with the VIA ACE Engine");
    else
#endif
    printf("\n\nAES Timing (Cycles/Byte)");
    printf("\nMode   Blocks:      1       10      100     1000");

#ifdef TEST_ECB
    printf("\necb encrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_ecb_enc(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }

    printf("\necb decrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_ecb_dec(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }
#endif

#ifdef TEST_CBC
    printf("\ncbc encrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_cbc_enc(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }

    printf("\ncbc decrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_cbc_dec(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }
#endif

#ifdef TEST_CFB
    printf("\ncfb encrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_cfb_enc(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }

    printf("\ncfb decrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_cfb_dec(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }
#endif

#ifdef TEST_OFB
    printf("\nofb encrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_ofb_enc(16, blocks, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }

#endif

#ifdef TEST_CTR
    printf("\nctr encrypt ");
    for(blocks = 1; blocks < 10000; blocks *= 10)
    {
        time_base(&a0, &sig);
        time_ctr_crypt(16, blocks, ctr_inc, &av, &sig);
        sig *= 100.0 / av;
        av = (int)(100.0 * (av - a0) / (16.0 * blocks)) / 100.0;
        sig = (int)(10 * sig) / 10.0;
        printf("%9.2f", av);
    }

#endif

#if defined( DLL_IMPORT ) && defined( DYNAMIC_LINK )
    if(h_dll) FreeLibrary(h_dll);
#endif
    printf("\n\n");
    return 0;
}