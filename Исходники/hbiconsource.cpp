bool HbIconSource::canKeepOpen() const
{
#ifdef Q_OS_SYMBIAN
    if (mFullFilename.isEmpty()) {
        return false;
    } else {
        QChar driveLetter = mFullFilename.at(0);
        return driveLetter.toUpper() == 'Z';
    }
#else
    return false;
#endif
}