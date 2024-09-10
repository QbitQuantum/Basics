  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    std::ifstream infile("pngnow.png", std::ios::binary);
    if (infile.fail())
      infile.open("../pngnow.png", std::ios::binary);
    if (infile.fail())
      result = "Could not open file pngnow.png";
    else {

      XmlRpcValue::BinaryData& data = result;
      int n = 0;
      for (;; ++n) {
        char c = infile.get();
        if (infile.eof()) break;
        data.push_back(c);
      }
      s.exit();
      std::cerr << "Read " << n << " bytes from pngnow.png\n";
    }
  }