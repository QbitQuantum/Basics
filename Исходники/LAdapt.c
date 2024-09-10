/* ProcessText: read text files line by line and count ngrams */
void ProcessText(char *fn, bool lastFile)
{
   FILE *f;
   LabId id;
   bool isPipe;
   char word[256];

   if (trace&T_TOP) 
      printf("Reading source text file %s\n",(fn==NULL) ? "<stdin>" : fn);
   if ((fn!=NULL) && (strcmp(fn,"-")!=0)) {
      if ((f = FOpen(fn,LMTextFilter,&isPipe))==NULL)
	 HError(16410,"ProcessText: unable to open text file %s", fn);
   } else {
      f = stdin;
   }
   while (fscanf(f,"%255s",word)==1) {
      if (pruneWords) {
	 if ((id = GetLabId(word,FALSE))==NULL && (id = unkId)==NULL) {
	    stdBuf.used=0;
	    continue;
	 }
      } else {
	 id = GetLabId(word,TRUE);
      }
      if (trace&T_INP) printf("[%s]\n",id->name);
      PutShiftRegister(id,&stdBuf);
   }
   if (fn!=NULL) {
      FClose(f,isPipe);
      if (lastFile)
	 CompressBuffer(stdBuf.ngb,TRUE);
   } else {
      CompressBuffer(stdBuf.ngb,TRUE);
   } 
}