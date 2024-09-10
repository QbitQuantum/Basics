status_t HTTPStream::receive_header(int *http_status) {
    *http_status = -1;
    mHeaders.clear();

    char line[2048];
    status_t err = receive_line(line, sizeof(line));
    if (err != OK) {
        return err;
    }

    mHeaders.add(AString(kStatusKey), AString(line));

    char *spacePos = strchr(line, ' ');
    if (spacePos == NULL) {
        // Malformed response?
        return UNKNOWN_ERROR;
    }

    char *status_start = spacePos + 1;
    char *status_end = status_start;
    while (isdigit(*status_end)) {
        ++status_end;
    }

    if (status_end == status_start) {
        // Malformed response, status missing?
        return UNKNOWN_ERROR;
    }

    memmove(line, status_start, status_end - status_start);
    line[status_end - status_start] = '\0';

    long tmp = strtol(line, NULL, 10);
    if (tmp < 0 || tmp > 999) {
        return UNKNOWN_ERROR;
    }

    *http_status = (int)tmp;

    for (;;) {
        err = receive_line(line, sizeof(line));
        if (err != OK) {
            return err;
        }

        if (*line == '\0') {
            // Empty line signals the end of the header.
            break;
        }

        // puts(line);

        char *colonPos = strchr(line, ':');
        if (colonPos == NULL) {
            AString key = line;
            key.tolower();

            mHeaders.add(key, AString());
        } else {
            char *end_of_key = colonPos;
            while (end_of_key > line && isspace(end_of_key[-1])) {
                --end_of_key;
            }

            char *start_of_value = colonPos + 1;
            while (isspace(*start_of_value)) {
                ++start_of_value;
            }

            *end_of_key = '\0';

            AString key = line;
            key.tolower();

            mHeaders.add(key, AString(start_of_value));
        }
    }

    return OK;
}