int main(int argc, char *argv[])
{
  os_time delay_2ms = { 0, 2000000 };
  DDSEntityManager *mgr = new DDSEntityManager();

  // create domain participant
  char partition_name[] = "Listener example";
  mgr->createParticipant(partition_name);

  //create type
  MsgTypeSupport_var mt = new MsgTypeSupport();
  mgr->registerType(mt.in());

  //create Topic
  char topic_name[] = "ListenerData_Msg";
  mgr->createTopic(topic_name);

  //create Publisher
  mgr->createPublisher();

  // create DataWriter
  mgr->createWriter();

  // Publish Events
  DataWriter_ptr dwriter = mgr->getWriter();
  MsgDataWriter_var listenerWriter = MsgDataWriter::_narrow(dwriter);

  Msg msgInstance; /* Example on Stack */
  msgInstance.userID = 1;
  msgInstance.message = CORBA::string_dup("Hello World");
  cout << "=== [ListenerDataPublisher] writing a message containing :" << endl;
  cout << "    userID  : " << msgInstance.userID << endl;
  cout << "    Message : \"" << msgInstance.message << "\"" << endl;

  ReturnCode_t status = listenerWriter->write(msgInstance, NULL);
  checkStatus(status, "MsgDataWriter::write");
  os_nanoSleep(delay_2ms);

  /* Remove the DataWriters */
  mgr->deleteWriter(listenerWriter.in ());

  /* Remove the Publisher. */
  mgr->deletePublisher();

  /* Remove the Topics. */
  mgr->deleteTopic();

  /* Remove Participant. */
  mgr->deleteParticipant();

  delete mgr;
  return 0;
}