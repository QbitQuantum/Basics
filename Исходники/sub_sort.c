float nth(int ndat,float *dat,float n)
 {
  float a,temp;
  int i,nmax;
  float s;
  int nsame;

  if(n>=ndat-1) return dat[ndat-1];
  if (ndat==1 || n<0) return dat[0];
  if (ndat<=2)
    {
      if(dat[0]<dat[1])
	return (dat[0]*(1.-n)+n*dat[1]);
      else
	return (dat[1]*(1.-n)+n*dat[0]);
    }    

  /* quick sort! */
  a=dat[0];
  nmax=ndat;
  nsame=1;

  for(i=1;i<nmax;i++)
    {
      if(dat[i]>a)
	{
	  /* swap */
	  temp=dat[i];
	  dat[i]=dat[nmax-1];
	  dat[nmax-1]=temp;
	  nmax--;
	  i--;
	}  
      else if(dat[i]==a) 
	{
	  temp=dat[i];
	  dat[i]=dat[nsame];
	  dat[nsame]=temp;
	  nsame++;
	}
    }

  if(nmax==ndat)
    {
      /* 1999/04/08 */
      if (nmax-nsame<=n)
	{
	  return a;
	}
      else if(nmax-nsame-1>n)
	{
	  return nth(nmax-nsame,dat+nsame,n);
	}
      else
	{
	  /* ans is {nmax-nsame-1,(nmax-nsame=dat[0])}*/
	  s=n-(nmax-nsame-1);
	  return (floatmax(nmax-nsame,dat+nsame)*(1.-s)+s*dat[0]);	  
	}
    } 

  if (n<nmax-nsame-1) 
    {
      return nth(nmax-nsame,dat+nsame,n);    
    }
  else if (n<nmax-nsame)
    {
      s=n-(nmax-nsame-1);
      return (floatmax(nmax-nsame,dat+nsame)*(1.-s)+s*dat[0]);	  
    }
  else if (n<=nmax-1)
    {
      return a;
    }

  else if(n<nmax)
    {
      /* nmax-1< | n<nmax  */
      s=n-(nmax-1);
      return (dat[0]*(1.-s)+s*floatmin(ndat-nmax,dat+nmax));
    }
  else 
    {
      return nth(ndat-nmax,dat+nmax,n-nmax);
    }
}