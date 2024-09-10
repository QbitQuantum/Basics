void CDynPatcher::Error(const char *File, const char *Func, int Line, bool IsCritical, char *Fmt, ...)
{
   static char Buff[0x1000];
   int len=0;
   
   len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,"[CDynPatcher] %serror",IsCritical?"critical":"");
   if(File&&Func&&Line&&strlen(File)<MAX_PATH&&strlen(Func)<300)
   {
      len+=_snprintf(&Buff[len],sizeof(Buff)-len-1," at %s(%s:%i)",CSectionData::GetFileName(File),Func,Line);
   }
   len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,":");
   va_list marker;
   if(!Fmt)
   {
      len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,"(NO DESCRIPTION)\r\n");
   }
   else
   {
      va_start( marker, Fmt );
      len+=_vsnprintf(&Buff[len],sizeof(Buff)-len-1, Fmt, marker );
   }
   len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,"\r\n");
   printf("%s",Buff);
   if(IsCritical)
   {
      #ifdef WIN32
      __asm{int 3};
      
      if(!IsDebuggerPresent())
      {
         exit(0);
      }
      #else
      exit(0);
      #endif
   }
}

void CDynPatcher::Message(const char *File, const char *Func, int Line, char *Fmt, ...)
{
   static char Buff[0x1000];
   int len=0;
   
   len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,"[CDynPatcher]");
   if(File&&Func&&Line&&strlen(File)<MAX_PATH&&strlen(Func)<300)
   {
      len+=_snprintf(&Buff[len],sizeof(Buff)-len-1," at %s(%s:%i)",CSectionData::GetFileName(File),Func,Line);
   }
   len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,":");
   va_list marker;
   if(!Fmt)
   {
      len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,"(NO DESCRIPTION)\r\n");
   }
   else
   {
      va_start( marker, Fmt );
      len+=_vsnprintf(&Buff[len],sizeof(Buff)-len-1, Fmt, marker );
   }
   len+=_snprintf(&Buff[len],sizeof(Buff)-len-1,"\r\n");
   printf("%s",Buff);
}

bool CDynPatcher::Init(const char *LibName,bool ForceLoad)
{
   if (!LibName)
   {
      szLibName = "<<===NO LIBRARY NAME===>>";
      return false;
   }

   if(!LoadLib(LibName,ForceLoad))
   {
      DynErr(false,"Unable to load \"%s\"",LibName);
      return false;
   }
#ifdef WIN32
   if(!ParseGenericDllData_PE())
   {
      DynErr(false,"Failed to parse \"%s\"",szLibName);
      return false;
   }
   DynMsg("\"%s\" parsed",szLibName);
#else
	FILE *fl = fopen(szLibName, "rb");
	int LibSize;
	void* LibBuf;
	if (fl == NULL) 
	{
		DynErr(false,"Failed to open '%s' for read\n", szLibName);
		return false;
	}

	fseek(fl, 0, SEEK_END);
	LibSize = ftell(fl);
	fseek(fl, 0, SEEK_SET);


	if (LibSize < 0)
	LibSize = 0;
	LibBuf = malloc(LibSize + 4);
	fread(LibBuf, 1, LibSize, fl);
	fclose(fl);
   if(!ParseGenericDllData_ELF(LibBuf, LibSize))
   {
      DynErr(false,"Failed to parse \"%s\"",szLibName);
      return false;
   }
#endif
   return true;
}


bool CDynPatcher::Init(const wchar_t *LibName, bool ForceLoad /*= false*/)
{
	return 0;
   static char UTF8LibName[MAX_PATH];
   //Q_UnicodeToUTF8(LibName, UTF8LibName, MAX_PATH-1);
   return Init(UTF8LibName, ForceLoad);
}

bool CDynPatcher::Init(void *FuncAddr)
{
   char szTmpName[400];
   sprintf(szTmpName, "Unk_load_by_func_addr_%p", FuncAddr);
   szLibName = new  char[strlen(szTmpName) + 1];
   strcpy(szLibName, szTmpName);
   bSelfLoaded = false;
#ifdef _WIN32
   MEMORY_BASIC_INFORMATION mem;
   VirtualQuery(FuncAddr, &mem, sizeof(mem));
   szTmpName[0] = 0;
   GetModuleFileNameA(reinterpret_cast<HMODULE>(mem.AllocationBase ), szTmpName, sizeof(szTmpName) - 1);
 
   if (szTmpName[0] != 0)
   {
      delete[]szLibName;
      szLibName = new char[strlen(CSectionData::GetFileName(szTmpName)) + 1];
      strcpy(szLibName, CSectionData::GetFileName(szTmpName));
   }
   IMAGE_DOS_HEADER *dos = (IMAGE_DOS_HEADER*)mem.AllocationBase;
   IMAGE_NT_HEADERS *pe = (IMAGE_NT_HEADERS*)((unsigned long)dos + (unsigned long)dos->e_lfanew);
   
   if (pe->Signature == IMAGE_NT_SIGNATURE)
   {
      this->DllHandler = mem.AllocationBase;
      if (!ParseGenericDllData_PE())
      {
         DynErr(false, "Failed to parse \"%s\"", szLibName);
         return false;
      }
      DynMsg("\"%s\" parsed",szLibName);
   }
#else
   Dl_info info;
   if (dladdr(FuncAddr, &info) && info.dli_fbase &&info.dli_fname)
   {
      delete [] szLibName;
      szLibName = new  char[strlen(info.dli_fname) + 1];
      strcpy(szLibName, info.dli_fname);
      bool ParseOK=false;
      size_t LoadLibSize=0;
      DllBase = info.dli_fbase;
      LoadLibSize = (size_t)GetBaseLen(DllBase);
      DllHandler = dlopen(info.dli_fname, RTLD_NOW);
      dlclose(DllHandler);
      DynMsg("Found library \"%s\" at addr %p. Base=%p, size=%x, handler=%p",szLibName,FuncAddr,DllBase,LoadLibSize,DllHandler);
      FILE *fl = fopen(szLibName, "rb");
      int LibSize;
      void* LibBuf;
      if (fl)
      {  
         fseek(fl, 0, SEEK_END);
         LibSize = ftell(fl);
         fseek(fl, 0, SEEK_SET);
         DynMsg("Reading \"%s\" as file. Size=%x",szLibName,LibSize);

         if (LibSize < 0)
            LibSize = 0;
         LibBuf = malloc(LibSize + 4);
         fread(LibBuf, 1, LibSize, fl);
         fclose(fl);
         ParseOK=ParseGenericDllData_ELF(LibBuf, LibSize);
         free(LibBuf);       
      }
      else
      {
         DynMsg("Unable to read \"%s\" as file. Trying to use information from Dl_info.",szLibName);
         ParseOK=ParseGenericDllData_ELF(DllBase, LoadLibSize);
      }
      if (!ParseOK)
      {
         DynErr(false, "Failed to parse \"%s\"", szLibName);
         return false;
      }
   }
#endif
   else
   {
      DynErr(false, "Failed find library at %p",FuncAddr);
      return false;
   }
   return true;
}