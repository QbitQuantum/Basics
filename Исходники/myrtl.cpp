FILE *wfopen(const wchar_t *filename, const wchar_t *mode)
{
   if(!mode || !filename || !*filename)
      return NULL;
   //_D(SysLog("fopen: filename[%s], mode[%s] strpbrk%c=NULL",
   //   filename, mode, strpbrk(mode, "rwa")?'!':'='));
   if(wcspbrk(mode, L"rwa")==NULL)
      return NULL;
   DWORD dwDesiredAccess=0, dwCreationDistribution=0;
   BOOL R, W, A;
   R=W=A=FALSE;
/*
r   Open for reading only.
w   Create for writing. If a file by that name already exists, it will be
    overwritten.
a   Append; open for writing at end-of-file or create for writing if the file
    does not exist.
r+  Open an existing file for update (reading and writing).
w+  Create a new file for update (reading and writing). If a file by that name
    already exists, it will be overwritten.
a+  Open for append; open (or create if the file does not exist) for update at
    the end of the file.
*/
   if(wcschr(mode, L'r'))
   {
     //_D(SysLog("r - GENERIC_READ"));
     dwDesiredAccess|=GENERIC_READ;
     dwCreationDistribution=OPEN_EXISTING;
     R=TRUE;
   }
   if(wcschr(mode, L'w'))
   {
     //_D(SysLog("w - GENERIC_WRITE"));
     dwDesiredAccess|=GENERIC_WRITE;
     dwCreationDistribution=CREATE_ALWAYS;
     W=TRUE;
   }
   if(wcschr(mode, L'a'))
   {
     //_D(SysLog("a - GENERIC_WRITE"));
     dwDesiredAccess|=GENERIC_WRITE;
     dwCreationDistribution=OPEN_ALWAYS;
     A=TRUE;
   }
   if(wcschr(mode, L'+'))
   {
     //_D(SysLog("+++"));
     dwDesiredAccess|=GENERIC_WRITE;
     dwCreationDistribution=CREATE_ALWAYS;
     if(R) dwDesiredAccess|=GENERIC_WRITE;
     if(W) dwDesiredAccess|=GENERIC_READ;
   }

   HANDLE hFile=CreateFile(filename, dwDesiredAccess, FILE_SHARE_READ, NULL,
                           dwCreationDistribution, 0, NULL);
   //_D(SysLog("hFile%c=INVALID_HANDLE_VALUE", hFile==INVALID_HANDLE_VALUE?'=':'!'));
   if(hFile==INVALID_HANDLE_VALUE) return NULL;
   if(A) fseek((FILE *)hFile, 0, SEEK_END);
   return (FILE *)hFile;
};