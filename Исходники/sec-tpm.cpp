bool
SecTpm::getImpExpPassWord(std::string& password, const std::string& prompt)
{
  bool isInitialized = false;

#ifdef NDN_CXX_HAVE_GETPASS
  char* pw0 = nullptr;

  pw0 = getpass(prompt.c_str());
  if (pw0 == nullptr)
    return false;
  std::string password1 = pw0;
  memset(pw0, 0, strlen(pw0));

  pw0 = getpass("Confirm:");
  if (pw0 == nullptr) {
    std::fill(password1.begin(), password1.end(), 0);
    return false;
  }

  if (password1.compare(pw0) == 0) {
    isInitialized = true;
    password.swap(password1);
  }

  std::fill(password1.begin(), password1.end(), 0);
  memset(pw0, 0, strlen(pw0));

  if (password.empty())
    return false;

#endif // NDN_CXX_HAVE_GETPASS

  return isInitialized;
}