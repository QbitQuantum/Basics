// **************************************************************************
// construct a string with the node number of the 
//  process and the string ".log". This will be used as the suffix
// of the log name forthis process . So if the log name specified by the 
// user in the 
// configuration file is "sql_events", the actual log name will be
// something like "sql_events_<nid>.log"
// **************************************************************************
void getMyNidSuffix(char stringNidSuffix[])
{
  short result = 0;

  NAProcessHandle myPhandle;
  myPhandle.getmine();
  myPhandle.decompose();
  
  Int32 myNid = myPhandle.getCpu();

  snprintf (stringNidSuffix, 5+sizeof(Int32), "_%d.log", myNid);
}