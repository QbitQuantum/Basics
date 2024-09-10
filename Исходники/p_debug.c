void _debug_break(void) 
{
#if defined(PIPE_ARCH_X86) && defined(PIPE_CC_GCC)
   __asm("int3");
#elif defined(PIPE_ARCH_X86) && defined(PIPE_CC_MSVC)
   _asm {int 3};
#elif defined(PIPE_SUBSYSTEM_WINDOWS_DISPLAY)
   EngDebugBreak();
#else
   abort();
#endif
}


#ifdef PIPE_SUBSYSTEM_WINDOWS_DISPLAY
static const char *
find(const char *start, const char *end, char c) 
{
   const char *p;
   for(p = start; !end || p != end; ++p) {
      if(*p == c)
	 return p;
      if(*p < 32)
	 break;
   }
   return NULL;
}

static int 
compare(const char *start, const char *end, const char *s)
{
   const char *p, *q;
   for(p = start, q = s; p != end && *q != '\0'; ++p, ++q) {
      if(*p != *q)
	 return 0;
   }
   return p == end && *q == '\0';
}

static void 
copy(char *dst, const char *start, const char *end, size_t n) 
{
   const char *p;
   char *q;
   for(p = start, q = dst, n = n - 1; p != end && n; ++p, ++q, --n)
      *q = *p;
   *q = '\0';
}
#endif


static INLINE const char *
_debug_get_option(const char *name)
{
#if defined(PIPE_SUBSYSTEM_WINDOWS_DISPLAY)
   /* EngMapFile creates the file if it does not exists, so it must either be
    * disabled on release versions (or put in a less conspicuous place). */
#ifdef DEBUG
   const char *result = NULL;
   ULONG_PTR iFile = 0;
   const void *pMap = NULL;
   const char *sol, *eol, *sep;
   static char output[1024];
   
   pMap = EngMapFile(L"\\??\\c:\\gallium.cfg", 0, &iFile);
   if(pMap) {
      sol = (const char *)pMap;
      while(1) {
	 /* TODO: handle LF line endings */
	 eol = find(sol, NULL, '\r');
	 if(!eol || eol == sol)
	    break;
	 sep = find(sol, eol, '=');
	 if(!sep)
	    break;
	 if(compare(sol, sep, name)) {
	    copy(output, sep + 1, eol, sizeof(output));
	    result = output;
	    break;
	 }
	 sol = eol + 2;
      }
      EngUnmapFile(iFile);
   }
   return result;
#else
   return NULL;
#endif
#elif defined(PIPE_SUBSYSTEM_WINDOWS_CE) || defined(PIPE_SUBSYSTEM_WINDOWS_MINIPORT) 
   /* TODO: implement */
   return NULL;
#else
   return getenv(name);
#endif
}

const char *
debug_get_option(const char *name, const char *dfault)
{
   const char *result;

   result = _debug_get_option(name);
   if(!result)
      result = dfault;
      
   debug_printf("%s: %s = %s\n", __FUNCTION__, name, result ? result : "(null)");
   
   return result;
}

boolean
debug_get_bool_option(const char *name, boolean dfault)
{
   const char *str = _debug_get_option(name);
   boolean result;
   
   if(str == NULL)
      result = dfault;
   else if(!util_strcmp(str, "n"))
      result = FALSE;
   else if(!util_strcmp(str, "no"))
      result = FALSE;
   else if(!util_strcmp(str, "0"))
      result = FALSE;
   else if(!util_strcmp(str, "f"))
      result = FALSE;
   else if(!util_strcmp(str, "false"))
      result = FALSE;
   else
      result = TRUE;

   debug_printf("%s: %s = %s\n", __FUNCTION__, name, result ? "TRUE" : "FALSE");
   
   return result;
}


long
debug_get_num_option(const char *name, long dfault)
{
   long result;
   const char *str;
   
   str = _debug_get_option(name);
   if(!str)
      result = dfault;
   else {
      long sign;
      char c;
      c = *str++;
      if(c == '-') {
	 sign = -1;
	 c = *str++;
      } 
      else {
	 sign = 1;
      }
      result = 0;
      while('0' <= c && c <= '9') {
	 result = result*10 + (c - '0');
	 c = *str++;
      }
      result *= sign;
   }
   
   debug_printf("%s: %s = %li\n", __FUNCTION__, name, result);

   return result;
}