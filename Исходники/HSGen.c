/* GenSentences: top level control of the sentence generator */
void  GenSentences(char * latfn, char * dicfn)
{
   int i,min,max,len;
   double e,p;
   MemHeap lheap;
   FILE *f;
   Boolean isPipe;

   InitVocab(&voc);
   if(ReadDict(dicfn,&voc)<SUCCESS)
      HError(3413,"GenSententces:ReadDict failed" );
   CreateHeap(&lheap,"Lattice Heap",MSTAK,1,0.4,1000,5000);
   if ((f=FOpen(latfn,NetFilter,&isPipe)) == NULL)
      HError(3410,"GenSentences: Can't open lattice file %s",latfn);
   if((lat = ReadLattice(f, &lheap, &voc, TRUE, FALSE))==NULL)
      HError(3410,"GenSentences: ReadLattice failed");
   FClose(f,isPipe);

   if (trace&T_TOP)
      printf("HSGen %d sents from lattice %s/dictionary %s\n",
             ngen,latfn,dicfn);
   psSum = 0.0; lenSum = 0; min = 100000; max = 0;
   if (trace&T_DET) quiet = TRUE;  /* kill output if detailed trace */
   for (i=1; i<=ngen; i++){
      len = GenSent(i);
      lenSum += len;
      if (len>max) max = len;
      if (len<min) min = len;
   }
   if (stats)  {
      ComputeVSize();
      e = psSum / lenSum;
      p = exp(e);
      e = e / log(2.0);
      printf("Entropy = %f,  Perplexity = %f\n",e,p);
      printf("%d Sentences: average len = %.1f, min=%d, max=%d\n",
             ngen,(float)lenSum/ngen,min,max);
   }
}