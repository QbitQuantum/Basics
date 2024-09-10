bool QImageLoader::save(const QString& filePath, DImgLoaderObserver* const observer)
{
    QVariant qualityAttr = imageGetAttribute(QLatin1String("quality"));
    int quality          = qualityAttr.isValid() ? qualityAttr.toInt() : 90;

    if (quality < 0)
    {
        quality = 90;
    }

    if (quality > 100)
    {
        quality = 100;
    }

    QVariant formatAttr = imageGetAttribute(QLatin1String("format"));
    QByteArray format   = formatAttr.toByteArray();
    QImage image        = m_image->copyQImage();

    if (observer)
    {
        observer->progressInfo(m_image, 0.1F);
    }

    // Saving is opaque to us. No support for stopping from observer,
    // progress info are only pseudo values
    bool success = image.save(filePath, format.toUpper().constData(), quality);

    if (observer && success)
    {
        observer->progressInfo(m_image, 1.0F);
    }

    imageSetAttribute(QLatin1String("format"), format.toUpper());

    saveMetadata(filePath);

    return success;
}