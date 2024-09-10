  bool AddSid(LPCWSTR sid_str)
  {
    if (_wcsicmp(sid_str, L"CU") == 0)
    {
      return AddSid(GetCurrentUserSid().c_str());
    }
    else
    {
      PSID p = nullptr;

      if (!::ConvertStringSidToSid(sid_str, &p))
      {
        return false;
      }

      std::unique_ptr<void, LocalFreeDeleter> buf(p);

      SID_IDENTIFIER_AUTHORITY il_id_auth = { { 0,0,0,0,0,0x10 } };
      PSID_IDENTIFIER_AUTHORITY sid_id_auth = GetSidIdentifierAuthority(p);

      if (memcmp(il_id_auth.Value, sid_id_auth->Value, sizeof(il_id_auth.Value)) == 0)
      {
        return !!AddIntegrityLabelToBoundaryDescriptor(&boundary_desc_, p);
      }
      else
      {
        return !!AddSIDToBoundaryDescriptor(&boundary_desc_, p);
      }
    }
  }