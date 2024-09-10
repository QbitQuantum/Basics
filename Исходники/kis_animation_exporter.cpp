KisImportExportFilter::ConversionStatus KisAnimationExporter::exportAnimation()
{

    if (!m_d->batchMode) {
        emit m_d->document->statusBarMessage(i18n("Export frames"));
        emit m_d->document->sigProgress(0);
        connect(m_d->document, SIGNAL(sigProgressCanceled()), this, SLOT(cancel()));
    }
    m_d->status = KisImportExportFilter::OK;
    m_d->exporting = true;
    m_d->currentFrame = m_d->firstFrame;
    connect(m_d->image->animationInterface(), SIGNAL(sigFrameReady(int)), this, SLOT(frameReadyToCopy(int)), Qt::DirectConnection);
    m_d->image->animationInterface()->requestFrameRegeneration(m_d->currentFrame, m_d->image->bounds());

    QEventLoop loop;
    loop.connect(this, SIGNAL(sigFinished()), SLOT(quit()));
    loop.exec();

    return m_d->status;
}