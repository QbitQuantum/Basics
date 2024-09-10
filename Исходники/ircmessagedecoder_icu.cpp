QByteArray IrcMessageDecoder::codecForData(const QByteArray &data) const
{
    QByteArray encoding;
    UErrorCode status = U_ZERO_ERROR;
    if (d.detector) {
        ucsdet_setText(UCSD(d.detector), data.constData(), data.length(), &status);
        if (!U_FAILURE(status)) {
            const UCharsetMatch* match = ucsdet_detect(UCSD(d.detector), &status);
            if (match && !U_FAILURE(status))
                encoding = ucsdet_getName(match, &status);
        }
    }
    if (U_FAILURE(status))
        qWarning("IrcMessageDecoder::codecForData() failed: %s", u_errorName(status));
    return encoding;
}