void QAudioEngine::updateListenerOrientation()
{
    QVector3D dir = m_listenerDirection;
    QVector3D up = m_listenerUp;
    dir.normalize();
    up.normalize();
    QVector3D u = up - dir * QVector3D::dotProduct(dir, up);
    u.normalize();
    d->setListenerOrientation(dir, u);
}