/*! \brief load groups and their positions
 *
 * Groups are loaded from the settings "groups"
 */
void XletSwitchBoard::reloadGroups()
{
    m_group_list.clear();
    QSettings *settings = b_engine->getSettings();
    settings->beginGroup("groups");
    Group *group;
    int i, size = settings->beginReadArray("groups");
    for (i=0;i<size;i++) {
        settings->setArrayIndex(i);
        group = new Group(this);
        group->setName(settings->value("name").toString());
        group->setRect(settings->value("rect").toRect());
        group->setColor(settings->value("color").value<QColor>());
        m_group_list.insert(i, group);
    }
    settings->endArray();
    settings->endGroup();
}