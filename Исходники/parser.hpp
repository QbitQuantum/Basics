    inline bool _parse_codepoint(String& out, parser<Iter>& in)
    {
        int uni_ch;

        if ((uni_ch = _parse_quadhex(in)) == -1)
        {
            return false;
        }

        if (0xd800 <= uni_ch && uni_ch <= 0xdfff)
        {
            if (0xdc00 <= uni_ch)
            {
                // a second 16-bit of a surrogate pair appeared
                return false;
            }

            // first 16-bit of surrogate pair, get the next one
            if (in.getc() != '\\' || in.getc() != 'u')
            {
                in.ungetc();
                return false;
            }

            int second = _parse_quadhex(in);

            if (!(0xdc00 <= second && second <= 0xdfff))
            {
                return false;
            }

            uni_ch = ((uni_ch - 0xd800) << 10) | ((second - 0xdc00) & 0x3ff);
            uni_ch += 0x10000;
        }

        if (uni_ch < 0x80)
        {
            out.push_back(uni_ch);
        }
        else
        {
            if (uni_ch < 0x800)
            {
                out.push_back(0xc0 | (uni_ch >> 6));
            }
            else
            {
                if (uni_ch < 0x10000)