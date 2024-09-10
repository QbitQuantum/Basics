Log::Log(const Char8 *fileName, LogLevel logLevel) :
    std::ostream  (_nilbufP == NULL ?
                   _nilbufP = new Log::nilbuf() : _nilbufP),
    _logType       (LOG_FILE      ),
    _logLevel      (logLevel      ),
    _fileStream    (              ),
    _logBuf        (              ),
    _headerElem    (             0),
    _moduleHandling(LOG_MODULE_ALL),
    _moduleList    (              ),
    _refTime       (             0)
{
    if(_nilstreamP == NULL)
        _nilstreamP = new std::ostream(_nilbufP);

    for(UInt32 i = 0; i < sizeof(_streamVec)/sizeof(LogOStream *); i++)
    {
#ifdef OSG_HAS_NILBUF
        _streamVec[i] = new LogOStream(_nilbufP);
#else
        _streamVec[i] = new LogOStream(_nilStreamP->rdbuf());
#endif
    }

    _refTime = getSystemTime();

    setHeaderElem(LOG_TYPE_HEADER);
    setLogFile   (fileName);
    setLogLevel  (logLevel);
}