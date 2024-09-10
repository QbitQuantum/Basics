void QCharsetDetector::enableInputFilter(bool enable)
{
    Q_D(QCharsetDetector);
    clearError();
    ucsdet_enableInputFilter(d->_uCharsetDetector, UBool(enable));
}