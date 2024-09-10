void gotConfig(void)
{
  ArConfig *newConfig;
  done = true;
  configHandler->getConfig()->writeFile("configClient.txt");
  newConfig = new ArConfig(*(configHandler->getConfig()));
  newConfig->writeFile("configClientNew.txt");
}