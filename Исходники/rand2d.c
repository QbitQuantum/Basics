int InicGen2D(float func(int,int),int TimeSize,int FreqSize,int Srand)
 {	/* Inicjacja generatora liczb z 2D rozkladu p-stwa func(x,y) */
   register int i,j;
   float sum,norma=0.0F;

   if((DystMatrix=MakeTable(TimeSize,FreqSize))==NULL)
     return -1;
   if((DystVector=(float *)malloc(TimeSize*sizeof(float)))==NULL)
    {
      FreeTable(DystMatrix,TimeSize); DystMatrix=NULL;
      return -1;
    }

   if(Srand==0)
     SRAND(0U);
   else SRAND((unsigned short)time(NULL));

   GlobTimeSize=TimeSize;
   GlobFreqSize=FreqSize;

   for(i=0 ; i<TimeSize ; i++)   /* Generacja rozkladu p-stwa + normalizacja */
     for(j=0 ; j<FreqSize ; j++)
      { 
        const float ftmp=func(i,j); /* Wartosci ujemne nie maja interpretacji */

        norma+=DystMatrix[i][j]=((ftmp<0.0F) ? 1.0F : ftmp); 
      }

   for(i=0,sum=0.0F ; i<FreqSize ; i++) /* Dystrybuanta brzegowa */
    sum+=DystMatrix[0][i];
   DystVector[0]=sum/norma;
   for(i=1 ; i<TimeSize ; i++)
    {
      for(j=0,sum=0.0F ; j<FreqSize ; j++)
       sum+=DystMatrix[i][j];
      DystVector[i]=DystVector[i-1]+sum/norma;
    }

   for(i=0 ; i<TimeSize ; i++)	       /* Dystrybuanty warunkowe */
     {
       for(j=0,sum=0.0F ; j<FreqSize ; j++)
	sum+=DystMatrix[i][j];
       DystMatrix[i][0]/=sum;
       for(j=1 ; j<FreqSize ; j++)
	 DystMatrix[i][j]=DystMatrix[i][j-1]+DystMatrix[i][j]/sum;
     }
   return 0;
 }