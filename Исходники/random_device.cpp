  impl(const std::string & token) : provider(token) {
    char buffer[80];
    DWORD type;
    DWORD len;

    // Find the type of the provider
    for(DWORD i = 0; ; ++i) {
      len = sizeof(buffer);
      if(!CryptEnumProvidersA(i, NULL, 0, &type, buffer, &len)) {
        error("Could not find provider name");
      }
      if(buffer == provider) {
        break;
      }
    }

    if(!CryptAcquireContextA(&hProv, NULL, provider.c_str(), type,
        CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
      error("Could not acquire CSP context");
    }
  }