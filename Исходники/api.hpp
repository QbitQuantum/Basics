    inline std::wstring wcsfmon_l(double value,winlocale const &l)
    {
        std::wostringstream ss;
        ss.imbue(std::locale::classic());

        ss << std::setprecision(std::numeric_limits<double>::digits10+1) << value;
        std::wstring sval = ss.str();
        int len = GetCurrencyFormatW(l.lcid,0,sval.c_str(),0,0,0);
        std::vector<wchar_t> buf(len+1);
        GetCurrencyFormatW(l.lcid,0,sval.c_str(),0,&buf.front(),len);
        return &buf.front();
    }