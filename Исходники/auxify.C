ECString
auxify(ECString wM, ECString trmM)
{
  char temp[128];
  ECString w = toUpper(wM.c_str(),temp);
  ECString trm = toUpper(trmM.c_str(),temp);
  cerr << "AUX!!!" << endl;
  assert(0);
  if( isVerb( trm ) )
    {
      //cout << "saw verb " << trm << " " << wM << endl;
      if( isAux( w ) || hasAuxSuf( w ) )
	{
	  //cout << "was aux " << w << endl;
	  return "AUX";
	}
      else if( isAuxg( w ) )
	{
	  //cout << "was auxg " << w << endl;
	  return "AUXG";
	}
    }
  if(trm == "BES" || trm == "HVS")  //??? strange tags in switchboard
    {
      assert(w == "'S" || w == "-S");
      return "AUX";
    }
  return trmM;
}