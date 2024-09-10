int main(int argc, char **argv){
  myDistro->Init(argc,argv);
  char *hostname = NULL;
  if (argc > 1) {
  	hostname = argv[1];
  }
  hostname = getHostname(hostname);
  char* res = getQpidPort(hostname);
  if (!res) {
  	printf("%s\n%s\nDONE \n", hostname, "-1");
  } else {
  	printf("%s\n%s\nDONE \n", hostname, res);  	
  	free(res);
  }
  if (argc <= 1)
  	free(hostname);
  
  return 0;
}