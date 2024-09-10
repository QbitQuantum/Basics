static int SystemCall(int mode)
{ 
  char buff[2000];
  int err;
  FILE*f;

  if(!access(FOUT,R_OK)) unlink(FOUT);

  sprintf(buff,"%s/SPheno",SPHENO);
  if(access( buff,X_OK))
  { printf("Executable \n %s\n is not found. Program stops.\n",buff);
    exit(13);
  }  

   f=fopen("Control.in","w");
   fprintf(f,"0       | ErrorLevel\n"
             ".false. ! Calculation of branching ratios\n"
             ".false. ! Calculation of cross sections\n");
   fclose(f);

  err=System(buff);   
  if(err>0) err=slhaRead(FOUT,0); else cleanSLHAdata();
  if(delFiles)
  { unlink(FIN);unlink(FOUT);  
    unlink("Control.in");unlink("Messages.out");unlink("SPheno.out");
  }
          
  return err;
}