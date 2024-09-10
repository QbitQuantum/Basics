void DictApplet::sendDelayedCommand()
{
  if (waiting > 100) {   // timeout after ten seconds
    waiting = 0;
    return;
  }

  DCOPClient *client = kapp->dcopClient();
  if (!client->isApplicationRegistered("kdict")) {
    waiting++;
    QTimer::singleShot(100, this, SLOT(sendDelayedCommand()));
    return;
  } else {
    QCStringList list = client->remoteObjects("kdict");
    if (list.findIndex("KDictIface")==-1) {
      waiting++;
      QTimer::singleShot(100, this, SLOT(sendDelayedCommand()));
      return;
    }
  }

  client->send("kdict","default",delayedFunc,delayedData);
  waiting = 0;
}