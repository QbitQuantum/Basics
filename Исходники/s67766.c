int main(int argc, char *argv[])
{
        FILE *rsapub_key_fp;
        unsigned char *cam128_key, *cam128_iv;
        unsigned char *cipher_of_secret_text, *cipher_of_signed_key, *signed_key, *secret_text, *clobbered_key;
        EVP_PKEY *rsapub_key;
        unsigned char *rc4_40_key;
        const EVP_CIPHER *cam128_cfb8, *rc4_40;
        const EVP_MD *sha;
        EVP_MD_CTX sha_ctx;
        int cam128_cfb8_keylen, cam128_cfb8_ivlen, rc4_40_keylen, signed_key_size;
        int ret, count;
        long cipher_of_signed_key_size, clobbered_key_size, cipher_of_secret_text_size,  secret_text_size;

        // get the parameters for CAMELLIA128_cfb8
        cam128_cfb8 = EVP_camellia_128_cfb8();
        cam128_cfb8_keylen = EVP_CIPHER_key_length(cam128_cfb8);
        cam128_cfb8_ivlen = EVP_CIPHER_iv_length(cam128_cfb8);

        // get the parameters for RC4_40
        rc4_40 = EVP_rc4_40();
        rc4_40_keylen = EVP_CIPHER_key_length(rc4_40);

        // get the parameters for sha
        sha = EVP_sha();

        // read the s67766-clobbered-key.bin and store the key and iv for CAMELLIA128-cfb8
        cam128_key = malloc(cam128_cfb8_keylen);
        cam128_iv = malloc(cam128_cfb8_ivlen);

        clobbered_key_size = read_file(clobbered_key_file, &clobbered_key);
        if(clobbered_key_size != cam128_cfb8_keylen+cam128_cfb8_ivlen)
        {
                printf("reading file %s returned not enough Bytes: %ld, instead of: %d\n", clobbered_key_file, clobbered_key_size, cam128_cfb8_keylen+cam128_cfb8_ivlen);
                perror("");
        }
        memcpy(cam128_key, clobbered_key, cam128_cfb8_keylen);
        memcpy(cam128_iv, clobbered_key+cam128_cfb8_keylen, cam128_cfb8_ivlen);

        // read the s67766-cipher-of-signed-key.bin
        cipher_of_signed_key_size = read_file(cipher_of_signed_key_file, &cipher_of_signed_key);

        // read the public key from rsapub.pem
        rsapub_key_fp = fopen(rsapub_key_file, "r");
        if (!rsapub_key_fp)
        {
                printf("opening file %s returned error\n", rsapub_key_file);
                perror("");
        }

        rsapub_key = PEM_read_PUBKEY(rsapub_key_fp, NULL, NULL, NULL);
        if (!rsapub_key)
        {
                printf("PEM_read_PUBKEY returned error for RSA\n");
        }

        if(fclose(rsapub_key_fp) != 0)
        {
                printf("closing file %s returned error\n", rsapub_key_file);
                perror("");
        }

        // restore the clobbered key with bruteforce
        signed_key = malloc(cipher_of_signed_key_size);
        for(count = 0; count<=255; count++)
        {
                memset(cam128_key, count, 1);

                //decrypt the cipher with guessed key
                signed_key_size =  decrypt(cam128_cfb8, &signed_key, cipher_of_signed_key, cipher_of_signed_key_size, cam128_key, cam128_iv);
                if(signed_key_size==-1)
                {
                        return -1;
                }

                if(EVP_VerifyInit(&sha_ctx, sha) == 0)
                {
                        printf("EVP_VerifyInit returned error for SHA\n");
                }
                if(EVP_VerifyUpdate(&sha_ctx, signed_key, rc4_40_keylen) == 0)
                {
                        printf("EVP_VerifyUpdate returned error for SHA\n");
                }
                ret = EVP_VerifyFinal(&sha_ctx, signed_key+rc4_40_keylen, signed_key_size-rc4_40_keylen, rsapub_key);
                switch(ret)
                {
                        case -1:
                                printf("EVP_VerifyFinal returned error for SHA\n");
                                break;
                        case 0:
                                break;
                        case 1:
                                count = 255;
                                break;
                }
        }
        // extract the key for RC-4 40
        rc4_40_key = malloc(rc4_40_keylen);
        memcpy(rc4_40_key, signed_key, rc4_40_keylen);

        // read the s67766-cipher-of-secret-text.bin
        cipher_of_secret_text_size = read_file(cipher_of_secret_text_file, &cipher_of_secret_text);

        // decrypt s67766-cipher-of-secret-text.bin
        secret_text = malloc(cipher_of_secret_text_size);
        secret_text_size = 0;

        secret_text_size =  decrypt(rc4_40, &secret_text, cipher_of_secret_text, cipher_of_secret_text_size, rc4_40_key, NULL);

        // write the s67766-plain.bin
        if(write_file(plain_file, secret_text, secret_text_size)==-1)
        {
                return -1;
        }

        return 0;
}