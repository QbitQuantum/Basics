int loadStrings()
{
    const size_t tokenNum = 1 + STR_NUM * 2;
    jsmntok_t t[tokenNum];
    char buf[8192];
    jsmn_parser p;
    unsigned int i, j, k;
    const char *s;
    int l, r, len;
    File fd;

    sprintf(buf, "%s/%s", langPath, cfgs[CFG_LANG].val.s);
    if (!FileOpen(&fd, buf, 0))
        return 1;

    len = FileGetSize(&fd);
    if (len > sizeof(buf))
        return 1;

    FileRead(&fd, buf, len, 0);
    FileClose(&fd);

    jsmn_init(&p);
    r = jsmn_parse(&p, buf, len, t, tokenNum);
    if (r < 0)
        return r;

    for (i = 1; i < r; i++) {
        for (j = 0; j < STR_NUM; j++) {
            s = buf + t[i].start;

            len = t[i].end - t[i].start;
            if (!memcmp(s, keys[j], len) && !keys[j][len]) {
                i++;
                len = t[i].end - t[i].start;
                s = buf + t[i].start;
                for (k = 0; k + 1 < STR_MAX_LEN && len > 0; k++) {
                    l = mbtowc(strings[j] + k, s, len);
                    if (l < 0)
                        break;

                    len -= l;
                    s += l;
                }

                strings[j][k] = 0;
                mbtowc(NULL, NULL, 0);
                break;
            }
        }
    }

    return 0;
}