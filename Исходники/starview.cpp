void HostItem::updateHalos()
{
    int count = 1;

    QMap<Job,QGraphicsEllipseItem*>::Iterator it;
    for(it = m_jobHalos.begin(); it != m_jobHalos.end(); ++it) {
        QGraphicsEllipseItem *halo = it.value();
        halo->setRect(halo->x() - 5 - count * 3,
                      halo->y() - 5 - count * 3,
                      m_baseWidth + count * 6,
                      m_baseHeight + count * 6);
        halo->setBrush(m_hostInfoManager->hostColor(it.key().client()));
        halo->setPen(Qt::NoPen);
        ++count;
    }
}