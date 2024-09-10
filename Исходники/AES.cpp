int aes::AES_do_decrypt_from_file(char *infile, char *outfile, unsigned long *CifKey)
{
	BYTE* in = new BYTE[4*Nb];
        printf("Decoding...\n");
        GenPowerTab();
        GenSubBytesTab();

        FILE* stream_in;
        FILE* stream_out;
        if ( !(stream_in = fopen(infile, "rb")))
        {
            printf("File in: %s cannot be read", infile);
            return -1;
        }
        if ( !(stream_out = fopen(outfile, "wb")) )
        {
            printf("File out: %s cannot be read", outfile);
            return -1;
        }

        fpos_t flen;
        //   
        fseek(stream_in, 0, SEEK_END);
        fgetpos(stream_in, &flen); 
        unsigned long rlen = file_len(flen);
        //   
        fseek(stream_in, 0, SEEK_SET);

        WORD ExpKey[Nb*(Nr+1)]; 
        //WORD CifKey[Nk] = { 0x00010203,    0x04050607,
        //    0x08090a0b,    0x0c0d0e0f};
        KeyExpansion(CifKey, ExpKey);

        while(rlen > 0 && !feof(stream_in))
        {  
            unsigned long len =
                (unsigned long)fread(in, 1, 4*Nb, stream_in);
            if (rlen < 4*Nb)
                for (int i = rlen; i < 4*Nb; i++)
                    in[i] = 0;
            rlen -= len;
            //if (len != 4*Nb)

            #ifdef LOGit
            printf("\nNew block\n");
            for(int i=0; i<4; i++)
            {
                printf("%02x %02x %02x %02x\n", in[i], in[4+i],
                    in[8+i], in[12+i]);
            }
            #endif

            AddRoundKey((WORD*)in, &ExpKey[4*Nr]);
            InvCipher((WORD*)in, ExpKey);

            if (rlen == 1)
            {
                BYTE* out = new BYTE[1];
                fread(out, sizeof(BYTE), 1, stream_in);
                len = out[0];
                rlen = 0;
            }

            int nWritten = fwrite(in, sizeof(BYTE), len, stream_out);
        }

        fclose(stream_out);
}