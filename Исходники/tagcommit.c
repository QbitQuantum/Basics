/* Fetch the sha of a library in the folder 'path' and return it in 'res'. */
void getCommit(const char *path, char* res){
  /* Buffers */
  char buffer[250]; 
  char sha[42];
  /* Command to fetch sha */
  sprintf(buffer, "cd %s && git rev-parse HEAD", path); 

  /* Read command result */
  FILE *fp;
  #ifdef __linux__ 
    fp = popen(buffer, "r");
   #elif _WIN32
    fp = _popen(buffer, "r");
  #else
    ModelicaFormatError("Unsupported operating system\n");
  #endif  
  
  if (fp == NULL) {
    ModelicaFormatError("Failed to call git command\n");
  }
  if (fgets(sha, sizeof(sha)-1, fp) == NULL){
  	ModelicaFormatError("Path %s does not exist or git cannot be called\n", path);
  }
  
  #ifdef __linux__ 
    pclose(fp);
  #else
    _pclose(fp);
  #endif    

  /* Return result */
  strcpy(res,sha);
}