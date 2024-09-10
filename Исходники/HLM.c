/* WriteBoNGram: write out WSJ/DP format ngram */
static void WriteBoNGram(LModel *lm,char *fn,int flags)
{
   int i,k;
   FILE *file;
   NGramLM *nglm;
   Boolean isPipe;

   nglm = lm->data.ngram;
   file=FOpen(fn,LangModOFilter,&isPipe);
   fprintf(file,"\\data\\\n");

   for (i=1;i<=nglm->nsize;i++) {
      fprintf(file,"ngram %d=%d\n",i,nglm->counts[i]);
   }
   for (i=1;i<=nglm->nsize;i++) {
      k = WriteNGrams(file,nglm,i,1.0/LN10);
      if (k!=nglm->counts[i])
         HError(-8190,"WriteBoNGram: Counts disagree for %dgram (%d vs %d)",
                i, k, nglm->counts[i]);
   }
   fprintf(file,"\n\\end\\\n");
   FClose(file,isPipe);
}