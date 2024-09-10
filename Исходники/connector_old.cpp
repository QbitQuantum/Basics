void ConnectorOld::stringParser(QByteArray recv)
{
  QString recvStr = codec->toUnicode(recv);
  QChar category = recvStr[0];                        // First symbol of string
  QStringList message = recvStr.mid(1).split("\t");   // Remove first symbol & splitting
  QString cmd;
  switch (category.toAscii())
  {
  case 'R':       // Authentification request
    qDebug() << "CONN :: Auth_req:" << message;
    emit authRequestRecv(message.at(0));
    break;
  case 'b':       // Information
    qDebug() << "CONN :: Inform:" << message;
    emit infoMessage(message.at(0));
    // Verify for success auth string
    if (message.at(0).split(" ").count() == 7)
      if (message.at(0).split(" ").at(2).at(8) == ',')
        emit authSuccess();
    break;
  case 'd':       // Board
    cmd = message.at(0);
    if (cmd == "channels")  // Receved channel list
    {
      qDebug() << "CONN :: Board: channels recv";
      message.pop_front();    // Remove command from message
      emit boardChannelsRecv(parseBoardChannels(message.join("\t")));
    }
    else
    {
      if (cmd == "new")  // New messages
      {
        qDebug() << "CONN :: Board: new messages avaible";
        emit boardNewMessages();
      }
      else
      {
        if (cmd == "skins")
        {
          qDebug() << "CONN :: Board: \"skins\" cmd recv";
        }
        else
        {
          if (cmd == "admin")
          {
            qDebug() << "CONN :: Board: \"admin\" cmd recv";
          }
          else
          {
            qDebug() << "CONN :: Board: messages recv";
            emit boardMessagesRecv(parseBoardMessages(message.join("\t")));
          }
        }
      }
    }
//    qDebug() << "DBoard :: " << message;
    break;
  case 'c':       // Chat
    cmd = message.at(0);
    message.pop_front();    // Remove command from message
    if (cmd == "main")
    {
      qDebug() << "CONN :: Chat: channel message recv";
      emit chatPublicMessage(message.at(0),
                             getUserIdByName(message.at(0), message.at(2)),
                             message.at(3));
    }
    else
    {
      if (cmd == "enter")
      {
        QString channelId = message.at(0);
        if (QHostAddress().setAddress(channelId))
        {
          qDebug() << "CONN :: Host entered"
                   << message.at(2) << "@" << channelId;
        }
        else
        {
          qDebug() << "CONN :: Chat: new user entered" << message.at(3);
          emit chatUserEnter(channelId, parseEnteredUser(message));
        }
      }
      else
      {
        if (cmd == "leave")
        {
          QString channelId = message.at(0);
          if (QHostAddress().setAddress(channelId))
          {
            qDebug() << "CONN :: Host leave"
                     << message.at(2) << "@" << channelId;
          }
          else
          {
            shared_ptr<ChatChannel> ch =
                getChatInstance()->getChannel(channelId);
            bool online; // Verify for user connect state
            ch->getUser(message.at(2), &online);
            if (online)
            {
              qDebug() << "CONN :: Chat: user leave" << message.at(3);
              emit chatUserLeave(channelId, message.at(2));
            }
          }
        }
        else
        {
          if (cmd == "private")
          {
            qDebug() << "CONN :: Chat: new private message";
            emit chatPrivateMessage(parseChatPrivate(message));
          }
          else
          {
            if (cmd == "infoGet")
            {
              qDebug() << "CONN :: Chat: \"infoGet\" cmd recv";
            }
            else
            {
              if (cmd == "channels")
              {
                qDebug() << "CONN :: Chat: channels recv";
                emit chatChannelsRecv(parseChatChannels(message.join("\t")));
              }
              else
              {
                if (cmd == "userlist")
                {
                  qDebug() << "CONN :: Chat: userlist recv";
                  emit chatUsersRecv(message.at(0), parseChatUsers(message));
                }
                else
                {
                  if (cmd == "privateresived")
                  {
                    emit chatPrivateDelivered(
                          message.at(0), message.at(1), message.at(2));
                  }
                  else
                    qDebug() << "CONN ::" << cmd << message;
                }
              }
            }
          }
        }
      }
    }
//    qDebug() << "Chat   :: " << message;
    break;
  default:       // Uncategorised
    qDebug() << "Unctg  :: " << recvStr;
  }
}