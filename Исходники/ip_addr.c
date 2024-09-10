/**
 * Check whether "cp" is a valid ascii representation
 * of an Internet address and convert to a binary address.
 * Returns 1 if the address is valid, 0 if not.
 * This replaces inet_addr, the return value from which
 * cannot distinguish between failure and a local broadcast address.
 *
 * @param cp IP address in ascii represenation (e.g. "127.0.0.1")
 * @param addr pointer to which to save the ip address in network order
 * @return 1 if cp could be converted to addr, 0 on failure
 */
int
ipaddr_aton(const char *cp, ip_addr_t *addr)
{
    u32_t val;
    u8_t base;
    char c;
    u32_t parts[4];
    u32_t *pp = parts;

    c = *cp;
    for (;;) {
        /*
         * Collect number up to ``.''.
         * Values are specified as for C:
         * 0x=hex, 0=octal, 1-9=decimal.
         */
        if (!isdigit(c))
            return (0);
        val = 0;
        base = 10;
        if (c == '0') {
            c = *++cp;
            if (c == 'x' || c == 'X') {
                base = 16;
                c = *++cp;
            } else
                base = 8;
        }
        for (;;) {
            if (isdigit(c)) {
                val = (val * base) + (int)(c - '0');
                c = *++cp;
            } else if (base == 16 && isxdigit(c)) {
                val = (val << 4) | (int)(c + 10 - (islower(c) ? 'a' : 'A'));
                c = *++cp;
            } else
                break;
        }
        if (c == '.') {
            /*
             * Internet format:
             *  a.b.c.d
             *  a.b.c   (with c treated as 16 bits)
             *  a.b (with b treated as 24 bits)
             */
            if (pp >= parts + 3) {
                return (0);
            }
            *pp++ = val;
            c = *++cp;
        } else
            break;
    }
    /*
     * Check for trailing characters.
     */
    if (c != '\0' && !isspace(c)) {
        return (0);
    }
    /*
     * Concoct the address according to
     * the number of parts specified.
     */
    switch (pp - parts + 1) {

        case 0:
            return (0);       /* initial nondigit */

        case 1:             /* a -- 32 bits */
            break;

        case 2:             /* a.b -- 8.24 bits */
            if (val > 0xffffffUL) {
                return (0);
            }
            val |= parts[0] << 24;
            break;

        case 3:             /* a.b.c -- 8.8.16 bits */
            if (val > 0xffff) {
                return (0);
            }
            val |= (parts[0] << 24) | (parts[1] << 16);
            break;

        case 4:             /* a.b.c.d -- 8.8.8.8 bits */
            if (val > 0xff) {
                return (0);
            }
            val |= (parts[0] << 24) | (parts[1] << 16) | (parts[2] << 8);
            break;
        default:
            LWIP_ASSERT("unhandled", 0);
            break;
    }
    if (addr) {
        ip4_addr_set_u32(addr, htonl(val));
    }
    return (1);
}