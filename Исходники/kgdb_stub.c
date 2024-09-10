/*
 * Send a message.  The host gets one chance to read it.
 */
static void
kgdb_send(u_char type, u_char *bp, int len)
{
    u_char csum;
    u_char *ep = bp + len;

    PUTC(FRAME_START);
    PUTESC(type);

    csum = type;
    while (bp < ep) {
        type = *bp++;
        csum += type;
        PUTESC(type)
    }
    csum = -csum;
    PUTESC(csum)
    PUTC(FRAME_END);
}