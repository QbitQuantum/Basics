TEST(adb_utils, directory_exists) {
#ifdef _WIN32
  char profiles_dir[MAX_PATH];
  DWORD cch = arraysize(profiles_dir);

  // On typical Windows 7, returns C:\Users
  ASSERT_TRUE(GetProfilesDirectoryA(profiles_dir, &cch));

  ASSERT_TRUE(directory_exists(profiles_dir));

  // On modern (English?) Windows, this is a directory symbolic link to
  // C:\ProgramData. Symbolic links are rare on Windows and the user requires
  // a special permission (by default granted to Administrative users) to
  // create symbolic links.
  ASSERT_FALSE(directory_exists(subdir(profiles_dir, "All Users")));

  // On modern (English?) Windows, this is a directory junction to
  // C:\Users\Default. Junctions are used throughout user profile directories
  // for backwards compatibility and they don't require any special permissions
  // to create.
  ASSERT_FALSE(directory_exists(subdir(profiles_dir, "Default User")));

  ASSERT_FALSE(directory_exists(subdir(profiles_dir, "does-not-exist")));
#else
  ASSERT_TRUE(directory_exists("/proc"));
  ASSERT_FALSE(directory_exists("/proc/self")); // Symbolic link.
  ASSERT_FALSE(directory_exists("/proc/does-not-exist"));
#endif
}