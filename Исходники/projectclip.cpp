ProjectClip::ProjectClip(const QString &id, QIcon thumb, ClipController *controller, ProjectFolder* parent) :
    AbstractProjectItem(AbstractProjectItem::ClipItem, id, parent)
    , m_abortAudioThumb(false)
    , m_controller(controller)
    , m_thumbsProducer(NULL)
{
    m_clipStatus = StatusReady;
    m_name = m_controller->clipName();
    m_duration = m_controller->getStringDuration();
    m_date = m_controller->date;
    m_description = m_controller->description();
    m_type = m_controller->clipType();
    if (m_type == Audio) {
        m_thumbnail = QIcon::fromTheme(QStringLiteral("audio-x-generic"));
    } else {
        m_thumbnail = thumb;
    }
    // Make sure we have a hash for this clip
    hash();
    setParent(parent);
    connect(this, &ProjectClip::updateJobStatus, this, &ProjectClip::setJobStatus);
    bin()->loadSubClips(id, m_controller->getPropertiesFromPrefix(QStringLiteral("kdenlive:clipzone.")));
    createAudioThumbs();
}