void MCharsetDetector::setText(const QByteArray &ba)
{
    Q_D(MCharsetDetector);
    clearError();
    d->_ba = ba;
    d->_baExtended = ba;
    if (!ba.isEmpty())
        while (d->_baExtended.size() < 50)
            d->_baExtended += d->_ba;
    ucsdet_setText(d->_uCharsetDetector, d->_baExtended.constData(), int32_t(-1), &(d->_status));
    if(hasError())
        qWarning() << __PRETTY_FUNCTION__ << errorString();
}