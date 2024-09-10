QCollatorSortKey QCollator::sortKey(const QString &string) const
{
    if (d->dirty)
        d->init();

#ifndef USE_COMPARESTRINGEX
    int size = LCMapStringW(d->localeID, LCMAP_SORTKEY | d->collator,
                           reinterpret_cast<const wchar_t*>(string.constData()), string.size(),
                           0, 0);
#else
    int size = LCMapStringEx(LPCWSTR(d->localeName.utf16()), LCMAP_SORTKEY | d->collator,
                           reinterpret_cast<LPCWSTR>(string.constData()), string.size(),
                           0, 0, NULL, NULL, 0);
#endif
    QString ret(size, Qt::Uninitialized);
#ifndef USE_COMPARESTRINGEX
    int finalSize = LCMapStringW(d->localeID, LCMAP_SORTKEY | d->collator,
                           reinterpret_cast<const wchar_t*>(string.constData()), string.size(),
                           reinterpret_cast<wchar_t*>(ret.data()), ret.size());
#else
    int finalSize = LCMapStringEx(LPCWSTR(d->localeName.utf16()), LCMAP_SORTKEY | d->collator,
                           reinterpret_cast<LPCWSTR>(string.constData()), string.size(),
                           reinterpret_cast<LPWSTR>(ret.data()), ret.size(),
                           NULL, NULL, 0);
#endif
    if (finalSize == 0) {
        qWarning() << "there were problems when generating the ::sortKey by LCMapStringW with error:" << GetLastError();
    }
    return QCollatorSortKey(new QCollatorSortKeyPrivate(ret));
}