static log4cxx::Logger* initLogger(const char* logFile, const char* logLevel)
{
    static char s_parttern[] = "%d [%p] [%c] %m";
    using namespace LOG4CXX_NS;    
    Logger *pLogger = Logger::getRootLogger() ;
    Appender * appender
    = Appender::getAppender( logFile, "appender.ps" );
    Layout* layout = Layout::getLayout( "patternErrLog", "layout.pattern" );
    layout->setUData( s_parttern );
    appender->setLayout( layout );
    log4cxx::Level::setDefaultLevel(Level::toInt(logLevel));
    pLogger->setLevel( logLevel );
    pLogger->setAppender( appender );
    return pLogger;
}