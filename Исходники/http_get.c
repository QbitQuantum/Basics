static int
httprecv(int sfd, struct string* buf, int* httpres)
{
    char* b;
    ssize_t bl, bptr = 0;
    size_t i;
    struct string oneline;
    int retval = HTTP_EOK;
    int BUFSIZE = 8192;
    int isfirsthdr = 1;

    if ((b = malloc(BUFSIZE)) == NULL) return HTTP_ENOMEM;
    string_init(&oneline, 512, 512);

    while(1) {
        bl = recv(sfd, b + bptr, BUFSIZE - bptr, 0);
        if (bl == 0) {
            if (bptr == 0) {
                break;
            }
        } else if (bl < 0) {
            retval = HTTP_ENETERR;
            goto bail_out;
        }
        bptr += bl;
        if ((*b == '\n') || (*b == '\r')) goto finished;
        for (i = 0; i < bptr; i++) {
            if (b[i] == '\n') {
                string_clear(&oneline);
                if (string_concatb(&oneline, b, i)) { retval=HTTP_ENOMEM; goto bail_out; }
                if (oneline.s[oneline._u._s.length - 1] == '\r') --oneline._u._s.length;
                if (++i >= bptr) { retval=HTTP_ESRVERR; goto bail_out; }
                if (bptr != i) {
                    memmove(b, b + i, bptr - i);
                }
                bptr -= i;
                if (isfirsthdr) {
                    if (handle_header(&oneline, httpres)) { retval=HTTP_ESRVERR; goto bail_out; }
                    isfirsthdr = 0;
                }
                break;
            }
        }
    }
finished:

    if (isfirsthdr) { retval=HTTP_ESRVERR; goto bail_out; }

    bl = 0;
    if (bptr > 2) {
        if ((b[0] == '\r') || (b[0] == '\n')) {
            ++bl;
            if ((b[1] == '\r') || (b[1] == '\n')) {
                ++bl;
            }
        }
    }
    if (string_concatb(buf, b + bl, bptr - bl)) { retval=HTTP_ENOMEM; goto bail_out; }
    while(1) {
        bl = recv(sfd, b, BUFSIZE, 0);
        if (bl == 0) break;
        if (bl < 0) { retval=HTTP_ENETERR; goto bail_out; }
        if (string_concatb(buf, b, bl)) { retval=HTTP_ENOMEM; goto bail_out; }
    }

    if (retval == HTTP_EOK) if (*httpres != 200) retval = HTTP_ESRVERR;

bail_out:
    close(sfd);
    string_free(&oneline);
    free(b);
    return retval;
}