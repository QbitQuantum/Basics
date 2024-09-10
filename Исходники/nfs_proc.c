/* The following X functions affect are the only ones that affect the name
 cache (and the directory cache):
 nfs_open (in file nfs_lookup_cache.c),
 nfs_lookup (in file nfs_lookup_cache.c),
 nfs_link,
 nfs_symlink,
 nfs_mkdir,
 nfs_rmdir,
 nfs_rename 
 */
int 
nfs_unlink(struct file *dirp, const char *name) {
  nfsc_p d,f;
  int dev;
  struct nfs_fh *fhandle;
  int status,lookup_status;

  DPRINTF(CLU_LEVEL,("** nfs_unlink %s\n",name));
  demand(dirp, bogus filp);
  d = GETNFSCE(dirp);
  fhandle = GETFHANDLE(dirp);
  dev = FHGETDEV(fhandle);

  lookup_status = nfs_cache_lookup(dev,GETNFSCEINO(d),name,&f);
  switch(lookup_status) {
  case -1: 
    /* negative cache hit, treat it as a miss to be sure is properly removed */
  case 0:
    /* cache miss */
    {
      struct nfs_fh fhandle2;
      struct nfs_fattr temp_fattr;
      
      k2printf("nfs_unlink: nfs_proc_lookup %s\n",name);
      status = nfs_proc_lookup(fhandle,
			       name,
			       &fhandle2,
			       &temp_fattr);

      if (status != 0) {
	errno = status;
	return -1;
      } 

      f = nfsc_get(dev,temp_fattr.fileid);
      nfs_fill_stat(&temp_fattr, f);
      
    }
  /* fall-through now that we have setup f */
  case 1:
    /* cache hit */
    if (nfsc_get_refcnt(f) == 1) {
      /* last copy */
      if (S_ISDIR(nfsc_get_mode(f))) {
        status = nfs_proc_rmdir(fhandle, name);
	//fprintf(stderr,"rmdir  status %d\n",status);
      } else {
	status = nfs_proc_remove(fhandle,name);
	//fprintf(stderr,"remove status %d\n",status);
      }
      if (status == 0) {
	nfs_cache_remove(dirp,NULL);
	nfs_flush_filp(dirp);
      }

      nfsc_put(f);
      if (status != 0) {
	errno = status; return -1;
      } 
      return 0;


    } else {
      /* has other references */
      static int i = 0;
      char difname[NAME_MAX];
      //fprintf(stderr,"removing a file that is still referenced: %s\n",name);
      demand (!(S_ISDIR(f->sb.st_mode)), removing last ref directory);
      if (i == 0) atexit(nfs_process_unlinkatend);
      sprintf(difname,".nfs%d%d.%s",time(0),i++,name);
      status = nfs_proc_rename(fhandle,name,fhandle,difname);
      if (status != 0) fprintf(stderr,"could not rename %s\n",name);
      nfs_cache_remove(dirp,name);
      nfs_flush_filp(dirp);
      nfs_unlinkatend(difname, fhandle);
      nfsc_put(f);
      
      /* since it will be unlinked we can avoid flushing on close */
      nfsc_or_flags(f,NFSCE_WILLBEGONE); 

      return 0;
    }
  default:
    PR;
    assert(0);
    return 0;
  }
}