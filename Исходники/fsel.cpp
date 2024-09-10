static int do_paths(int sel) {
  path_sel *paths = new path_sel();
  paths->add_item(getenv("HOME"));
#ifdef RAINE_UNIX
  int pipe_opened = 0;
  FILE *f = fopen("/etc/mtab","r");
  if (!f) {
      // Darwin doesn't seem to have a file for that, so let's use popen...
      f = popen("mount","r");
      pipe_opened = 1;
  }
  if (f) {
    char buff[2048];
    while (!feof(f)) {
      fgets(buff,2048,f);
      if (strncmp(buff,"/dev/",5)) // keep only the /dev entries
	continue;
      char *s1 = strchr(buff,' ');
      if (!s1) continue;
      char *s2 = strchr(s1+1,' ');
      if (!s2) continue;
      *s2 = 0;
      if (!strcmp(s1+1,"on")) {
	  // darwin speciality, just ignore it
	  s1 = s2;
	  s2 = strchr(s1+1,'(');
	  if (!s2) continue;
	  s2[-1] = 0;
      }
      paths->add_item(s1+1);
    }
    if (pipe_opened)
	pclose(f);
    else
	fclose(f);
  }
#else
  // windows
  paths->add_item(getenv("PROGRAMFILES"));
  paths->add_item(getenv("USERPROFILE"));
  int drives = GetLogicalDrives();
  int n;
  char path[3];
  strcpy(path,"x:");
  for (n=0; n<32; n++) {
    if (drives & (1<<n)) {
      path[0]=65+n;
      paths->add_item(path);
    }
  }
#endif
  selected_path = -1;
  TMenu *menu = new TPathDlg((char*)_("Path selection"),paths->get_menu());
  menu->execute();
  if (selected_path >= 0)
    dlg->set_dir((char*)paths->get_menu()[selected_path].label);
  delete menu;
  delete paths;
  return 0;
}