void ChannelsModel::update()
{
  m_availableChannels->clear();
  m_subscribedChannels->clear();
  m_availableChannels = common::DbSession::getInstance().getChannels();
  QSharedPointer<std::vector<QSharedPointer<common::User> > > users=common::DbSession::getInstance().getUsers();
  for (int i = 0; i < users->size(); i++)
  {
    QSharedPointer<loader::User> user = users->at(i).dynamicCast<loader::User>();
    //        WString token = WString(user->getToken());
    if (m_token == user->getToken())
    {
      m_subscribedChannels = user->getSubscribedChannels();
      break;
    }
  }
  int *a = NULL;
  dataChanged().emit(createIndex(0, 0, a),
    createIndex(m_availableChannels->size() - 1,
    AMOUNT_OF_COLUMNS - 1,
    a));
}