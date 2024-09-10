bool TraceSession::Process()
{
    _status = ProcessTrace(&_hTrace, 1, NULL, NULL);
    return (_status == ERROR_SUCCESS);
}