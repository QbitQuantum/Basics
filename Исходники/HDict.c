/* EXPORT->WriteDict: Write the given Vocab structure to the file dictFn */
ReturnStatus WriteDict(char *dictFn, Vocab *voc)
{
   FILE *df;
   Boolean isPipe,withOut,withProbs;
   Word wid, *wlist;
   Pron thisPron;
   float prob;
   char buf[MAXSTRLEN];
   int i,j,nw;

   nw = voc->nwords;
   if (trace&T_TOP)
      printf("WriteDict: %d words/%d prons to %s\n",
             nw,voc->nprons,dictFn);  
   if ( (df = FOpen(dictFn,DictOFilter,&isPipe)) == NULL){
      HRError(8011,"WriteDict: Cannot create dictionary file %s",dictFn);
      return(FAIL);
   }
   /* Create array of words */
   j = 0;
   wlist = (Word *)New(&gstack,sizeof(Word)*(nw+1));
   for (i=0,withOut=withProbs=FALSE; i< VHASHSIZE; i++)
      for ( wid = voc->wtab[i]; wid != NULL; wid = wid->next ) {
         if (wid==voc->nullWord || wid==voc->subLatWord)
            continue;
         if (j>=nw){
            FClose(df, isPipe);
            HRError(8090,"WriteDict: wlist full [%d]",j);
            return(FAIL);
         }
         wlist[j++] = wid;
         for (thisPron = wid->pron; thisPron != NULL; thisPron = thisPron->next) {
            if (thisPron->outSym==NULL || thisPron->outSym != wid->wordName) 
               withOut=TRUE;
            if (thisPron->prob!=0.0)
               withProbs=TRUE;
         }
      }
   if (j!=nw){
      HRError(-8090,"WriteDict: only %d of %d words found",j,nw);
   }
   /* sort list */
   qsort(wlist,nw,sizeof(Word),Wd_Cmp);

   /* print list of prons */
   for (i=0; i<nw; i++){
      wid = wlist[i];
      for (thisPron = wid->pron; thisPron != NULL; thisPron = thisPron->next) {
         ReWriteString(wid->wordName->name,buf,ESCAPE_CHAR);
         fprintf(df,"%s",buf); 
         Pad(df,WORDFIELDWIDTH-strlen(buf),1);
         if (thisPron->outSym==NULL) {
            fprintf(df,"[]");
            Pad(df,WORDFIELDWIDTH-2,0);
         } else if (thisPron->outSym != wid->wordName) {
            ReWriteString(thisPron->outSym->name,buf,ESCAPE_CHAR);
            fprintf(df,"[%s]",buf);
            Pad(df,WORDFIELDWIDTH-strlen(buf)-2,0);
         } else if (withOut)
            Pad(df,WORDFIELDWIDTH,0);
         if (withProbs) {
            prob=(thisPron->prob>LSMALL && thisPron->prob<=0.0)?exp(thisPron->prob):1.0;
            if (prob<1.0) fprintf(df," %8.6f",prob);
            /* 1.0 is just skipped */
            else Pad(df,9,0);
         }

         for (j=0; j < thisPron->nphones; j++) {
            fputc(' ',df);
            WriteString(df,thisPron->phones[j]->name,ESCAPE_CHAR);
         }
         fprintf(df,"\n");
      }
   }
   FClose(df,isPipe);
   return(SUCCESS);
}