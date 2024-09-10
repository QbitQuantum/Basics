void QPlainTestLogger::enterTestFunction(const char * /*function*/)
{
    if (QTestLog::verboseLevel() >= 1)
        printMessage(QTest::messageType2String(Info), "entering");
}