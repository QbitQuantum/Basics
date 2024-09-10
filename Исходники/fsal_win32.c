int fsal_init(void) {
  //set the root dir for the simulated FAT
  _getcwd(root_dir, READER_PATH_MAX);
  printf("root=%s\n", root_dir);
  _wgetcwd(root_dir_uni, READER_PATH_MAX);
  _chdir(root_dir);
  return 0;
}