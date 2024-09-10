void object::test<7>()
{ 
    string stmpfile(TOP_BUILD_DIR);
    stmpfile += "/lt.test7.log";   
    const char *filename = stmpfile.c_str();
    unlink(filename);
    Logger *root = alog::Logger::getRootLogger();
    root->setAppender(alog::FileAppender::getAppender(filename));
    Logger *childA = alog::Logger::getLogger("childA");
    Logger *childB = alog::Logger::getLogger("childB");
    childA->log(alog::LOG_LEVEL_DEBUG, "message 1. should NOT output it");
    childB->log(alog::LOG_LEVEL_DEBUG, "message 1. should NOT output it");
    Logger::flushAll();
    ensure("test 7-1 lineCount is right", getFileLineCount(filename) == 0);
    childA->setLevel(LOG_LEVEL_DEBUG);
    childA->log(alog::LOG_LEVEL_DEBUG, "message 2. SHOULD output it");
    childB->log(alog::LOG_LEVEL_DEBUG, "message 2. should NOT output it");
    childB->log(alog::LOG_LEVEL_DEBUG, "message 2. should NOT output it");
    Logger::flushAll();
    ensure("test 7-2 lineCount is right", getFileLineCount(filename) == 1);
    root->setLevel(LOG_LEVEL_TRACE1);
    childB->setLevel(LOG_LEVEL_TRACE2);
    childA->log(alog::LOG_LEVEL_TRACE1, "message 3. should NOT output it");
    childA->log(alog::LOG_LEVEL_TRACE1, "message 3. should NOT output it");
    childB->log(alog::LOG_LEVEL_TRACE1, "message 3. SHOULD output it");
    Logger::flushAll();
    ensure("test 7-3 lineCount is right", getFileLineCount(filename) == 2);
    unlink(filename);
    Logger::shutdown();
}