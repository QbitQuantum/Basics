int main(int argc, char** argv){

  int CALL_CHKSUM=0;
  int CHUNK_SIZE=1024;
  int fileCount=0;
  int isFinished=1;
  unsigned int fileChecksum = 0;
  char* fileName;
  int opt;
  
  while((opt = getopt(argc, argv,"-hx:b:"))!=-1){
    switch (opt) {
      case 1:
fileName = optarg;
break;
      case 'h':
printf("OPTIONS\n\t-h\t\tprint a summary of options and exit\n\t-b SIZE\t\tput at most SIZE bytes per output file\n\t-x\t\tprint the checksum as a hexadecimal rather than decimal number.\n");
exit(0);
      case 'x':
CALL_CHKSUM=1;
fileName = argv[argc-1];
break;
      case 'b':
if(optarg!=0) CHUNK_SIZE = atoi(optarg);
fileName = argv[argc-1];
break;
      default:
fprintf(stderr,"Usage: %s [-h] [-x] [-b SIZE] FILE\n",argv[0]);
exit(1);
    }
  }
  FILE *fp = fopen(fileName, "r");
  if(fp==0){
    printf("The filename argument you provided is not valid\n");
    return 0;
  }
  unsigned char chunk[CHUNK_SIZE];
  memset(chunk,0,CHUNK_SIZE);
  unsigned char checksum = 0;
  int fileSize = 0;
  struct stat st = {0};
  if (stat("parts", &st) == -1) {
    mkdir("parts", 0700);
  }
 //part A
 //we should write a function which gets (location in a file, max size of bytes, name of target)
 //it will do the body of the while, one and replace it
 //ftell(tell me where in the file we are)
 //fseek(takes us to the place we want)
 //use only before the loop,jump to the end (0 from the end)
 //then use ftell to know the filesize
 //now get chank file: int numchank=(filesize+chanksize-1)/chanksize;
 
 
 
 //part B
 //make the function works on difreent proccesses
 //use folk()
 
 
 //this part should work in deffirent procceses
  while (isFinished){
    if ((fileSize = fread(&chunk, 1, CHUNK_SIZE, fp))==0) break;
    unsigned int chunksum=0;
    char newFileName[strlen(fileName)+15]; //create new file name
    fileCount++;
    newFile(newFileName,fileName,fileCount);
    FILE* file = fopen(newFileName,"w+"); //new file
    fwrite(&chunksum,sizeof(chunksum),1,file);	//write 0000 at the beginning
    fwrite(&chunk,fileSize,1,file);
    chunksum = chksum(file);//do chksum
    fileChecksum^=chunksum;//overall chanksum
    rewind(file);//look at first byte and write the new chanksum instand of 0000
    fwrite(&chunksum,sizeof(chunksum),1,file);//write
    memset(chunk,0,CHUNK_SIZE);//write 0 to chanksum (clean)
    if (fileSize<CHUNK_SIZE){//is theis dfinal chank
      isFinished=0;
      fclose(file);
    }
  }


  if (CALL_CHKSUM==1){//return as hex
    if (fileChecksum !=0){
      printf("Checksum: %u\n",fileChecksum);
    }
  }

return 0;
}