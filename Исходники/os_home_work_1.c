int main()
{
  pid_t pid;
  FILE *f;
  char str1[100], str2[100], str3[100];
  if((pid=fork()) == 0)
  {//child
    strcpy (str1,"file_");
    gcvt(getpid(), 12, str3);
    strcat (str1, str3);
    strcat (str1, ".txt");
    f = fopen(str1,"w+");
    fprintf(f, "Parent: %d;\n", getppid());
    fclose(f);
  } 
  else
  {//parent
    strcpy (str2,"file_");
    gcvt(getpid(), 12, str3);
    strcat (str2, str3);
    strcat (str2, ".txt");
    f = fopen(str2, "w+");
    fprintf(f, "I am: %d and my child: %d; \n", getpid(), pid);
    waitpid(pid, NULL, 0);
    fclose(f);
  }
  return 0;
}