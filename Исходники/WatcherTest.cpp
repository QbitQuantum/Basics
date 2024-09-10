TEST(WatcherTest, SampleNetwork)
{
  //generate sample network
  Network n;
  n.addRegion("level1", "TestNode", "");
  n.addRegion("level2", "TestNode", "");
  n.addRegion("level3", "TestNode", "");
  Dimensions d;
  d.push_back(8);
  d.push_back(4);
  n.getRegions().getByName("level1")->setDimensions(d);
  n.link("level1", "level2", "TestFanIn2", "");
  n.link("level2", "level3", "TestFanIn2", "");
  n.initialize();

  //erase any previous contents of testfile
  OFStream o("testfile");
  o.close();
  
  //test creation
  Watcher w("testfile");

  //test uint32Params
  unsigned int id1 = w.watchParam("level1", "uint32Param");
  ASSERT_EQ(id1, (unsigned int)1);
  //test uint64Params
  unsigned int id2 = w.watchParam("level1", "uint64Param");
  ASSERT_EQ(id2, (unsigned int)2);
  //test int32Params
  w.watchParam("level1", "int32Param");
  //test int64Params
  w.watchParam("level1", "int64Param");
  //test real32Params
  w.watchParam("level1", "real32Param");
  //test real64Params
  w.watchParam("level1", "real64Param");
  //test stringParams
  w.watchParam("level1", "stringParam");
  //test unclonedParams
  w.watchParam("level1", "unclonedParam", 0);
  w.watchParam("level1", "unclonedParam", 1);
  
  //test attachToNetwork()
  w.attachToNetwork(n);

  //test two simultaneous Watchers on the same network with different files
  Watcher* w2 = new Watcher("testfile2");

  //test int64ArrayParam
  w2->watchParam("level1", "int64ArrayParam");
  //test real32ArrayParam
  w2->watchParam("level1", "real32ArrayParam");
  //test output
  w2->watchOutput("level1", "bottomUpOut");
  //test int64ArrayParam, sparse = false
  w2->watchParam("level1", "int64ArrayParam", -1, false);

  w2->attachToNetwork(n);

  //set one of the uncloned parameters to 1 instead of 0
  //n.getRegions().getByName("level1")->getNodeAtIndex(1).setParameterUInt32("unclonedParam", (UInt32)1);
  //n.run(3);
  //see if Watcher notices change in parameter values after 3 iterations
  n.getRegions().getByName("level1")->setParameterUInt64("uint64Param", (UInt64)66);
  n.run(3);

  //test flushFile() - this should produce output
  w.flushFile();

  //test closeFile()
  w.closeFile();

  //test to make sure data is flushed when Watcher is deleted
  delete w2;
}