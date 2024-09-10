void vflsh()
{
VPAGE *vp;
VPAGE *vlowest;
long addr;
VFILE *vfile;
int x;
for(vfile=vfiles.link.next;
    vfile!=&vfiles;
    vfile=vfile->link.next)
 {
 loop:
 addr= MAXLONG;
 vlowest=0;
 for(x=0;x!=HTSIZE;x++)
  for(vp=htab[x];vp;vp=vp->next)
   if(vp->addr<addr && vp->dirty && vp->vfile==vfile && !vp->count)
    addr=vp->addr, vlowest=vp;
 if(vlowest)
  {
/*  if(!vfile->name) vfile->name=mktmp("/tmp/"); */  /* changed p,w. wong */

  char *pwstring="c:/joe";
  
  if (getenv("JOERC")) pwstring = getenv("JOERC");
  if(!vfile->name) vfile->name=mktmp(pwstring); 
  if(!vfile->fd)
   {
   vfile->fd=Fopen(vfile->name);
   }
  Fseek(vfile->fd,addr);
  if(addr+PGSIZE>vsize(vfile))
   {
   Fwrite(vfile->fd,vlowest->data,(int)(vsize(vfile)-addr));
   vfile->size=vsize(vfile);
   }
  else
   {
   Fwrite(vfile->fd,vlowest->data,PGSIZE);
   if(addr+PGSIZE>vfile->size) vfile->size=addr+PGSIZE;
   }
  vlowest->dirty=0;
  goto loop;
  }
 }
}