  void open_config()
  {
    libconfig::Config cfg;
    try  {
      cfg.readFile(TEST_CONF_FILE.c_str());
    }
    catch(const libconfig::FileIOException &fioex)  {
      ASSERT_TRUE(false);
    }
    catch(const libconfig::ParseException &pex)   {
      ASSERT_TRUE(false);
    }

    const libconfig::Setting& config_root = cfg.getRoot();
    test_regex_manager = new RegexManager(TEMP_DIR, config_root, &test_ip_database, &test_swabber_interface);

  }