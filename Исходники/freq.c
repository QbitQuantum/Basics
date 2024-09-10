uint8_t* f2str(freq_t f, uint8_t *buffer, uint8_t len)
{
    uint8_t i;
    uint8_t j;
    uint8_t *p;

    // Mhz
    ultoa(f_MHZ(f), buffer, 10);

    i = len - strlen(buffer);
    j = 0;
    p = buffer + strlen(buffer);

    // multiply fractional part to get the rest of required digits
    while (j < i) {
        if (j & 0b11) {
            f = 10 * (f - MHZ_f(f_MHZ(f)));
            *p = '0' + f_MHZ(f);
        }
        else{
            if (j == 0) *p = ',';
            else *p = '.';
        }
        ++p;
        ++j;
    }

    // discard ending dot
    if (*(p-1) == '.') --p;
    *p = '\0';

    return buffer;
}