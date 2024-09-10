/* Try to interpret a whole incoming packet */
static int baum_eat_packet(BaumDriverState *baum, const uint8_t *buf, int len)
{
    const uint8_t *cur = buf;
    uint8_t req = 0;

    if (!len--)
        return 0;
    if (*cur++ != ESC) {
        while (*cur != ESC) {
            if (!len--)
                return 0;
            cur++;
        }
        DPRINTF("Dropped %d bytes!\n", cur - buf);
    }

#define EAT(c) do {\
    if (!len--) \
        return 0; \
    if ((c = *cur++) == ESC) { \
        if (!len--) \
            return 0; \
        if (*cur++ != ESC) { \
            DPRINTF("Broken packet %#2x, tossing\n", req); \
            if (timer_pending(baum->cellCount_timer)) {    \
                timer_del(baum->cellCount_timer);     \
                baum_cellCount_timer_cb(baum);             \
            } \
            return (cur - 2 - buf); \
        } \
    } \
} while (0)

    EAT(req);
    switch (req) {
    case BAUM_REQ_DisplayData:
    {
        uint8_t cells[baum->x * baum->y], c;
        uint8_t text[baum->x * baum->y];
        uint8_t zero[baum->x * baum->y];
        int cursor = BRLAPI_CURSOR_OFF;
        int i;

        /* Allow 100ms to complete the DisplayData packet */
        timer_mod(baum->cellCount_timer, qemu_clock_get_ns(QEMU_CLOCK_VIRTUAL) +
                       get_ticks_per_sec() / 10);
        for (i = 0; i < baum->x * baum->y ; i++) {
            EAT(c);
            cells[i] = c;
            if ((c & (BRLAPI_DOT7|BRLAPI_DOT8))
                    == (BRLAPI_DOT7|BRLAPI_DOT8)) {
                cursor = i + 1;
                c &= ~(BRLAPI_DOT7|BRLAPI_DOT8);
            }
            if (!(c = nabcc_translation[c]))
                c = '?';
            text[i] = c;
        }
        timer_del(baum->cellCount_timer);

        memset(zero, 0, sizeof(zero));

        brlapi_writeArguments_t wa = {
            .displayNumber = BRLAPI_DISPLAY_DEFAULT,
            .regionBegin = 1,
            .regionSize = baum->x * baum->y,
            .text = (char *)text,
            .textSize = baum->x * baum->y,
            .andMask = zero,
            .orMask = cells,
            .cursor = cursor,
            .charset = (char *)"ISO-8859-1",
        };

        if (brlapi__write(baum->brlapi, &wa) == -1)
            brlapi_perror("baum brlapi_write");
        break;
    }
    case BAUM_REQ_SetMode:
    {
        uint8_t mode, setting;
        DPRINTF("SetMode\n");
        EAT(mode);
        EAT(setting);
        /* ignore */
        break;
    }
    case BAUM_REQ_SetProtocol:
    {
        uint8_t protocol;
        DPRINTF("SetProtocol\n");
        EAT(protocol);
        /* ignore */
        break;
    }
    case BAUM_REQ_GetDeviceIdentity:
    {
        uint8_t identity[17] = { BAUM_RSP_DeviceIdentity,
            'B','a','u','m',' ','V','a','r','i','o' };
        DPRINTF("GetDeviceIdentity\n");
        identity[11] = '0' + baum->x / 10;
        identity[12] = '0' + baum->x % 10;
        baum_write_packet(baum, identity, sizeof(identity));
        break;
    }
    case BAUM_REQ_GetVersionNumber:
    {
        uint8_t version[] = { BAUM_RSP_VersionNumber, 1 }; /* ? */
        DPRINTF("GetVersionNumber\n");
        baum_write_packet(baum, version, sizeof(version));
        break;
    }
    case BAUM_REQ_GetSerialNumber:
    {
        uint8_t serial[] = { BAUM_RSP_SerialNumber,
            '0','0','0','0','0','0','0','0' };
        DPRINTF("GetSerialNumber\n");
        baum_write_packet(baum, serial, sizeof(serial));
        break;
    }
    case BAUM_REQ_GetKeys:
    {
        DPRINTF("Get%0#2x\n", req);
        /* ignore */
        break;
    }
    default:
        DPRINTF("unrecognized request %0#2x\n", req);
        do
            if (!len--)
                return 0;
        while (*cur++ != ESC);
        cur--;
        break;
    }
    return cur - buf;
}

/* The other end is writing some data.  Store it and try to interpret */
static int baum_write(CharDriverState *chr, const uint8_t *buf, int len)
{
    BaumDriverState *baum = chr->opaque;
    int tocopy, cur, eaten, orig_len = len;

    if (!len)
        return 0;
    if (!baum->brlapi)
        return len;

    while (len) {
        /* Complete our buffer as much as possible */
        tocopy = len;
        if (tocopy > BUF_SIZE - baum->in_buf_used)
            tocopy = BUF_SIZE - baum->in_buf_used;

        memcpy(baum->in_buf + baum->in_buf_used, buf, tocopy);
        baum->in_buf_used += tocopy;
        buf += tocopy;
        len -= tocopy;

        /* Interpret it as much as possible */
        cur = 0;
        while (cur < baum->in_buf_used &&
                (eaten = baum_eat_packet(baum, baum->in_buf + cur, baum->in_buf_used - cur)))
            cur += eaten;

        /* Shift the remainder */
        if (cur) {
            memmove(baum->in_buf, baum->in_buf + cur, baum->in_buf_used - cur);
            baum->in_buf_used -= cur;
        }

        /* And continue if any data left */
    }
    return orig_len;
}