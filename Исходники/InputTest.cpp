TEST(InputTest, SplitterMap)
{
  Network net;
  Region * region1 = net.addRegion("region1", "TestNode", "");
  Region * region2 = net.addRegion("region2", "TestNode", "");

  Dimensions d1;
  d1.push_back(8);
  d1.push_back(4);
  region1->setDimensions(d1);

  //test addLink() indirectly - it is called by Network::link()
  net.link("region1", "region2", "TestFanIn2", "");

  //test initialize(), which is called by net.initialize()
  net.initialize();

  Dimensions d2 = region2->getDimensions();
  Input * in1 = region1->getInput("bottomUpIn");
  Input * in2 = region2->getInput("bottomUpIn");
  Output * out1 = region1->getOutput("bottomUpOut");

  //test isInitialized()
  ASSERT_TRUE(in1->isInitialized());
  ASSERT_TRUE(in2->isInitialized());

  //test evaluateLinks(), in1 already initialized
  ASSERT_EQ(0u, in1->evaluateLinks());
  ASSERT_EQ(0u, in2->evaluateLinks());

  //test prepare
  {    
    //set in2 to all zeroes
    const ArrayBase * ai2 = &(in2->getData());
    Real64* idata = (Real64*)(ai2->getBuffer());
    for (UInt i = 0; i < 64; i++)
      idata[i] = 0;

    //set out1 to all 10's
    const ArrayBase * ao1 = &(out1->getData());
    idata = (Real64*)(ao1->getBuffer());
    for (UInt i = 0; i < 64; i++)
      idata[i] = 10;

    //confirm that in2 is still all zeroes
    ai2 = &(in2->getData());
    idata = (Real64*)(ai2->getBuffer());
    //only test 4 instead of 64 to cut down on number of tests
    for (UInt i = 0; i < 4; i++)
      ASSERT_EQ(0, idata[i]);

    in2->prepare();

    //confirm that in2 is now all 10's
    ai2 = &(in2->getData());
    idata = (Real64*)(ai2->getBuffer());
    //only test 4 instead of 64 to cut down on number of tests
    for (UInt i = 0; i < 4; i++)
      ASSERT_EQ(10, idata[i]);
  }

  net.run(2);

  //test getSplitterMap()
  std::vector< std::vector<size_t> > sm;
  sm = in2->getSplitterMap();
  ASSERT_EQ(8u, sm.size());
  ASSERT_EQ(8u, sm[0].size());
  ASSERT_EQ(16u, sm[0][4]);
  ASSERT_EQ(12u, sm[3][0]);
  ASSERT_EQ(31u, sm[3][7]);

  //test getInputForNode()
  std::vector<Real64> input;
  in2->getInputForNode(0, input);
  ASSERT_EQ(1, input[0]);
  ASSERT_EQ(0, input[1]);
  ASSERT_EQ(8, input[5]);
  ASSERT_EQ(9, input[7]);
  in2->getInputForNode(3, input);
  ASSERT_EQ(1, input[0]);
  ASSERT_EQ(6, input[1]);
  ASSERT_EQ(15, input[7]);

  //test getData()
  const ArrayBase * pa = &(in2->getData());
  ASSERT_EQ(64u, pa->getCount());
  Real64* data = (Real64*)(pa->getBuffer());
  ASSERT_EQ(1, data[0]);
  ASSERT_EQ(0, data[1]);
  ASSERT_EQ(1, data[30]);
  ASSERT_EQ(15, data[31]);
  ASSERT_EQ(31, data[63]);
}