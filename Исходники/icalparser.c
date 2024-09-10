/**
 * Get a single property line, from the property name through the
 * final new line, and include any continuation lines
 */
char *icalparser_get_line(icalparser *parser,
                          icalparser_line_gen_func line_gen_func)
{
    char *line;
    char *line_p;
    size_t buf_size = parser->tmp_buf_size;

    line_p = line = icalmemory_new_buffer(buf_size);
    line[0] = '\0';

    /* Read lines by calling line_gen_func and putting the data into
       parser->temp. If the line is a continuation line ( begins with a
       space after a newline ) then append the data onto line and read
       again. Otherwise, exit the loop. */

    while (1) {

        /* The first part of the loop deals with the temp buffer,
           which was read on he last pass through the loop. The
           routine is split like this because it has to read lone line
           ahead to determine if a line is a continuation line. */

        /* The tmp buffer is not clear, so transfer the data in it to the
           output. This may be left over from a previous call */
        if (parser->temp[0] != '\0') {

            /* If the last position in the temp buffer is occupied,
               mark the buffer as full. The means we will do another
               read later, because the line is not finished */
            if (parser->temp[parser->tmp_buf_size - 1] == 0 &&
                parser->temp[parser->tmp_buf_size - 2] != '\n' &&
                parser->temp[parser->tmp_buf_size - 2] != 0) {
                parser->buffer_full = 1;
            } else {
                parser->buffer_full = 0;
            }

            /* Copy the temp to the output and clear the temp buffer. */
            if (parser->continuation_line == 1) {
                /* back up the pointer to erase the continuation characters */
                parser->continuation_line = 0;
                line_p--;

                if (*(line_p - 1) == '\r') {
                    line_p--;
                }

                /* copy one space up to eliminate the leading space */
                icalmemory_append_string(&line, &line_p, &buf_size, parser->temp + 1);

            } else {
                icalmemory_append_string(&line, &line_p, &buf_size, parser->temp);
            }

            parser->temp[0] = '\0';
        }

        parser->temp[parser->tmp_buf_size - 1] = 1;     /* Mark end of buffer */

        /****** Here is where the routine gets string data ******************/
        if ((*line_gen_func) (parser->temp, parser->tmp_buf_size, parser->line_gen_data)
            == 0) {     /* Get more data */

            /* If the first position is clear, it means we didn't get
               any more data from the last call to line_ge_func */
            if (parser->temp[0] == '\0') {

                if (line[0] != '\0') {
                    /* There is data in the output, so fall trhough and process it */
                    break;
                } else {
                    /* No data in output; return and signal that there
                       is no more input */
                    free(line);
                    return 0;
                }
            }
        }

        /* If the output line ends in a '\n' and the temp buffer
           begins with a ' ' or tab, then the buffer holds a continuation
           line, so keep reading.  RFC 5545, section 3.1 */

        if (line_p > line + 1 && *(line_p - 1) == '\n'
            && (parser->temp[0] == ' ' || parser->temp[0] == '\t')) {

            parser->continuation_line = 1;

        } else if (parser->buffer_full == 1) {

            /* The buffer was filled on the last read, so read again */

        } else {

            /* Looks like the end of this content line, so break */
            break;
        }
    }

    /* Erase the final newline and/or carriage return */
    if (line_p > line + 1 && *(line_p - 1) == '\n') {
        *(line_p - 1) = '\0';
        if (*(line_p - 2) == '\r') {
            *(line_p - 2) = '\0';
        }

    } else {
        *(line_p) = '\0';
    }

    while ((*line_p == '\0' || iswspace((wint_t) * line_p)) && line_p > line) {
        *line_p = '\0';
        line_p--;
    }

    return line;
}