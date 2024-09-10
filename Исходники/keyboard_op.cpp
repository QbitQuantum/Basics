  void readLineInput(char input[30])
  {
    std::cin.getline(input, 30);

    std::string inputStr(input);
    if (boost::iequals(inputStr, "q"))
    {
      rosNode.shutdown();
      std::exit(EXIT_SUCCESS);
    }
  }