void ClientSideResponse::ReadResponse(XRef<XStreamIO> socket)
{
READ_BEGIN:

    list<XString> requestLines;

    {
        char lineBuf[MAX_HEADER_LINE+1];
        memset(lineBuf, 0, MAX_HEADER_LINE+1);

        {
            char* writer = &lineBuf[0];
            _CleanSocket(socket, &writer);

            // Get initial header line
            _ReadHeaderLine(socket, writer, true);
        }

        _initialLine = XString(lineBuf).StripEOL();

        /// Now, read the rest of the header lines...
        do
        {
            memset(lineBuf, 0, MAX_HEADER_LINE);
            _ReadHeaderLine(socket, lineBuf, false);

        } while(!_AddLine(requestLines, lineBuf));
    }

    /// Now, populate our header hash...

    _headerParts.Clear();

    const vector<XString> initialLineParts = _initialLine.Split(' ');

    if(initialLineParts.size() <= 2)
        X_STHROW(WebbyException, ("HTTP request initial line doesn't have enough parts."));

    _AddHeader(XString("http_version"), initialLineParts[0]);
    _AddHeader(XString("response_code"), initialLineParts[1]);

    // After response code, we have a message, usually either "OK" or "Not Found", this code appends all the initial line
    // pieces after the first two parts so that we end up with a complete "message".

    XString msg = initialLineParts[2];

    for(int i = 3, e = initialLineParts.size(); i < e; ++i)
    {
        msg += " ";
        msg += initialLineParts[i];
    }

    _AddHeader(XString("message"), msg);

    if(const list<XString>* found = _headerParts.Find("response_code"))
    {
        _statusCode = found->front().ToInt();
        if(kWebbyResponseOk <= _statusCode && _statusCode < kWebbyResponseMultipleChoices)
            _success = true;
    }

    // Handling a "100 continue" initial line, as per http 1.1 spec; we basically
    // just restart... A 100 continue means another complete header and body follows...
    if(msg.ToLower().Contains ("continue"))
        goto READ_BEGIN;

    _ProcessRequestLines(requestLines);
    _ProcessBody(socket);
}