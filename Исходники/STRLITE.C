const char *str_replace(TSTR_LIST *list,int line,const char *text)
  {
  int count,i,j;
  TSTR_LIST p;
  char *c;

  count=str_count(*list);
  if (line>=count)
     {
     int plus;

        plus=count-line;
        plus=(plus/STR_REALLOC_STEP+1)*STR_REALLOC_STEP;
        p=getmem((count+plus)*sizeof(*p));
        memcpy(p,*list,count*sizeof(*p));
        free(*list);
        j=_msize(p)/sizeof(*p);
        i=count;
        for(;i<j;i++) p[i]=NULL;
        i=count;count=j;
        *list=p;
     }
  if ((*list)[line]!=NULL) free((*list)[line]);
  if (text!=NULL)
     {
     c=(char *)getmem(strlen(text)+1);
     if (c==NULL) return NULL;
     strcpy(c,text);
     }
  else
     c=NULL;
  (*list)[line]=c;
  return c;
  }