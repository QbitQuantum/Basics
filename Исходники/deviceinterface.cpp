void DeviceInterface::connectMediaPlayer()
{
    const QVariantMap &properties = qdbus_cast<QVariantMap>(Object::property(QStringLiteral("MediaPlayer")));
    const QDBusObjectPath &path = properties.value(QStringLiteral("Path")).value<QDBusObjectPath>();
    QVariantMap props = properties;
    props.remove(QStringLiteral("Path"));

    MediaPlayerObject *mediaPlayerObj = new MediaPlayerObject(path);
    m_mediaPlayer = new MediaPlayerInterface(path, props, mediaPlayerObj);

    ObjectManager *manager = ObjectManager::self();
    manager->addObject(m_mediaPlayer);
    manager->addAutoDeleteObject(mediaPlayerObj);

    m_connectedUuids.append(MediaPlayerUuid);
}