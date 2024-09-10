void GroupsSync::updateEntryData(Group *entry, Group *newData)
{
  qDebug() << "Updating the " + getType() + " data";
  Q_ASSERT(entry);
  Q_ASSERT(newData);
  entry->copyDataFrom(newData);
  entry->setTimeInfo(newData->timeInfo());
  getSyncObject()->increase(getObjectType(), SOlder(), SLocal());
}