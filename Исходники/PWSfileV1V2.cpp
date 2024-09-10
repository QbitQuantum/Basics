int PWSfileV1V2::Open(const StringX &passkey)
{
  int status = SUCCESS;

  ASSERT(m_curversion == V17 || m_curversion == V20);

  m_passkey = passkey;
  FOpen();
  if (m_fd == NULL)
    return CANT_OPEN_FILE;

  LPCTSTR passstr = m_passkey.c_str();
  size_t passLen = passkey.length();
  unsigned char *pstr;

#ifdef UNICODE
  size_t pstr_len = 3 * passLen;
  pstr = new unsigned char[pstr_len];
  size_t len = pws_os::wcstombs(reinterpret_cast<char *>(pstr), 3 * passLen, passstr, passLen, false);
  ASSERT(len != 0);
  // hack around OS-dependent semantics - too widespread to fix systematically :-(
  pstr[len < pstr_len ? len : pstr_len - 1] = '\0';
  passLen = strlen(reinterpret_cast<const char *>(pstr));
#else
  pstr = reinterpret_cast<unsigned char *>(passstr);
#endif

  if (m_rw == Write) {
    // Following used to verify passkey against file's passkey
    unsigned char randstuff[StuffSize];
    unsigned char randhash[20];   // HashSize

    PWSrand::GetInstance()->GetRandomData( randstuff, 8 );
    randstuff[8] = randstuff[9] = TCHAR('\0');
    GenRandhash(m_passkey, randstuff, randhash);

    SAFE_FWRITE(randstuff, 1, 8, m_fd);
    SAFE_FWRITE(randhash, 1, 20, m_fd);

    PWSrand::GetInstance()->GetRandomData(m_salt, SaltLength);

    SAFE_FWRITE(m_salt, 1, SaltLength, m_fd);

    PWSrand::GetInstance()->GetRandomData( m_ipthing, 8);
    SAFE_FWRITE(m_ipthing, 1, 8, m_fd);

    m_fish = BlowFish::MakeBlowFish(pstr, reinterpret_cast<int &>(passLen),
                                    m_salt, SaltLength);
    if (m_curversion == V20) {
      status = WriteV2Header();
    }
  } else { // open for read
    status = CheckPasskey(m_filename, m_passkey, m_fd);
    if (status != SUCCESS) {
#ifdef UNICODE
      trashMemory(pstr, pstr_len);
      delete[] pstr;
#endif
      Close();
      return status;
    }
    fread(m_salt, 1, SaltLength, m_fd);
    fread(m_ipthing, 1, 8, m_fd);

    m_fish = BlowFish::MakeBlowFish(pstr, reinterpret_cast<int &>(passLen),
                                    m_salt, SaltLength);
    if (m_curversion == V20)
      status = ReadV2Header();
  } // read mode
 exit:
  if (status != SUCCESS)
    Close();
#ifdef UNICODE
  trashMemory(pstr, pstr_len);
  delete[] pstr;
#endif
  return status;
}