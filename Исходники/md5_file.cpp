// make a random 32-char string
// (the MD5 of some quasi-random bits)
//
int make_random_string(char* out) {
    char buf[256];
#ifdef _WIN32
    HCRYPTPROV hCryptProv;
        
    if(! CryptAcquireContext(&hCryptProv, NULL, NULL, PROV_RSA_FULL, 0)) {
        return -1;
    }
    
    if(! CryptGenRandom(hCryptProv, (DWORD) 32, (BYTE *) buf)) {
        CryptReleaseContext(hCryptProv, 0);
        return -1;
    }
        
    CryptReleaseContext(hCryptProv, 0);
#elif defined ANDROID
    // /dev/random not available on Android, using stdlib function instead
    int i = rand();
    snprintf(buf, sizeof(buf), "%d", i);
#else
#ifndef _USING_FCGI_
    FILE* f = fopen("/dev/random", "r");
#else
    FILE* f = FCGI::fopen("/dev/random", "r");
#endif
    if (!f) {
        return -1;
    }
    size_t n = fread(buf, 32, 1, f);
    fclose(f);
    if (n != 1) return -1;
#endif
    md5_block((const unsigned char*)buf, 32, out);
    return 0;
}