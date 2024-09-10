// This function has been copied (and modified a little bit) from Scribus (program under GPL license):
// http://docs.scribus.net/devel/util_8cpp-source.html#l00112
QString fileFilters::shortPathName(QString long_path) {
    if ((QSysInfo::WindowsVersion >= QSysInfo::WV_NT) && (QFile::exists(long_path))) {
                QString short_path = long_path;

                const int max_path = 4096;
                WCHAR shortName[max_path];

                QString nativePath = QDir::convertSeparators(long_path);
                int ret = GetShortPathNameW((LPCWSTR) nativePath.utf16(), shortName, max_path);
                if (ret != ERROR_INVALID_PARAMETER && ret < MAX_PATH)
                        short_path = QString::fromUtf16((const ushort*) shortName);

                return short_path;
        } else {
                return long_path;
        }
}