static bool  /* consumes input bytes; knows nothing about records! */
skip_input_bytes(RECSTREAM *rstrm, long cnt)
{
    u_int32_t current;

    while (cnt > 0) {
      current = (size_t)(PtrToUlong(rstrm->in_boundry) -
			 PtrToUlong(rstrm->in_finger));
        if (current == 0) {
            if (! fill_input_buf(rstrm, INT_MAX))
                return (FALSE);
            continue;
        }
        current = (u_int32_t)((cnt < current) ? cnt : current);
        rstrm->in_finger += current;
        cnt -= current;
    }
    return (TRUE);
}