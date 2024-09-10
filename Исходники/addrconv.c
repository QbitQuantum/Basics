ULONG
MyInetAddr(
    IN LPWSTR String,
    OUT LPWSTR * Terminator
    )

/*++

Routine Description:

    This function interprets the character string specified by the cp
    parameter.  This string represents a numeric Internet address
    expressed in the Internet standard ".'' notation.  The value
    returned is a number suitable for use as an Internet address.  All
    Internet addresses are returned in network order (bytes ordered from
    left to right).

    Internet Addresses

    Values specified using the "." notation take one of the following
    forms:

    a.b.c.d   a.b.c     a.b  a

    When four parts are specified, each is interpreted as a byte of data
    and assigned, from left to right, to the four bytes of an Internet
    address.  Note that when an Internet address is viewed as a 32-bit
    integer quantity on the Intel architecture, the bytes referred to
    above appear as "d.c.b.a''.  That is, the bytes on an Intel
    processor are ordered from right to left.

    Note: The following notations are only used by Berkeley, and nowhere
    else on the Internet.  In the interests of compatibility with their
    software, they are supported as specified.

    When a three part address is specified, the last part is interpreted
    as a 16-bit quantity and placed in the right most two bytes of the
    network address.  This makes the three part address format
    convenient for specifying Class B network addresses as
    "128.net.host''.

    When a two part address is specified, the last part is interpreted
    as a 24-bit quantity and placed in the right most three bytes of the
    network address.  This makes the two part address format convenient
    for specifying Class A network addresses as "net.host''.

    When only one part is given, the value is stored directly in the
    network address without any byte rearrangement.

Arguments:

    String - A character string representing a number expressed in the
        Internet standard "." notation.

    Terminator - Receives a pointer to the character that terminated
        the conversion.

Return Value:

    If no error occurs, inet_addr() returns an in_addr structure
    containing a suitable binary representation of the Internet address
    given.  Otherwise, it returns the value INADDR_NONE.

--*/

{
        ULONG val, base, n;
        WCHAR c;
        ULONG parts[4], *pp = parts;

again:
        /*
         * Collect number up to ``.''.
         * Values are specified as for C:
         * 0x=hex, 0=octal, other=decimal.
         */
        val = 0; base = 10;
        if (*String == L'0') {
                base = 8, String++;
                if (*String == L'x' || *String == L'X')
                        base = 16, String++;
        }

        while (c = *String) {
                if (iswdigit(c)) {
                        val = (val * base) + (c - L'0');
                        String++;
                        continue;
                }
                if (base == 16 && iswxdigit(c)) {
                        val = (val << 4) + (c + 10 - (islower(c) ? L'a' : L'A'));
                        String++;
                        continue;
                }
                break;
        }
        if (*String == L'.') {
                /*
                 * Internet format:
                 *      a.b.c.d
                 *      a.b.c   (with c treated as 16-bits)
                 *      a.b     (with b treated as 24 bits)
                 */
                /* GSS - next line was corrected on 8/5/89, was 'parts + 4' */
                if (pp >= parts + 3) {
                        *Terminator = String;
                        return ((ULONG) -1);
                }
                *pp++ = val, String++;
                goto again;
        }
        /*
         * Check for trailing characters.
         */
        if (*String && !iswspace(*String) && (*String != L':')) {
                *Terminator = String;
                return (INADDR_NONE);
        }
        *pp++ = val;
        /*
         * Concoct the address according to
         * the number of parts specified.
         */
        n = pp - parts;
        switch ((int) n) {

        case 1:                         /* a -- 32 bits */
                val = parts[0];
                break;

        case 2:                         /* a.b -- 8.24 bits */
                if ((parts[0] > 0xff) || (parts[1] > 0xffffff)) {
                    *Terminator = String;
                    return(INADDR_NONE);
                }
                val = (parts[0] << 24) | (parts[1] & 0xffffff);
                break;

        case 3:                         /* a.b.c -- 8.8.16 bits */
                if ((parts[0] > 0xff) || (parts[1] > 0xff) ||
                    (parts[2] > 0xffff)) {
                    *Terminator = String;
                    return(INADDR_NONE);
                }
                val = (parts[0] << 24) | ((parts[1] & 0xff) << 16) |
                        (parts[2] & 0xffff);
                break;

        case 4:                         /* a.b.c.d -- 8.8.8.8 bits */
                if ((parts[0] > 0xff) || (parts[1] > 0xff) ||
                    (parts[2] > 0xff) || (parts[3] > 0xff)) {
                    *Terminator = String;
                    return(INADDR_NONE);
                }
                val = (parts[0] << 24) | ((parts[1] & 0xff) << 16) |
                      ((parts[2] & 0xff) << 8) | (parts[3] & 0xff);
                break;

        default:
                *Terminator = String;
                return (INADDR_NONE);
        }

        val = SWAP_LONG(val);
        *Terminator = String;
        return (val);
}