EvtDecayMode EvtMultiChannelParser::getDecayMode(const char* file)
{
  // Open file, read tokens

  EvtParser parser;
  parser.read(file);

  // Seek Decay

  int i = 0;
  int N = parser.getNToken();
  while(i<N) {
    
    std::string tok = parser.getToken(i++);
    if(tok == std::string("Decay")) break;
  }
  
  // Get mother

  string mother = string(parser.getToken(i++).c_str());
  std::string bf = parser.getToken(i++);

  vector<string> dauV;
  // Get daughters
    
  while(1) {

    std::string d = parser.getToken(i++);

    if(EvtPDL::getStdHep(EvtPDL::getId(d.c_str())) == 0) break;
    
    dauV.push_back(string(d.c_str()));
  }
  
  EvtDecayMode mode(mother,dauV);
  printf("Decay File defines mode %s\n",mode.mode().c_str());

  return mode;
}