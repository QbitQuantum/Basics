// Returns true if the load bias reported by the linker is incorrect for the
// given entry. This
// function is used to handle cases where we want to work around a bug in the
// system linker.
static bool isLoadBiasIncorrect(Target &target, const std::string &file_path) {
  // On Android L (API 21, 22) the load address of the "/system/bin/linker"
  // isn't filled in
  // correctly.
  uint32_t os_major = 0, os_minor = 0, os_update = 0;
  if (target.GetArchitecture().GetTriple().isAndroid() &&
      target.GetPlatform()->GetOSVersion(os_major, os_minor, os_update) &&
      (os_major == 21 || os_major == 22) &&
      (file_path == "/system/bin/linker" ||
       file_path == "/system/bin/linker64")) {
    return true;
  }

  return false;
}