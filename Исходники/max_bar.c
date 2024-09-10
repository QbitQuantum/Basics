static void near BadBarPwd(char *pwd, char *name, int tries)
{
  logit(log_bad_bar_pwd, name, pwd);

  Printf(wrong_pwd, tries);
  Putc('\n');

  if (tries==3)
  {
    logit(l_invalid_pwd);
    Puts(invalid_pwd);
    ci_barricade();
    mdm_hangup();
  }
}