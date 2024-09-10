  double readBranchLength(std::istream &iss)
  {
    bool foundNext = false; 
    while(not foundNext)
      {
	int ch = iss.get(); 

	foundNext = ( ch == ')'
		      || ch == ';'
		      || ch == ',' ) ; 
      }
    iss.unget();
    return nan("");
  }