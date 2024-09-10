int main (int argc, char **argv)
{
  ini_sContext *cp;
  pwr_tStatus sts;

  set_valid_time();

  cp = createContext(argc, argv);

  ver_WriteVersionInfo("Proview Runtime Environment");

  if (cp->flags.b.restart) {
    sts = interactive(argc, argv, cp);
  } else if (cp->flags.b.stop) {
    sts = stop(argc, argv, cp);
  } else {
    sts = start(cp);
    sts = events(cp);
    errh_LogInfo(&cp->log, "Ich sterbe!!");
  }

  exit(sts);
}