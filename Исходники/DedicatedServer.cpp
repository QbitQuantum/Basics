void ExecScript(const CTString &str)
{
  CPrintF("Executing: '%s'\n", str);
  CTString strCmd;
  strCmd.PrintF("include \"%s\"", str);
  _pShell->Execute(strCmd);
}