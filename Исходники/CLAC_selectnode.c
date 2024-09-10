void selectclust(int *n, int *merge, int *senode, int *seleaf)
{
  int i,j,k,temp,nn;
  int *sn, *tleaf, *tnode;
  
  nn=(*n)+1;
  sn=(int *)malloc((nn-1)*sizeof(int));
  tleaf=(int *)malloc(nn*sizeof(int));
  tnode=(int *)malloc(nn*sizeof(int));
  
  setzero(&nn, tleaf);
  setzero(n, tnode);

  for(i=0;i<(*n);i++)
    {
      *(sn+i)=*(senode+i);
    }

  maxnonzero(n, sn, &temp);
  k=1;
  while(temp>0)
    {
      subtree(n, merge, &temp, tnode, tleaf);
      for(i=0;i<((*n)+1);i++)
    {
      if(*(tleaf+i)==1)
        *(seleaf+i)=k;
    }
      for(i=0;i<(*n);i++)
        {
          if(*(tnode+i)==1)
        *(sn+i)=0;
    }
      k++;
      setzero(&nn, tleaf);
      setzero(n, tnode);
      maxnonzero(n, sn, &temp);
    }
}