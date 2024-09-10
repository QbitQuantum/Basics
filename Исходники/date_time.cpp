    time_t date_time::to_time(const tm_type& tm, bool check_wday) {
        assert_in_range(tm, check_wday);
        time_t t;
        tm_type tt = tm;
#ifdef _WIN32
        t = _mkgmtime(&tt);
#else
        t = timegm(&tt);
#endif
        if (t == NULL_TIME)
            throw std::invalid_argument("invalid time structure on conversion to date and time");
        // Check that tm is canonical.
        std::string err;
        if (check_wday && tm.tm_wday != tt.tm_wday)
            err = std::string("week day (1-7) incorrect: ") + uripp::convert(tm.tm_wday + 1);
        else if (tm.tm_mday != tt.tm_mday)
            err = std::string("month day (1-31) incorrect: ") + uripp::convert(tm.tm_mday);
        else if (tm.tm_sec != tt.tm_sec)
            err = std::string("second (0-60) incorrect: ") + uripp::convert(tm.tm_sec);
        if (!err.empty()) {
            std::ostringstream oss;
            oss << "time structure for date (YYY-MM-DD) "
                << (tm.tm_year + 1900) << "-"
                << std::setw(2) << std::setfill('0') << (tm.tm_mon + 1) << "-"
                << std::setw(2) << std::setfill('0') << tm.tm_mday << ": "
                << err;
            throw std::invalid_argument(oss.str());
        }
        return t;
    }