std::basic_string<Char> float_to_string(double val, size_t precision)
{
    std::basic_string<Char> s;
    char buf[_CVTBUFSIZE];
    int decimal_point = 0;
    int sign = 0;

    if (precision >= _CVTBUFSIZE)
    {
        precision = _CVTBUFSIZE - 1;
    }

    int err = _ecvt_s(buf, _CVTBUFSIZE, val, static_cast<int>(precision), &decimal_point, &sign);
    if (err != 0)
    {
        throw std::runtime_error("Failed attempting double to string conversion");
    }
    if (sign != 0)
    {
        s.push_back('-');
    }

    int len = static_cast<int>(precision);

    int decimal;
    int exponent;
    if (decimal_point < 0 || decimal_point > len)
    {
        decimal = 1;
        exponent = decimal_point - 1;
    }
    else
    {
        decimal = decimal_point;
        exponent = 0;
    }

    while (len >= 2 && buf[len - 1] == '0' && (len - 1) != decimal)
    {
        --len;
    }

    if (decimal == 0)
    {
        s.push_back('0');
        s.push_back('.');
    }
    s.push_back(buf[0]);
    for (int i = 1; i < len; ++i)
    {
        if (i == decimal)
        {
            s.push_back('.');
        }
        s.push_back(buf[i]);
    }
    if (exponent != 0)
    {
        s.push_back('e');
        if (exponent > 0)
        {
            s.push_back('+');
        }
        int err2 = _itoa_s(exponent,buf,_CVTBUFSIZE,10);
        if (err2 != 0)
        {
            throw std::runtime_error("Failed attempting double to string conversion");
        }
        for (int i = 0; i < _CVTBUFSIZE && buf[i]; ++i)
        {
            s.push_back(buf[i]);
        }
    }
    return s;
}