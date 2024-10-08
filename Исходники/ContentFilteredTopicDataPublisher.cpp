int main(int argc, char *argv[])
{
  os_time delay_100ms = { 0, 100000000 };
  DDSEntityManager *mgr = new DDSEntityManager();

  // create domain participant
  char partition_name[] = "ContentFilteredTopic example";
  mgr->createParticipant(partition_name);

  StockTypeSupport_var st = new StockTypeSupport();
  mgr->registerType(st.in());

  //create Topic
  char topic_name[] = "StockTrackerExclusive";
  mgr->createTopic(topic_name);

  //create Publisher
  mgr->createPublisher();

  // create DataWriter
  mgr->createWriter();
  DataWriter_ptr dWriter = mgr->getWriter();
  StockDataWriter_var ContentFilteredTopicDataWriter = StockDataWriter::_narrow(dWriter);

  Stock geQuote;
  Stock msftQuote;

  geQuote.ticker = CORBA::string_dup("GE");
  geQuote.price = 12.00f;
  msftQuote.ticker = CORBA::string_dup("MSFT");
  msftQuote.price = 25.00f;


  InstanceHandle_t geHandle = ContentFilteredTopicDataWriter->register_instance(geQuote);
  InstanceHandle_t msftHandle = ContentFilteredTopicDataWriter->register_instance(msftQuote);

  // Publish Events
  ReturnCode_t status;
  // update ContentFilteredTopicData price every second
  for (int x = 0; x < 20; x++)
  {
    geQuote.price = geQuote.price + 0.5;
    msftQuote.price = msftQuote.price + 1.5;
    printf("=== [ContentFilteredTopicDataPublisher] sends 2 stockQuotes : (GE, %.1f) (MSFT, %.1f)\n", geQuote.price, msftQuote.price);
    status = ContentFilteredTopicDataWriter->write(geQuote, geHandle);
    checkStatus(status, "StockDataWriter::write");
    status = ContentFilteredTopicDataWriter->write(msftQuote, msftHandle);
    checkStatus(status, "StockDataWriter::write");
    os_nanoSleep(delay_100ms);
  }
  // signal to terminate
  geQuote.price =  - 1;
  msftQuote.price =  - 1;
  ContentFilteredTopicDataWriter->write(geQuote, geHandle);
  ContentFilteredTopicDataWriter->write(msftQuote, msftHandle);
  cout << "Market Closed" << endl;

  /* Unregister the instances */
  ContentFilteredTopicDataWriter->unregister_instance(geQuote, geHandle);
  ContentFilteredTopicDataWriter->unregister_instance(msftQuote, msftHandle);

  /* Remove the DataWriters */
  mgr->deleteWriter(ContentFilteredTopicDataWriter.in ());

  /* Remove the Publisher. */
  mgr->deletePublisher();

  /* Remove the Topics. */
  mgr->deleteTopic();

  /* Remove Participant. */
  mgr->deleteParticipant();

  delete mgr;
  return 0;
}