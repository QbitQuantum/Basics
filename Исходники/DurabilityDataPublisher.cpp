int OSPL_MAIN (int argc, char *argv[])
{
  bool automatic = true;
  ReturnCode_t status =  - 1;
  os_time delay = { 20, 0 };
  os_time delay_1s = { 1, 0 };
  char buf[MAX_MSG_LEN];

  if (argc < 4)
  {
    usage();
  }
  if ((strcmp(argv[1], "transient") && strcmp(argv[1], "persistent")) ||
    (strcmp(argv[2], "false") && strcmp(argv[2], "true")))
  {
    usage();
  }
  string durability_kind(argv[1]);
  bool autodispose_unregistered_instances = (strcmp(argv[2], "true") == 0);
  DDSEntityManager mgr (durability_kind, autodispose_unregistered_instances);

  automatic = (strcmp(argv[3], "true") == 0);

  // Wait for the Subscriber (case of transient = true && auto_dispose = true)
  os_nanoSleep(delay_1s);

  // create domain participant
  char partition_name[] = "Durability example";
  mgr.createParticipant(partition_name);

  //create type
  MsgTypeSupport_var mt = new MsgTypeSupport();
  mgr.registerType(mt.in());

  //create Topic
  char topic_name[] = "DurabilityData_Msg";
  mgr.createTopic(topic_name);

  //create Publisher
  mgr.createPublisher();

  // create DataWriter
  mgr.createWriter();

  // Publish Events
  DataWriter_var dwriter = mgr.getWriter();
  MsgDataWriter_var DurabilityDataWriter = MsgDataWriter::_narrow(dwriter.in());

  Msg *instances[10];
  InstanceHandle_t userHandle[10];
  for (int x = 0; x < 10; x++)
  {
    instances[x] = new Msg();
    instances[x]->id = x;
    snprintf(buf, MAX_MSG_LEN, "%d", x);
    userHandle[x] = DurabilityDataWriter->register_instance(*instances[x]);
    instances[x]->content = DDS::string_dup(buf);
    cout << instances[x]->content << endl;
    DurabilityDataWriter->write(*instances[x], userHandle[x]);

  }
  if (! automatic) {
     char c = 0;
     cout << "Enter E to exit" << endl;
     while (c != 'E')
     {
       cin >> c;
     }
  }