void testPynodeLinking()
{
  Network net = Network();

  Region * region1 = net.addRegion("region1", "TestNode", "");
  Region * region2 = net.addRegion("region2", "py.TestNode", "");
  std::cout << "Linking region 1 to region 2" << std::endl;
  net.link("region1", "region2", "TestFanIn2", "");

  std::cout << "Setting region1 dims to (6,4)" << std::endl;
  Dimensions r1dims;
  r1dims.push_back(6);
  r1dims.push_back(4);
  region1->setDimensions(r1dims);

  std::cout << "Initializing network..." << std::endl;
  net.initialize();

  const Dimensions& r2dims = region2->getDimensions();
  NTA_CHECK(r2dims.size() == 2) << " actual dims: " << r2dims.toString();
  NTA_CHECK(r2dims[0] == 3) << " actual dims: " << r2dims.toString();
  NTA_CHECK(r2dims[1] == 2) << " actual dims: " << r2dims.toString();
  
  ArrayRef r1OutputArray = region1->getOutputData("bottomUpOut");

  region1->compute();

  std::cout << "Checking region1 output after first iteration..." << std::endl;
  Real64 *buffer = (Real64*) r1OutputArray.getBuffer();

  for (size_t i = 0; i < r1OutputArray.getCount(); i++)
  {
    if (verbose)
      std::cout << "  " << i << "    " << buffer[i] << "" << std::endl;
    if (i%2 == 0)
      NTA_CHECK(buffer[i] == 0);
    else
      NTA_CHECK(buffer[i] == (i-1)/2);
  }

  region2->prepareInputs();
  ArrayRef r2InputArray = region2->getInputData("bottomUpIn");
  std::cout << "Region 2 input after first iteration:" << std::endl;
  Real64 *buffer2 = (Real64*) r2InputArray.getBuffer();
  NTA_CHECK(buffer != buffer2);

  for (size_t i = 0; i < r2InputArray.getCount(); i++)
  {
    if (verbose)
      std::cout << "  " << i << "    " << buffer2[i] << "" << std::endl;

    if (i%2 == 0)
      NTA_CHECK(buffer[i] == 0);
    else
      NTA_CHECK(buffer[i] == (i-1)/2);
  }

  std::cout << "Region 2 input by node" << std::endl;
  std::vector<Real64> r2NodeInput;

  for (size_t node = 0; node < 6; node++)
  {
    region2->getInput("bottomUpIn")->getInputForNode(node, r2NodeInput);
    if (verbose)
    {
      std::cout << "Node " << node << ": ";
      for (size_t i = 0; i < r2NodeInput.size(); i++)
      {
        std::cout << r2NodeInput[i] << " ";
      }
      std::cout << "" << std::endl;
    }
    // 4 nodes in r1 fan in to 1 node in r2
    int row = node/3;
    int col = node - (row * 3);
    NTA_CHECK(r2NodeInput.size() == 8);
    NTA_CHECK(r2NodeInput[0] == 0);
    NTA_CHECK(r2NodeInput[2] == 0);
    NTA_CHECK(r2NodeInput[4] == 0);
    NTA_CHECK(r2NodeInput[6] == 0);
    // these values are specific to the fanin2 link policy
    NTA_CHECK(r2NodeInput[1] == row * 12    + col * 2) 
      << "row: " << row << " col: " << col << " val: " << r2NodeInput[1];
    NTA_CHECK(r2NodeInput[3] == row * 12    + col * 2 + 1)
      << "row: " << row << " col: " << col << " val: " << r2NodeInput[3];
    NTA_CHECK(r2NodeInput[5] == row * 12 + 6 + col * 2)
      << "row: " << row << " col: " << col << " val: " << r2NodeInput[5];
    NTA_CHECK(r2NodeInput[7] == row * 12 + 6 + col * 2 + 1)
      << "row: " << row << " col: " << col << " val: " << r2NodeInput[7];
  }

  region2->compute();
}