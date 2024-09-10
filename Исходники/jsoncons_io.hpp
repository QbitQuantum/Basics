    void print(double val, buffered_ostream<CharT>& os)
    {
        char buf[_CVTBUFSIZE];
        int decimal_point = 0;
        int sign = 0;

        if (precision_ >= _CVTBUFSIZE)
        {
            precision_ = _CVTBUFSIZE - 1;
        }

        int err = _ecvt_s(buf, _CVTBUFSIZE, val, precision_, &decimal_point, &sign);
        if (err != 0)
        {
            throw std::runtime_error("Failed attempting double to string conversion");
        }
        char* s = buf;
        char* se = s + precision_;

        int i, k;
        int j;

        if (sign)
        {
            os.put('-');
        }
        if (decimal_point <= -4 || decimal_point > se - s + 5) 
        {
            os.put(*s++);
            if (s < se) 
            {
                os.put('.');
                while ((se-1) > s && *(se-1) == '0')
                {
                    --se;
                }

                while(s < se)
                {
                    os.put(*s++);
                }
            }
            os.put('e');
            /* sprintf(b, "%+.2d", decimal_point - 1); */
            if (--decimal_point < 0) {
                os.put('-');
                decimal_point = -decimal_point;
                }
            else
                os.put('+');
            for(j = 2, k = 10; 10*k <= decimal_point; j++, k *= 10);
            for(;;) 
            {
                i = decimal_point / k;
                os.put(i + '0');
                if (--j <= 0)
                    break;
                decimal_point -= i*k;
                decimal_point *= 10;
            }
        }
        else if (decimal_point <= 0) 
        {
            os.put('0');
            os.put('.');
            while ((se-1) > s && *(se-1) == '0')
            {
                --se;
            }
            for(; decimal_point < 0; decimal_point++)
            {
                os.put('0');
            }
            while(s < se)
            {
                os.put(*s++);
            }
        }
        else {
            while(s < se) 
            {
                os.put(*s++);
                if ((--decimal_point == 0) && s < se)
                {
                    os.put('.');
                    while ((se-1) > s && *(se-1) == '0')
                    {
                        --se;
                    }
                }
            }
            for(; decimal_point > 0; decimal_point--)
            {
                os.put('0');
            }
        }
    }