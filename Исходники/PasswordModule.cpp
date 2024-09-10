bool PasswordModule::GeneratePassHash(const wchar_t *userName, const wchar_t *passWord, std::string &passWordHash)
{
    if (wcsnlen(userName, 51) > 50 || wcsnlen(passWord, 51) > 50) {
        sLog.Error("PasswordModule", "username or password is simply to long");
        return false;
    }

    std::wstring salt(userName);

    Utils::Strings::trim(salt, true, true);     // comparable to the ".strip" function in python.
    Utils::Strings::toLowerCase(salt);

    int saltLen = (int)salt.size() * 2;
    uint8 * saltChar = (uint8*)&salt[0];

    std::wstring init(passWord);
    init += salt;

    int saltInitLen = (int)init.size() * 2;
    uint8 * saltInitChar = (uint8*)&init[0];

    #ifndef WIN32
        saltChar = wchar_tToUtf16(saltChar, salt.size());
        saltInitChar = wchar_tToUtf16(saltInitChar, init.size());
    #endif

    ShaModule::SHAobject shaObj;

    ShaModule::sha_init(&shaObj);
    ShaModule::sha_update(&shaObj, saltInitChar, saltInitLen);

    int daylySaltLen = SHA_DIGEST_SIZE + saltLen;

    // allocate buffer for the hashing, this way its only allocated once.
    uint8 * uDaylySalt = (uint8 *)malloc(daylySaltLen);   // first part of the data string
    uint8 * uDaylySaltPart = &uDaylySalt[SHA_DIGEST_SIZE];      // second part of the data string

    for (int i = 0; i < 1000; i++)
    {
        ShaModule::sha_digest(&shaObj, uDaylySalt);
        memcpy(uDaylySaltPart, saltChar, saltLen);

        ShaModule::sha_init(&shaObj);
        ShaModule::sha_update(&shaObj, uDaylySalt, daylySaltLen);
    }

    free(uDaylySalt);

    ShaModule::sha_final(mDigest, &shaObj);

    if (passWordHash.size() != 0)
        passWordHash = "";

    passWordHash.append((char*)mDigest, SHA_DIGEST_SIZE);

    return true;
}