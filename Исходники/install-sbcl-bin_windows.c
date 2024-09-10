int sbcl_bin_install(struct install_options* param) {
  char* version=param->version;
  char* arch=param->arch;
  char* home=configdir();
  char *str,*str2,*str3,*str4;
  char* version_num= q(version);
  int ret;
  str2=cat(home,"src\\sbcl-",version,"-",arch,"-windows\\PFiles\\Steel Bank Common Lisp\\",version_num,"\\sbcl.exe",NULL);
  str3=cat(home,"impls\\",arch,"\\windows\\sbcl-bin\\",version,"\\bin\\sbcl.exe",NULL);
  str=cat("cmd /c \"echo f|xcopy ^\"",str2,"^\" ^\"",str3,"^\" > NUL","\"",NULL);
  s(str2),s(str3);
  ret=System(str);s(str);
  if(ret) return 0;
  str2=cat(home,"src\\sbcl-",version,"-",arch,"-windows\\PFiles\\Steel Bank Common Lisp\\",version_num,"\\sbcl.core",NULL);
  str3=cat(home,"impls\\",arch,"\\windows\\sbcl-bin\\",version,"\\lib\\sbcl\\sbcl.core",NULL);
  str=cat("cmd /c \"echo f|xcopy ^\"",str2,"^\" ^\"",str3,"^\" > NUL","\"",NULL);
  ret=System(str);s(str);
  if(ret) return 0;
  str=cat("echo d|xcopy ^\"",
          home,"src\\sbcl-",version,"-",arch,"-windows\\PFiles\\Steel Bank Common Lisp\\",version_num,"\\contrib^\" ^\"",
          home,"impls\\",arch,"\\windows\\sbcl-bin\\",version,"\\lib\\sbcl\\contrib^\" >NUL",NULL);

  str2=cat(home,"src\\sbcl-",version,"-",arch,"-windows\\PFiles\\Steel Bank Common Lisp\\",version_num,"\\contrib",NULL);
  str3=cat(home,"impls\\",arch,"\\windows\\sbcl-bin\\",version,"\\lib\\sbcl\\contrib",NULL);
  str=cat("cmd /c \"echo d|xcopy ^\"",str2,"^\" ^\"",str3,"^\""," > NUL","\"",NULL);
  ret=System(str);
  s(str),s(home);
  if(ret) return 0;
  return 1;
} 