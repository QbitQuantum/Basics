/*************** MAIN PROGRAM ******************************/
int main(int arg_count, char **args)
{
  char startpath[_MAX_PATH], *apu;
  char *defaultdir = ".";
  unsigned long disk_size,disk_free, summa;
  double slack;

  printf("\nDU/" VERSION_BITS "bit v" VERSION_NO
	 "     Copyright (c) Timo Kokkonen, OH6LXV               "
	 RELEASE_DATE "\n\n");

  strcpy(startpath,".");
  if (arg_count>1) {
    if (!strcmp(args[1],"/?")) {
      print_syntax();
      exit(0);
    }
    if (args[arg_count-1][0]=='/')
     if (sscanf(&args[arg_count-1][1],"%d",&sublevels)!=1) {
       printf("\nInvalid parameter '%s'.\n",args[arg_count-1]);
       print_syntax();
       exit(1);
     }
  }
  if ((arg_count>=2)&&(args[1][0]!='/'))  apu=args[1];
    else apu=defaultdir;

  if (!_fullpath(startpath,apu,_MAX_PATH)) {
    printf("Cannot convert '%s' to absolute path.\n",apu);
    exit(1);
  }
  if (startpath[strlen(startpath)-1]!='\\') strcat(startpath,"\\");
  strcpy(startpath,SplitDir(startpath));

  if (!getDiskSize(startpath[0]-64,&disk_size,&disk_free,&cluster_size)) {
    printf("Cannot read drive %c: \n",startpath[0]);
    exit(1);
  }
  summa=calc_dir(startpath);
  if (true_sum!=0) slack=(1-(double)summa/true_sum)*100.0;
    else slack=0;

  // printf(" %lu  %lu  %lu \n",disk_size-disk_free,summa,true_sum);
  printf("\n %lu bytes in %lu file(s), %1.1lf%% slack (%lu bytes).\n",
							true_sum,
							file_counter,
							slack,
							true_sum-summa);
  return 0;
}