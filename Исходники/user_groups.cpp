void processLocalUserGroups(std::string uid,
                            std::string user,
                            QueryData& results) {
  unsigned long userGroupInfoLevel = 0;
  unsigned long numGroups = 0;
  unsigned long totalUserGroups = 0;
  LOCALGROUP_USERS_INFO_0* ginfo = nullptr;
  PSID sid = nullptr;

  unsigned long ret = 0;

  ret = NetUserGetLocalGroups(nullptr,
                              stringToWstring(user).c_str(),
                              userGroupInfoLevel,
                              1,
                              reinterpret_cast<LPBYTE*>(&ginfo),
                              MAX_PREFERRED_LENGTH,
                              &numGroups,
                              &totalUserGroups);
  if (ret == ERROR_MORE_DATA) {
    LOG(WARNING) << "User " << user
                 << " group membership exceeds buffer limits, processing "
                 << numGroups << " our of " << totalUserGroups << " groups";
  } else if (ret != NERR_Success || ginfo == nullptr) {
    VLOG(1) << " NetUserGetLocalGroups failed for user " << user << " with "
            << ret;
    return;
  }

  for (size_t i = 0; i < numGroups; i++) {
    Row r;
    auto sid = getSidFromUsername(ginfo[i].lgrui0_name);

    r["uid"] = uid;
    r["gid"] = INTEGER(getGidFromSid(static_cast<PSID>(sid.get())));

    results.push_back(r);
  }

  if (ginfo != nullptr) {
    NetApiBufferFree(ginfo);
  }
}