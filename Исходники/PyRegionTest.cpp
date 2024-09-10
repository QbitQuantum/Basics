int realmain(bool leakTest)
{
  // verbose == true turns on extra output that is useful for
  // debugging the test (e.g. when the TestNode compute() 
  // algorithm changes)


  std::cout << "Creating network..." << std::endl;
  Network n;
  
  std::cout << "Region count is " << n.getRegions().getCount() << "" << std::endl;

  std::cout << "Adding a PyNode region..." << std::endl;
  Network::registerPyRegion("nupic.regions.TestNode", "TestNode");
  Region* level2 = n.addRegion("level2", "py.TestNode", "{int32Param: 444}");

  std::cout << "Region count is " << n.getRegions().getCount() << "" << std::endl;
  std::cout << "Node type: " << level2->getType() << "" << std::endl;
  std::cout << "Nodespec is:\n"  << level2->getSpec()->toString() << "" << std::endl;
  
  Real64 rval;
  std::string int64Param("int64Param");
  std::string real64Param("real64Param");

  // get the value of intArrayParam after the setParameter call.

  // --- Test getParameterReal64 of a PyNode
  rval = level2->getParameterReal64("real64Param");
  NTA_CHECK(rval == 64.1); 
  std::cout << "level2 getParameterReal64() returned: " << rval << std::endl;

  // --- Test setParameterReal64 of a PyNode
  level2->setParameterReal64("real64Param", 77.7);
  rval = level2->getParameterReal64("real64Param");
  NTA_CHECK(rval == 77.7); 

  // should fail because network has not been initialized
  SHOULDFAIL(n.run(1));

  // should fail because network can't be initialized
  SHOULDFAIL (n.initialize() );

  std::cout << "Setting dimensions of level1..." << std::endl;
  Dimensions d;
  d.push_back(4);
  d.push_back(4);


  std::cout << "Setting dimensions of level2..." << std::endl;
  level2->setDimensions(d);

  std::cout << "Initializing again..." << std::endl;
  n.initialize();

  testExceptionBug();
  testPynodeInputOutputAccess(level2);
  testPynodeArrayParameters(level2);
  testPynodeLinking();
  if (!leakTest)
  {
    //testNuPIC1x();
    //testPynode1xLinking();
  }

  std::cout << "Done -- all tests passed" << std::endl;

  return 0;
}