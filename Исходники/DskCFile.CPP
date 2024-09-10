CFile *FOpen(U8 *filename,U8 *flags,I64 cnt=0)
{  //allows flags "r","w","w+".  Include a "c" for contiguous.
  CFile *f=CAlloc(sizeof(CFile));
  CFileAccess *fa;
  U8 *full_name;
  Bool contiguous=StrOcc(flags,'c');

  f->cluster=INVALID_CLUSTER;
  f->fblk_num=0;
  if (cnt>0)
    f->max_blk=cnt-1;
  else
    f->max_blk=MAX_I64;
  f->file_cluster_num=INVALID_CLUSTER;
  full_name=FileNameAbs(filename);
  f->p=Drv2Prt(*full_name);
  if (f->p->type==PT_REDSEA)
    contiguous=TRUE;
  if (contiguous) {
    f->flags|=FF_CONTIGUOUS;
    if (f->p->type!=PT_REDSEA) {
      if (!(FileAttr(filename) & _ATTR_CONTIGUOUS))
	throw(EXCEPT_FILE,2);
    }
  }
  f->cluster_buf=CAlloc(f->p->spc<<BLK_SIZE_BITS);
  if (StrOcc(flags,'w')) {
    f->flags=f->flags|FF_WRITE|FF_NEEDS_WRITE;
    if (StrOcc(flags,'+')) {
      if (FileFind(full_name,&f->de,FUF_JUST_FILES)) {
	Free(full_name);
	if (contiguous)
	  f->max_blk=(FSize(f)+BLK_SIZE-1)>>BLK_SIZE_BITS-1;
	return f;
      }
    } else