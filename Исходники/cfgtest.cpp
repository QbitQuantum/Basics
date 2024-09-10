void doStuff() {
  /* Create config and dereference pointers & shit */
  Config cfg;

  /* Get root setting and add sub-settings */
  Setting &root = cfg.getRoot();
  
  root.add("awesome", Setting::TypeBoolean) = false;
  cfg.writeFile("test.cfg");
}