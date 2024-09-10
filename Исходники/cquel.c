int cq_fields_to_utf8(char *buf, size_t buflen, size_t fieldc,
        char **fieldnames, bool usequotes)
{
    UChar *buf16;
    UErrorCode status = U_ZERO_ERROR;
    size_t num_left = fieldc;
    int rc = 0;

    if (num_left == 0)
        return 1;

    buf16 = calloc(buflen, sizeof(UChar));
    if (buf16 == NULL)
        return -1;

    for (size_t i = 0; i < fieldc; ++i) {
        UChar *temp = calloc(buflen, sizeof(UChar));
        if (temp == NULL) {
            rc = -2;
            break;
        }

        u_strFromUTF8(temp, buflen, NULL, fieldnames[i], strlen(fieldnames[i]),
                &status);
        if (!U_SUCCESS(status)) {
            rc = 2;
            free(temp);
            break;
        }

        bool isstr = false;
        if (usequotes) {
            for (int32_t j = 0; j < u_strlen(temp); ++j) {
                if (!isdigit(temp[j])) {
                    isstr = true;
                    break;
                }
            }
        }

        if (isstr) u_strcat(buf16, u"'");
        u_strcat(buf16, temp);
        if (isstr) u_strcat(buf16, u"'");
        free(temp);
        if (--num_left > 0) {
            u_strcat(buf16, u",");
        }
    }

    u_strToUTF8(buf, buflen, NULL, buf16, u_strlen(buf16), &status);
    if (!U_SUCCESS(status))
        rc = 3;

    free(buf16);
    return rc;
}