int main(int argc, char **argv) {
    uint8_t digest[DIGEST_SIZE], buf[BUFSIZE];
    size_t c, i;
    char *file;
    FILE *fp;

#if HMAC_MODE
    char *key;
    size_t keylen;

    if (argc < 2) {
        printf("Usage: %s <key> [FILE]\n", argv[0]);
        return 1;
    } else if (argc < 3) {
        file = "-";
    } else {
        file = argv[2];
    }
    key = argv[1];
    keylen = strlen(key);
#else
    if (argc < 2) {
        file = "-";
    } else {
        if (strcmp(argv[1], "--help") == 0) {
            printf("Usage: %s [FILE]\n", argv[0]);
            return 0;
        }
        file = argv[1];
    }
#endif

    if (strcmp(file, "-") == 0) {
        fp = stdin;
        freopen(NULL, "rb", stdin);
    } else if ((fp = fopen(file, "rb")) == NULL) {
        printf("cannot open %s\n", file);
        return 1;
    }

#if HMAC_MODE
    hmac_state S;
    DIGEST_INIT(&S, (uint8_t *) key, keylen);
#else
    state S;
    DIGEST_INIT(&S);
#endif

    while ((c = fread(buf, 1, BUFSIZE, fp)) > 0) {
        DIGEST_UPDATE(&S, buf, c * 8);

        if (feof(fp))
            break;
    }
    if (ferror(fp)) {
        printf("%s: read error\n", file);
        if (fp != stdin)
            fclose(fp);
        return 1;
    }
    if (fp != stdin)
        fclose(fp);

    DIGEST_FINAL(&S, digest);

    for(i = 0; i < DIGEST_SIZE; ++i) {
        printf("%02x", digest[i]);
    }
    printf("\n");

    return 0;
}