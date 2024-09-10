int main (int argc, char **argv)
{
  ini_sContext *cp;
  pwr_tStatus sts;

  cp = createContext(argc, argv);

  ver_WriteVersionInfo("Proview/R Storage Environment");

  if (cp->flags.b.stop) {
    sts = stop(argc, argv, cp);
  } else {
    sts = start(cp);
    sts = events(cp);
    errh_LogInfo(&cp->log, "Ich sterbe!!");
  }

  exit(sts);
}