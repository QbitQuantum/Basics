// static
bool OTKeyring::Windows_RetrieveSecret(const OTString& strUser,
                                       OTPassword& thePassword,
                                       const std::string& str_display)
{
    OT_ASSERT(strUser.Exists());

    OTString strFoldername("win32_data"); // todo hardcoding.
    OTASCIIArmor ascFileContents;
    bool bLoaded = (strFoldername.Exists() &&
                    ascFileContents.LoadFromFile(strFoldername, strUser) &&
                    ascFileContents.Exists());
    if (!bLoaded) {
        otWarn << "%s: No cached ciphertext of master key loaded during "
                  "attempted retrieval. "
                  "(However, once one is available, it WILL be cached using "
                  "DPAPI.) \n";
        return false;
    }
    // Below this point, we know for sure the ciphertext of the master
    // key loaded, and exists.
    //
    const OTData theCipherblob(ascFileContents);
    //
    if (theCipherblob.IsEmpty()) {
        otErr << __FUNCTION__ << ": Error: OTData is empty after decoding "
                                 "OTASCIIArmor (that wasn't empty.)\n";
    }
    else {
        DATA_BLOB input;
        input.pbData = const_cast<BYTE*>(
            reinterpret_cast<const BYTE*>(theCipherblob.GetPayloadPointer()));
        input.cbData = static_cast<DWORD>(theCipherblob.GetSize());

        //      CRYPTPROTECT_PROMPTSTRUCT PromptStruct;
        //      ZeroMemory(&PromptStruct, sizeof(PromptStruct));
        //      PromptStruct.cbSize = sizeof(PromptStruct);
        //      PromptStruct.dwPromptFlags = CRYPTPROTECT_PROMPT_ON_PROTECT;
        //      PromptStruct.szPrompt = L"This is a user prompt.";

        //      LPWSTR pDescrOut = nullptr;

        DATA_BLOB output;
        BOOL result = CryptUnprotectData(&input, nullptr, // &pDescrOut
                                         nullptr,         // optional entropy
                                         nullptr,         // reserved
                                         nullptr,         //&PromptStruct
                                         0, &output);
        if (!result) {
            otErr << __FUNCTION__
                  << ": Error: Output of Win32 CryptUnprotectData was empty.\n";
        }
        else {
            thePassword.setMemory(reinterpret_cast<void*>(output.pbData),
                                  static_cast<uint32_t>(output.cbData));
            SecureZeroMemory(output.pbData, output.cbData);
            LocalFree(output.pbData);
            //          LocalFree(pDescrOut);
            return true;
        }
    }

    return false;
}