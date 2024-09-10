int main(int argc, char *argv[])
{
  tokenlist args;
  args.Transfer(argc - 1, argv + 1);
  int argStat = parseArg(args);
  // print out usage message for illegal arguments
  if (argStat == 0) {
    printHelp();
    exit(1);
  }  
  // Make sure original condition function file exists and has right permission
  if (!chkOrgFile(infilename))
    exit(1);

  tokenlist condKey;
  VB_Vector *outVec = new VB_Vector();
  int refStat = getCondVec(infilename.c_str(), condKey, outVec);
  // Make sure the original condition function is in correct format
  if (!chkCfgStat(refStat, infilename.c_str()))
    exit(1);
  // Make sure new ref file's name is valid
  if ((argStat == 1 || argStat == 3) && !chkNewFile(newRef))
    exit(1);
  // Make sure new avg file's name is valid
  if ((argStat == 2 || argStat == 3) && !chkNewFile(avgName))
    exit(1);

  // Generate new condition function in numerical format
  if (newRef.length())
    outVec->WriteFile(newRef);
  // Generate avarages txt file
  if (avgName.length())
    writeAvg(avgName, condKey, outVec);

  delete outVec;
  return 0;
}