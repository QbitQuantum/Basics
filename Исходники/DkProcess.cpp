bool DkResizeBatch::prepareProperties(const QSize& imgSize, QSize& size, float& scaleFactor, QStringList& logStrings) const {

    float sf = 1.0f;
    QSize normalizedSize = imgSize;

    if (mMode == mode_default) {
        scaleFactor = this->mScaleFactor;
        return true;
    }
    else if (mMode == mode_long_side) {

        if (imgSize.width() < imgSize.height())
            normalizedSize.transpose();
    }
    else if (mMode == mode_short_side) {

        if (imgSize.width() > imgSize.height())
            normalizedSize.transpose();
    }
    else if (mMode == mode_height)
        normalizedSize.transpose();

    sf = this->mScaleFactor/normalizedSize.width();

    if (sf > 1.0 && this->mProperty == prop_decrease_only) {

        logStrings.append(QObject::tr("%1 I need to increase the image, but the option is set to decrease only -> skipping.").arg(name()));
        return false;
    }
    else if (sf < 1.0f && this->mProperty == prop_increase_only) {
        logStrings.append(QObject::tr("%1 I need to decrease the image, but the option is set to increase only -> skipping.").arg(name()));
        return false;
    }
    else if (sf == 1.0f) {
        logStrings.append(QObject::tr("%1 image size matches scale factor -> skipping.").arg(name()));
        return false;
    }

    size.setWidth(qRound(this->mScaleFactor));
    size.setHeight(qRound(sf*normalizedSize.height()));

    if (normalizedSize != imgSize)
        size.transpose();

    return true;
}