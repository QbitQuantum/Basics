U8 *FileRead(U8 *filename,I64 *_size=NULL,I64 *_attr=NULL,Bool raw=FALSE)
{
  CHashGeneric *temph;
  U8 *absname,*altname,*curname,*result=NULL;
  I64 i,size=0,attr=0;
  CFileAccess *fa;
  CArcCompress *ac=NULL;
  if (_attr) *_attr=0;
  absname=FileNameAbs(filename);
  altname=ToggleZorNotZ(absname);
  if (!raw && ((temph=HashFind(absname,adam_task->hash_table,HTT_FILE))||
	       (temph=HashFind(altname,adam_task->hash_table,HTT_FILE)))) {
    if (FileAttr(absname) & _ATTR_COMPRESSED) {
      ac=temph->user_data0;
      if (_size) *_size=ac->expanded_size;
      if (_attr) *_attr=FileAttr(absname,*_attr);
      result=ExpandBuf(ac);
    } else {
      result=MAlloc(temph->user_data1+1);
      MemCpy(result,temph->user_data0,temph->user_data1);
      result[temph->user_data1]=0; //Terminate
      if (_size) *_size=temph->user_data1;
    }
  } else {
    for (i=0;i<2 && !result;i++) {//Try name, then altname
      if (!i)
	curname=absname;
      else
	curname=altname;
      if (fa=FileAccessNew(curname)) {
	switch (fa->p->type) {
	  case PT_REDSEA:
	    result=RedSeaFSFileRead(fa->p,Fs->cur_dir,fa->mask,&size,&attr,raw,&ac);
	    break;
	  case PT_FAT32:
	    result=FAT32FileRead(fa->p,Fs->cur_dir,fa->mask,&size,&attr,raw,&ac);
	    break;
	  case PT_ISO9660:
	    result=ISO1FileRead(fa->p,Fs->cur_dir,fa->mask,&size,&attr,raw,&ac);
	    break;
	  default:
	    PutDefineErr("ST_UNSUPPORTED_FILE_SYSTEM");
	}
	FileAccessDel(fa);
      }
    }

    //Search parent directories.
    for (i=0;i<2 && !result;i++) {//Try name, then altname
      if (!i)
	curname=absname;
      else
	curname=altname;
      if (fa=FileAccessNew(curname)) {
	while (!result && StrCmp(Fs->cur_dir,"/")) {
	  Cd("..");
	  switch (Fs->cur_prt->type) {
	    case PT_REDSEA:
	      result=RedSeaFSFileRead(fa->p,Fs->cur_dir,fa->mask,&size,&attr,raw,&ac);
	      break;
	    case PT_FAT32:
	      result=FAT32FileRead(fa->p,Fs->cur_dir,fa->mask,&size,&attr,raw,&ac);
	      break;
	    case PT_ISO9660:
	      result=ISO1FileRead(fa->p,Fs->cur_dir,fa->mask,&size,&attr,raw,&ac);
	      break;
	    default:
	      PutDefineErr("ST_UNSUPPORTED_FILE_SYSTEM");
	  }
	}
	FileAccessDel(fa);
      }
    }
    if (!result) {
      "%s ",filename;
      PutDefineErr("ST_FILE_NOT_FOUND");
    }
    if (_size) *_size=size;
    if (_attr) *_attr=attr;
    if (result && !raw && attr & _ATTR_RESIDENT)
      HashGenericAdd(curname,HTT_FILE,AMAllocIdentical(ac),size,0,adam_task);
    Free(ac);
  }
  Free(absname);
  Free(altname);
  return result;
}