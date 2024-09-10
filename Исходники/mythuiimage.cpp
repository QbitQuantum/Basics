/**
*  \brief Load an image
*/
MythImage *MythUIImage::LoadImage(
    MythImageReader &imageReader, const QString &imFile,
    QSize bForceSize, int cacheMode)
{
    QString filename = imFile;

    m_loadingImagesLock.lock();

    // Check to see if the image is being loaded by us in another thread
    if ((m_loadingImages.contains(filename)) &&
        (m_loadingImages[filename] == this))
    {
        VERBOSE(VB_GUI|VB_FILE|VB_EXTRA, LOC + QString(
                    "MythUIImage::LoadImage(%1), this "
                    "file is already being loaded by this same MythUIImage in "
                    "another thread.").arg(filename));
        m_loadingImagesLock.unlock();
        return NULL;
    }

    // Check to see if the exact same image is being loaded anywhere else
    while (m_loadingImages.contains(filename))
        m_loadingImagesCond.wait(&m_loadingImagesLock);

    m_loadingImages[filename] = this;
    m_loadingImagesLock.unlock();

    VERBOSE(VB_GUI|VB_FILE, LOC + QString("LoadImage(%2) Object %3")
            .arg(filename).arg(objectName()));

    MythImage *image = NULL;

    bool bForceResize = false;
    bool bFoundInCache = false;

    QString imagelabel;

    int w = -1;
    int h = -1;

    if (!bForceSize.isNull())
    {
        if (bForceSize.width() != -1)
            w = bForceSize.width();

        if (bForceSize.height() != -1)
            h = bForceSize.height();

        bForceResize = true;
    }

    imagelabel = GenImageLabel(filename, w, h);

    if (!imageReader.supportsAnimation())
    {
        image = GetMythUI()->LoadCacheImage(
            filename, imagelabel, GetPainter(), (ImageCacheMode) cacheMode);
    }

    if (image)
    {
        image->UpRef();

        VERBOSE(VB_GUI|VB_FILE, LOC +
                QString("LoadImage found in cache :%1: RefCount = %2")
                .arg(imagelabel).arg(image->RefCount()));

        if (m_isReflected)
            image->setIsReflected(true);

        bFoundInCache = true;
    }
    else
    {
        VERBOSE(VB_GUI|VB_FILE, LOC +
                QString("LoadImage Not Found in cache. "
                        "Loading Directly :%1:").arg(filename));

        image = GetPainter()->GetFormatImage();
        image->UpRef();
        bool ok = false;
        if (imageReader.supportsAnimation())
            ok = image->Load(imageReader);
        else
            ok = image->Load(filename);

        if (!ok)
        {
            image->DownRef();

            m_loadingImagesLock.lock();
            m_loadingImages.remove(filename);
            m_loadingImagesCond.wakeAll();
            m_loadingImagesLock.unlock();

            return NULL;
        }
    }

    if (!bFoundInCache)
    {
        if (bForceResize)
            image->Resize(QSize(w, h), m_preserveAspect);

        if (m_isMasked)
        {
            QRect imageArea = image->rect();
            QRect maskArea = m_maskImage->rect();

            // Crop the mask to the image
            int x = 0;
            int y = 0;
            if (maskArea.width() > imageArea.width())
                x = (maskArea.width() - imageArea.width()) / 2;
            if (maskArea.height() > imageArea.height())
                y = (maskArea.height() - imageArea.height()) / 2;

            if (x > 0 || y > 0)
                imageArea.translate(x,y);
            d->m_UpdateLock.lockForWrite();
            QImage mask = m_maskImage->copy(imageArea);
            d->m_UpdateLock.unlock();
            image->setAlphaChannel(mask.alphaChannel());
        }

        if (m_isReflected)
            image->Reflect(m_reflectAxis, m_reflectShear, m_reflectScale,
                        m_reflectLength, m_reflectSpacing);

        if (m_isGreyscale)
            image->ToGreyscale();

        if (!imageReader.supportsAnimation())
            GetMythUI()->CacheImage(imagelabel, image);
    }

    if (image->isNull())
    {
        VERBOSE(VB_GUI|VB_FILE, LOC + QString("LoadImage Image is NULL :%1:")
                .arg(filename));

        image->DownRef();
        Reset();

        m_loadingImagesLock.lock();
        m_loadingImages.remove(filename);
        m_loadingImagesCond.wakeAll();
        m_loadingImagesLock.unlock();

        return NULL;
    }

    image->SetChanged();

    m_loadingImagesLock.lock();
    m_loadingImages.remove(filename);
    m_loadingImagesCond.wakeAll();
    m_loadingImagesLock.unlock();

    return image;
}