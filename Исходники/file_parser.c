/// Parse a file with a revocation list of any type
static EpidStatus EpidParseRlFile(void const* buf, size_t len,
                                  EpidCaCertificate const* cert, void* rl,
                                  size_t* rl_len, EpidFileType file_type) {
  size_t min_rl_file_size = 0;
  size_t empty_rl_size = 0;
  size_t rl_entry_size = 0;
  EpidStatus result = kEpidErr;
  EpidFileHeader const* file_header = (EpidFileHeader*)buf;
  void const* buf_rl =
      (void const*)((unsigned char*)buf + sizeof(EpidFileHeader));
  size_t buf_rl_len = 0;
  EcdsaSignature const* signature = NULL;

  if (!buf || !cert || !rl_len) return kEpidBadArgErr;

  switch (file_type) {
    case kPrivRlFile:
      empty_rl_size = sizeof(PrivRl) - sizeof(((PrivRl*)0)->f[0]);
      rl_entry_size = sizeof(((PrivRl*)0)->f[0]);
      min_rl_file_size = sizeof(EpidFileHeader) + sizeof(PrivRl) -
                         sizeof(((PrivRl*)0)->f[0]) + sizeof(EcdsaSignature);
      break;
    case kSigRlFile:
      empty_rl_size = sizeof(SigRl) - sizeof(((SigRl*)0)->bk[0]);
      rl_entry_size = sizeof(((SigRl*)0)->bk[0]);
      min_rl_file_size = sizeof(EpidFileHeader) + sizeof(SigRl) -
                         sizeof(((SigRl*)0)->bk[0]) + sizeof(EcdsaSignature);
      break;
    case kGroupRlFile:
      empty_rl_size = sizeof(GroupRl) - sizeof(((GroupRl*)0)->gid[0]);
      rl_entry_size = sizeof(((GroupRl*)0)->gid[0]);
      min_rl_file_size = sizeof(EpidFileHeader) + sizeof(GroupRl) -
                         sizeof(((GroupRl*)0)->gid[0]) + sizeof(EcdsaSignature);
      break;
    default:
      return kEpidErr;
  }

  if (min_rl_file_size > len) return kEpidBadArgErr;

  // Verify that Intel(R) EPID file header in the buffer is correct
  if (0 !=
      memcmp(&file_header->epid_version, &kEpidVersion, sizeof(kEpidVersion))) {
    return kEpidBadArgErr;
  }
  if (0 != memcmp(&file_header->file_type, &kEpidFileTypeCode[file_type],
                  sizeof(file_header->file_type))) {
    return kEpidBadArgErr;
  }

  // Verify that CA certificate is correct
  result = EpidVerifyCaCertificate(cert);
  if (kEpidNoErr != result) return result;

  // Verify that RL in file buffer contains of integer number of entries
  buf_rl_len = len - sizeof(EpidFileHeader) - sizeof(EcdsaSignature);
  if (0 != ((buf_rl_len - empty_rl_size) % rl_entry_size)) {
    return kEpidBadArgErr;
  }

  signature =
      (EcdsaSignature*)((unsigned char*)buf + len - sizeof(EcdsaSignature));
  // Authenticate signature for buffer
  result = EcdsaVerifyBuffer(buf, len - sizeof(EcdsaSignature),
                             (EcdsaPublicKey*)&cert->pubkey, signature);
  if (kEpidSigValid != result) return result;

  buf_rl_len = len - sizeof(EpidFileHeader) - sizeof(EcdsaSignature);

  // If pointer to output buffer is NULL it should return required size of RL
  if (!rl) {
    *rl_len = buf_rl_len;
    return kEpidNoErr;
  }

  if (*rl_len < buf_rl_len) return kEpidBadArgErr;
  *rl_len = buf_rl_len;

  // Copy revocation list from file buffer to output
  // Memory copy is used to copy a revocation list of variable length
  if (0 != memcpy_S(rl, *rl_len, buf_rl, buf_rl_len)) return kEpidBadArgErr;

  return kEpidNoErr;
}