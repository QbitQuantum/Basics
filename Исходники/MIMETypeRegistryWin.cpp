String MIMETypeRegistry::getPreferredExtensionForMIMEType(const String& type)
{
    String path = "MIME\\Database\\Content Type\\" + type;
    WCHAR extStr[MAX_PATH];
    DWORD extStrLen = sizeof(extStr);
    DWORD keyType;

    HRESULT result = SHGetValueW(HKEY_CLASSES_ROOT, path.charactersWithNullTermination(), L"Extension", &keyType, (LPVOID)extStr, &extStrLen);

    if (result == ERROR_SUCCESS && keyType == REG_SZ) 
        return String(extStr + 1, extStrLen / sizeof(extStr[0]) - 2);

    return String();
}