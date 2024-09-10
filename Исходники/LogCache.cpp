void LogCacheExt::onMessage(const LogMessage& msg) {
    if (!filter.isEmpty() && !filter.matches(msg)) {
        return;
    }
    if (consoleEnabled){
        QByteArray ba = msg.text.toLocal8Bit();
        char* buf = ba.data();
#ifdef Q_OS_WIN32
        // a bit of magic to workaround Windows console encoding issues
        CharToOemA(buf,buf);
#endif
        printf("%s\n", buf);
    }

    if (fileEnabled) {
        QByteArray ba = msg.text.toLocal8Bit();
        char* buf = ba.data();
        file.write(buf, ba.length());
        file.write("\n", 1);
        file.flush();
    }

    LogCache::onMessage(msg);
}