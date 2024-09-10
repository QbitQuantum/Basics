int sbcl_bin_install(struct install_options* param) {
  int ret;
  char* home=configdir();
  char* impl=param->impl;
  char* version=param->version;
  char* impl_path= cat(home,impldir(param->arch,param->os,impl,version),NULL);
  char* src=param->expand_path;
  char* sbcl_home=cat(impl_path,"/lib/sbcl",NULL);
  char* install_root=q(impl_path);
  char* log_path=cat(home,"impls/log/",impl,"-",version,"/install.log",NULL);
  cond_printf(0,"Building %s/%s...",impl,version);
  ensure_directories_exist(impl_path);
  ensure_directories_exist(log_path);
  change_directory(src);
  setenv("SBCL_HOME",sbcl_home,1);
  setenv("INSTALL_ROOT",install_root,1);
  ret=System("(cat find-gnumake.sh; echo find_gnumake)|sh");
  if(ret!=0) {
    fprintf(stderr,"'make' command not available.\n");
    return 0;
  }
  ret=1;
  if(system_redirect("sh install.sh",log_path)==-1)
    ret=0;
  s(home),s(impl_path),s(sbcl_home),s(install_root),s(log_path);
  printf(" Done.\n");
  return ret;
}