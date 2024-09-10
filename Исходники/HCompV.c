/* Export number of frames, mean, var to a given directory */
void ExportNMV(SpkrAccListItem *sal, char *OutDirName, char *tgtPKStr) 
{
   FILE *oFile;
   Boolean isPipe;
   char oFileName[MAXSTRLEN];
   char pathBuffer1[MAXSTRLEN];
   char pathBuffer2[MAXSTRLEN];
   SpkrAccListItem *p;
   int i;

   p = sal;
   while(p != NULL){
      /* create output file name for current spkr index */    
      if ( pathPattern[0] != '\0'){
         if ( MaskMatch(pathPattern,pathBuffer1,p->sa->SpkrName) != TRUE ){
            HError(2039,"HCompV: ExportNMV: path pattern matching failure on speaker: %s\n",p->sa->SpkrName);
         }
         MakeFN(pathBuffer1,OutDirName,NULL,pathBuffer2); 
         MakeFN(p->sa->SpkrName,pathBuffer2,NULL,oFileName);
      }
      else
         MakeFN(p->sa->SpkrName,OutDirName,NULL,oFileName);

      /* open and write */
      oFile = FOpen(oFileName,NoOFilter,&isPipe);
      if (oFile == NULL){
         HError(2011,"HCompV: ExportNMV: output file creation error %s",oFileName);
      }
    
      /* write header */
      fprintf(oFile,"<CEPSNORM> <%s>",tgtPKStr);
    
      /* write number frames */
      if (strchr(oflags,'n')){
         fprintf(oFile,"\n<NFRAMES> %d",p->sa->NumFrame);
      }
      /* write mean */
      if (strchr(oflags,'m')){
         fprintf(oFile,"\n<MEAN> %d\n",vSize);
         for (i=1;i<=vSize;i++){
            fprintf(oFile," %e",(p->sa->meanSum[i]));
         }
      }
      /* write variance */
      if (strchr(oflags,'v')){   
         fprintf(oFile,"\n<VARIANCE> %d\n",vSize);
         for (i=1;i<=vSize;i++){
            fprintf(oFile," %e",(p->sa->squareSum[i]));
         }
      }
      fprintf(oFile,"\n");
      FClose(oFile,isPipe);
      p = p->nextSpkr;
   }
}