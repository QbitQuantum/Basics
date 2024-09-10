static int 
os_startp (const char *shell, const char *command, const char *parm) 
{  
   if (parm) { 
         char *argv[256],*par=strdup(parm),*p,i=0;
         argv[i++]=strdup(shell); 
         argv[i++]=strdup("/c"); 
         argv[i++]=strdup(command); 
         p=strtok(par," ");
         while(p) {
             argv[i++]=strdup(p);
             p=strtok(0," ");
         }
         argv[i]=0; 
         spawnvp (P_WAIT,shell,argv);
         i=0;
         while(argv[i])free(argv[i++]);
         free(par);
    } else {
         spawnlp (P_WAIT, 
              (char *) shell, 
              (char *) shell, 
              "/c", 
              (char *) command, 
              (char *) 0);
    }
    return 0;
}