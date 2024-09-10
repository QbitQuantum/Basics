  /**
   * \brief Get an error string from an error code.
   */
  static std::string get_error_string(int err)
  {
    char buf[512];
#if defined(__GNUC__)
    strerror_r(err, buf, sizeof(buf));
#elif defined(_MSC_VER)
    strerror_s(buf, sizeof(buf), err);
#endif
    return std::string(buf);
  }