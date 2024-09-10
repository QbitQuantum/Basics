wchar_t input_common_readch(int timed)
{
    if (! has_lookahead())
    {
        if (timed)
        {
            int count;
            fd_set fds;
            struct timeval tm=
            {
                0,
                1000 * WAIT_ON_ESCAPE
            }
            ;

            FD_ZERO(&fds);
            FD_SET(0, &fds);
            count = select(1, &fds, 0, 0, &tm);

            switch (count)
            {
                case 0:
                    return WEOF;

                case -1:
                    return WEOF;
                    break;
                default:
                    break;

            }
        }

        wchar_t res;
        mbstate_t state = {};

        while (1)
        {
            wint_t b = readb();
            char bb;

            size_t sz;

            if ((b >= R_NULL) && (b < R_NULL + 1000))
                return b;

            bb=b;

            sz = mbrtowc(&res, &bb, 1, &state);

            switch (sz)
            {
                case (size_t)(-1):
                    memset(&state, '\0', sizeof(state));
                    debug(2, L"Illegal input");
                    return R_NULL;
                case (size_t)(-2):
                    break;
                case 0:
                    return 0;
                default:
                    return res;
            }
        }
    }
    else
    {
        if (!timed)
        {
            while (has_lookahead() && lookahead_top() == WEOF)
                lookahead_pop();
            if (! has_lookahead())
                return input_common_readch(0);
        }

        return lookahead_pop();
    }
}