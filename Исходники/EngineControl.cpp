    // バイトコードがメモリにロードされた直後のコールバック。
    // 対応するDLLがあればロードする
    static void cb4dll(const char* hybPath)
    {
        int len = HMD_STRLEN(hybPath);
        char* dllPath = (char*)HMD_ALLOCA(len + sizeof(dll_prefix)+sizeof(dll_ext));
        char* q = dllPath;
        char* q2 = q;

        const unsigned char* p = _mbsrchr((const unsigned char*)hybPath, PATH_DELIM);
        if (p == NULL) {
            p = (const unsigned char*)hybPath;
        } else {
            p += 1;
            size_t lp = p - (const unsigned char*)hybPath;
            memcpy(q, hybPath, lp);
            q += lp;
            q2 = q;
        }
        // pはhybPathのファイル名部分の先頭アドレス
        const unsigned char* p2 = _mbsstr((const unsigned char*)p, (const unsigned char*)".hyb");
        if ((p2 <= p) || (p2 >= (const unsigned char*)hybPath + len)) {
            p2 = (const unsigned char*)hybPath + len;
        }
        // p2は拡張子を抜いたファイル名部分の末尾アドレス

        memcpy(q, dll_prefix, sizeof(dll_prefix));
        q += sizeof(dll_prefix) - 1;
        size_t lp2 = p2 - p;
        memcpy(q, p, lp2);
        q += lp2;
        memcpy(q, dll_ext, sizeof(dll_ext));
        q += sizeof(dll_ext) - 1;
        *q = '\0';

#ifdef VERBOSE_LOAD_DLL
        HMD_PRINTF("try load dll: %s\n", dllPath);
#endif
		HMODULE hmod = LoadLibraryMB(dllPath);    // dllロード
#ifdef VERBOSE_LOAD_DLL
        if (hmod == NULL) printLastError();
#endif        
        if (hmod == NULL && q2 != dllPath) {
            // パス抜きのファイル名だけでロードしてみる
#ifdef VERBOSE_LOAD_DLL
            HMD_PRINTF("try load dll: %s\n", q2);
#endif        
            hmod = LoadLibraryMB(q2);
#ifdef VERBOSE_LOAD_DLL
            if (hmod == NULL) printLastError();
#endif        
        }

        if (hmod != NULL) {
            dllHandleArr.add(hmod);
#ifdef VERBOSE_LOAD_DLL
            HMD_PRINTF("DLL '%s' loaded.\n", q2);
#endif
        }
    }