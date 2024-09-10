static UBool readLine(UCHARBUF *f, UnicodeString &fileLine, IcuToolErrorCode &errorCode) {
    int32_t lineLength;
    const UChar *line = ucbuf_readline(f, &lineLength, errorCode);
    if(line == NULL || errorCode.isFailure()) { return FALSE; }
    // Strip trailing CR/LF, comments, and spaces.
    const UChar *comment = u_memchr(line, 0x23, lineLength);  // '#'
    if(comment != NULL) {
        lineLength = (int32_t)(comment - line);
    } else {
        while(lineLength > 0 && (line[lineLength - 1] == CARRIAGE_RETURN_CHARACTER || line[lineLength - 1] == LINEFEED_CHARACTER)) { --lineLength; }
    }
    while(lineLength > 0 && u_isspace(line[lineLength - 1])) { --lineLength; }
    fileLine.setTo(FALSE, line, lineLength);
    return TRUE;
}