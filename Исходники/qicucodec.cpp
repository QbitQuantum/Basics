QTextCodec *QIcuCodec::defaultCodecUnlocked()
{
    QCoreGlobalData *globalData = QCoreGlobalData::instance();
    if (!globalData)
        return 0;
    QTextCodec *c = globalData->codecForLocale.loadAcquire();
    if (c)
        return c;

#if defined(QT_LOCALE_IS_UTF8)
    const char *name = "UTF-8";
#else
    const char *name = ucnv_getDefaultName();
#endif
    c = codecForNameUnlocked(name);
    globalData->codecForLocale.storeRelease(c);
    return c;
}