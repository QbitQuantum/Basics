void ChaCha::encrypt(uint8_t *output, const uint8_t *input, size_t len)
{
    while (len > 0) {
        if (posn >= 64) {
            // Generate a new encrypted counter block.
            hashCore((uint32_t *)stream, (const uint32_t *)block, rounds);
            posn = 0;

            // Increment the counter, taking care not to reveal
            // any timing information about the starting value.
            // We iterate through the entire counter region even
            // if we could stop earlier because a byte is non-zero.
            uint16_t temp = 1;
            uint8_t index = 48;
            while (index < 56) {
                temp += block[index];
                block[index] = (uint8_t)temp;
                temp >>= 8;
                ++index;
            }
        }
        uint8_t templen = 64 - posn;
        if (templen > len)
            templen = len;
        len -= templen;
        while (templen > 0) {
            *output++ = *input++ ^ stream[posn++];
            --templen;
        }
    }