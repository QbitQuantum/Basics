Evr9VideoWindowControl::Evr9VideoWindowControl(QObject *parent)
    : QVideoWindowControl(parent)
    , m_windowId(0)
    , m_dirtyValues(0)
    , m_aspectRatioMode(Qt::KeepAspectRatio)
    , m_brightness(0)
    , m_contrast(0)
    , m_hue(0)
    , m_saturation(0)
    , m_fullScreen(false)
    , m_currentActivate(0)
    , m_evrSink(0)
    , m_displayControl(0)
{
    if (FAILED(MFCreateVideoRendererActivate(0, &m_currentActivate))) {
        qWarning() << "Failed to create evr video renderer activate!";
        return;
    }
    if (FAILED(m_currentActivate->ActivateObject(IID_IMFMediaSink, (LPVOID*)(&m_evrSink)))) {
        qWarning() << "Failed to activate evr media sink!";
        return;
    }
    if (FAILED(MFGetService(m_evrSink, MR_VIDEO_RENDER_SERVICE, IID_PPV_ARGS(&m_displayControl)))) {
        qWarning() << "Failed to get display control from evr media sink!";
        return;
    }
    if (FAILED(MFGetService(m_evrSink,  MR_VIDEO_MIXER_SERVICE, IID_PPV_ARGS(&m_processor)))) {
        qWarning() << "Failed to get video processor from evr media sink!";
        return;
    }
}