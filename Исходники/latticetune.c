static int strrcmp_i(char *s,char *cmp){
  return(strncmp(s+strlen(s)-strlen(cmp),cmp,strlen(cmp)));
}