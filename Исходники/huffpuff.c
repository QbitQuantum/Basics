/**
 * Reads strings from a file and computes the frequencies of the characters.
 * @param in File to read from
 * @param freq Where to store computed frequencies
 * @param total_length If not NULL, the total number of characters is stored here
 * @return The resulting list of strings
 */
string_list_t *read_strings(FILE *in, int ignore_case, int *freq,
                            int *total_length, int *string_count)
{
    unsigned char *buf;
    string_list_t *head;
    string_list_t **nextp;
    int max_len;
    int i;
    if (string_count)
        *string_count = 0;

    /* Zap frequency counts. */
    for (i = 0; i < 256; i++)
        freq[i] = 0;

    /* Read strings and count character frequencies as we go. */
    head = NULL;
    nextp = &head;
    max_len = 64;
    buf = (unsigned char *)malloc(max_len);
    if (total_length)
        *total_length = 0;
    while (!feof(in)) {
        /* Read one string (all chars until STRING_SEPARATOR) into temp buffer */
        int c;
        int in_comment = 0;
        i = 0;
        while (((c = fgetc(in)) != -1) && (c != STRING_SEPARATOR)) {
            if (c == '\\') {
                /* Check for line escape */
                int d;
                d = fgetc(in);
                if (d == STRING_SEPARATOR) {
                    continue;
                } else if (d == '#') {
                    c = '#';
                } else {
                    ungetc(d, in);
                }
            } else if ((i == 0) && (c == '#')) {
                in_comment = 1;
	    }
            if (in_comment)
                continue;
            if (i == max_len) {
                /* Allocate larger buffer */
                max_len += 64;
                buf = (unsigned char *)realloc(buf, max_len);
            }
            if (ignore_case && (c >= 'A') && (c <= 'Z'))
                c += 0x20;
            buf[i++] = (unsigned char)c;
            freq[c]++;
        }

        if (i > 0) {
            /* Add string to list */
            string_list_t *lst = (string_list_t *)malloc(sizeof(string_list_t));
            lst->text = (unsigned char *)malloc(i+1);
            lst->huff_data = 0;
            lst->huff_size = 0;
            memcpy(lst->text, buf, i);
            lst->text[i] = 0;
            lst->next = NULL;
            *nextp = lst;
            nextp = &(lst->next);
            if (total_length)
                *total_length = *total_length + i;
            if (string_count)
                *string_count = *string_count + 1;
        }
    }
    free(buf);
    return head;
}