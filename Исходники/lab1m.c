int main (int argc, char *argv[])
{
  if (argc != 6) {
    fputs("Usage: lab1 [rc2|rc4|rc4e|des|3des112|3des|aes128|aes192|aes256] "
          "[enc|dec] <input file> <output file> <key>", stderr);
    return -1;
  }

  enum mode mod;
  if (strncmp(argv[2], "enc", 3) == 0) {
    mod = ENC;
  } else if (strncmp(argv[2], "dec", 3) == 0) {
    mod = DEC;
  } else {
    fprintf(stderr, "Wrong encryption mode: \"%s\".", argv[2]);
    return -1;
  }

  HANDLE inf = 0;
  HANDLE inmmf = 0;
  PBYTE indata = NULL;
  HANDLE outf = 0;
  HANDLE outmmf = 0;
  PBYTE outdata = NULL;
  LARGE_INTEGER insz = {.QuadPart = 0};
  LARGE_INTEGER outsz = {.QuadPart = 0};
  unsigned char err = 1;


  inf = CreateFileA(argv[3], GENERIC_READ, 0, NULL, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL, NULL);
  inmmf = CreateFileMappingA(inf, NULL, PAGE_READONLY, 0, 0, NULL);
  if (inmmf == NULL) {
    fprintf(stderr, "Can't open memory mapped file. Error code: %lu\n",
            GetLastError());
    goto err;
  }
  indata = (PBYTE)MapViewOfFile(inmmf, FILE_MAP_READ, 0, 0, 0);
  if (indata == NULL) {
    fprintf(stderr, "Can't map view of file. Error code: %lu\n", GetLastError());
    goto err;
  }

  GetFileSizeEx(inf, &insz);
  outsz.QuadPart = (insz.QuadPart / 8 + 2) * 8;

  outf = CreateFileA(argv[4], GENERIC_READ | GENERIC_WRITE, 0, NULL,
                     CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
  outmmf = CreateFileMappingA(outf, NULL, PAGE_READWRITE,
                              outsz.HighPart, outsz.LowPart, NULL);
  if (outmmf == NULL) {
    fprintf(stderr, "Can't open memory mapped file. Error code: %lu\n",
            GetLastError());
    goto err;
  }

  outdata = (PBYTE)MapViewOfFile(outmmf, FILE_MAP_WRITE, 0, 0, 0);
  if (outdata == NULL) {
    fprintf(stderr, "Can't map view of file. Error code: %lu\n", GetLastError());
    goto err;
  }

  // Crypto stuff
  BOOL res;
  HCRYPTPROV prov;

  DWORD prov_type = PROV_RSA_AES;
  LPCTSTR prov_id = MS_ENH_RSA_AES_PROV; // MS_ENHANCED_PROV
  ALG_ID calg_id;
  if (strncmp(argv[1], "rc2", 3) == 0) {
    calg_id = CALG_RC2;
  } else if (strncmp(argv[1], "rc4e", 4) == 0) {
    calg_id = CALG_RC4;
  } else if (strncmp(argv[1], "rc4", 3) == 0) {
    prov_type = PROV_RSA_FULL;
    prov_id = MS_DEF_PROV;
    calg_id = CALG_RC4;
  } else if (strncmp(argv[1], "des", 3) == 0) {
    calg_id = CALG_DES;
  } else if (strncmp(argv[1], "3des112", 7) == 0) {
    calg_id = CALG_3DES_112;
  } else if (strncmp(argv[1], "3des", 4) == 0) {
    calg_id = CALG_3DES;
  } else if (strncmp(argv[1], "aes128", 6) == 0) {
    calg_id = CALG_AES_128;
  } else if (strncmp(argv[1], "aes192", 6) == 0) {
    calg_id = CALG_AES_192;
  } else if (strncmp(argv[1], "aes256", 6) == 0) {
    calg_id = CALG_AES_256;
  } else {
    fprintf(stderr, "Wrong cryptographic algorythm: \"%s\".", argv[1]);
    goto err;
  }

  if (!CryptAcquireContext(&prov, 0, prov_id, prov_type,
                           CRYPT_VERIFYCONTEXT)) {
    fputs("Cannot acquire crypt context.\n", stderr);
    goto err;
  }

  HCRYPTKEY key = generateKey(prov, calg_id, argv[5]);
  crash_if(key == 0, "Cannot make a key.");

  for (LARGE_INTEGER i = {.QuadPart = 0}; i.QuadPart < insz.QuadPart;
       (i.QuadPart) += buf_size) {

    unsigned char buf[buf_size + block_size];
    DWORD len = buf_size;
    void *inp = indata + i.QuadPart,
         *outp = outdata + i.QuadPart;
    BOOL final = insz.QuadPart - i.QuadPart <= buf_size;

    if (final) {
      len = insz.QuadPart - i.QuadPart;
    }

    memcpy(buf, inp, len);
    if (mod == ENC) {
      res = CryptEncrypt(key, 0, final, 0, buf, &len, buf_size + block_size);
    } else {
      res = CryptDecrypt(key, 0, final, 0, buf, &len);
    }

    if (res) {
      memcpy(outp, buf, len);
      if (final) {
        outsz.QuadPart = i.QuadPart + len;
      }
    } else {
      fprintf(stderr, "Can't crypt the block 0x%lx. Error code: %lu\n",
              i.QuadPart, GetLastError());
      goto err;
    }
  }

  CryptDestroyKey(key);
  CryptReleaseContext(prov,0);

  err = 0;

err:
  // Freeing resources.
  apply_not_null(indata, UnmapViewOfFile);
  apply_not_null(inmmf, CloseHandle);
  apply_not_null(inf, CloseHandle);

  apply_not_null(outdata, UnmapViewOfFile);
  apply_not_null(outmmf, CloseHandle);

  if (outf) {
    SetFilePointer(outf, outsz.LowPart, &(outsz.HighPart), FILE_BEGIN);
    SetEndOfFile(outf);
  }

  apply_not_null(outf, CloseHandle);

  if (err)
    return -1;
  else
    return 0;
}