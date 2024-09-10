vector <TString> OnlineConfig::SplitString(TString instring,TString delim) 
{
  // Utility to split up a string on the deliminator.
  //  returns a vector of strings.

  vector <TString> v;

  TString remainingString = instring;
  TString tempstring = instring;
  int i;

  while (remainingString.Index(delim) != -1) {
    i = remainingString.Index(delim);
    tempstring.Remove(i);
    v.push_back(tempstring);
    remainingString.Remove(0,i+1);
    while(remainingString.Index(delim) == 0) {
      remainingString.Remove(0,1);
    }
    tempstring = remainingString;
  }

  while(tempstring.EndsWith(delim)) {
    tempstring.Chop();
  }
     
  if(!tempstring.IsNull()) v.push_back(tempstring);

  return v;
}