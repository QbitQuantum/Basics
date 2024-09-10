// _lib1.so and _lib2.so are now searchable by having another namespace 'ns2'
// whose search paths include the 'ns2/' subdir.
TEST(dl, exec_with_ld_config_file) {
#if defined(__BIONIC__)
  if (!is_debuggable_build()) {
    // LD_CONFIG_FILE is not supported on user build
    return;
  }
  std::string helper = get_testlib_root() +
      "/ld_config_test_helper/ld_config_test_helper";
  TemporaryFile config_file;
  create_ld_config_file(config_file.filename);
  std::string env = std::string("LD_CONFIG_FILE=") + config_file.filename;
  chmod(helper.c_str(), 0755);
  ExecTestHelper eth;
  eth.SetArgs({ helper.c_str(), nullptr });
  eth.SetEnv({ env.c_str(), nullptr });
  eth.Run([&]() { execve(helper.c_str(), eth.GetArgs(), eth.GetEnv()); }, 0, "12345");
#endif
}