  virtual int check_test(unsigned int last_checkpoint,
      DataTestResult *test_result) override {
    for (unsigned int i = 0; i < NUM_TEST_FILES; ++i) {
      const string file_name = string(TEST_MNT "/" TEST_DIR "/" TEST_FILE
          + std::to_string(i));
      struct stat stats;
      int res = stat(file_name.c_str(), &stats);
      if (res < 0) {
        test_result->SetError(DataTestResult::kFileMissing);
        return 0;
      }
      if (!S_ISREG(stats.st_mode)) {
        test_result->SetError(DataTestResult::kFileMetadataCorrupted);
        return 0;
      }
      if (((S_IRWXU | S_IRWXG | S_IRWXO) & stats.st_mode) != TEST_FILE_PERMS) {
        test_result->SetError(DataTestResult::kFileMetadataCorrupted);
        return 0;
      }

      const int fd = open(file_name.c_str(), O_RDONLY);
      if (fd < 0) {
        test_result->SetError(DataTestResult::kOther);
        return 0;
      }

      unsigned int bytes_read = 0;
      char* buf = (char*) calloc(TEST_TEXT_SIZE, sizeof(char));
      if (buf == NULL) {
        test_result->SetError(DataTestResult::kOther);
      }
      do {
        res = read(fd, buf + bytes_read, TEST_TEXT_SIZE - bytes_read);
        if (res < 0) {
          free(buf);
          close(fd);
          test_result->SetError(DataTestResult::kOther);
          return 0;
        } else if (res == 0) {
          break;
        }
        bytes_read += res;
      } while (bytes_read < TEST_TEXT_SIZE);
      close(fd);

      if (bytes_read != TEST_TEXT_SIZE) {
        test_result->SetError(DataTestResult::kFileDataCorrupted);
      } else if (memcmp(text, buf, TEST_TEXT_SIZE) != 0) {
        test_result->SetError(DataTestResult::kFileDataCorrupted);
      }

      free(buf);
    }
    return 0;
  }