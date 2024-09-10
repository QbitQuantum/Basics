void main(int argc, char** argv)
{
  DIR* d;
  int f;
  struct dirent* entry;
  char name[555];
  char* p;
  int i = 1;
  
  do
  {
    assert((f = fork()) != -1);
    if(!f)
    {
      execlp("clear", "clear", NULL);
      exit(0);
    }
    wait(&f);

    strncpy(name, argc > 1 ? argv[i] : ".", 554);
    assert(d = opendir(name));
    
    if(inRepo(d))
    {
      printf("\tupdating svn of directory %s\n\n", argc > 1 ? argv[i++] : ".");
      assert((f = fork()) != -1);
      if(!f)
      {
	chdir(name);
	execlp("svn", "svn", "update", NULL);
	exit(0);
      }
      else
      {
	wait(&f);
	printf("\n\n");
      }
    }
    else
    {
      printf("\tlooking through subdirectories of %s for svn repositories\n\n", argc > 1 ? argv[i++] : ".");
      
      while(entry = readdir(d))
      {
	if(entry->d_type == DT_DIR && strcmp(entry->d_name, ".") && strcmp(entry->d_name, ".."))
	{
	  assert((f = fork()) != -1);
	  if(!f)
	  {
	    p = name;
	    while(*(++p));
	    if(*(p - 1) != '/')
	    {
	      *(p++) = '/';
	    }
	    strcpy(p, entry->d_name);
	    printf("%s:\n", entry->d_name);
	    chdir(name);
	    closedir(d);
	    assert(d = opendir("."));
	    if(inRepo(d))
	    {
	      execlp("svn", "svn", "update", NULL);
	    }
	    else
	    {
	      printf("Not a repository\n");
	    }
	    exit(0);
	  }
	  else
	  {
	    wait(&f);
	    printf("\n");
	  }
	}
      }
      
      closedir(d);
      printf("\n");
    }
  }
  while(i < argc);
}