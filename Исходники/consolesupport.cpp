// Initialize the console, depending on the OS and language/code page settings
void init_console()
{
	#ifdef WIN32
   #ifdef CH_USE_UNICODE
   SetConsoleOutputCP(65001); // use UTF-8 (Unicode)
   setlocale(LC_ALL,"English_United States.437"); // Windows does not support UTF-8/Unicode for setlocale, sorry
   #endif
   #ifdef CH_USE_CP437
   SetConsoleOutputCP(437); // use Code Page 437 (US English code page made by IBM for DOS)
   setlocale(LC_ALL,"English_United States.437");
   #endif
   #ifdef CH_USE_ASCII_HACK
   SetConsoleOutputCP(437); // use Code Page 437 (US English code page made by IBM for DOS)
   setlocale(LC_ALL,"English_United States.437");
   #endif
   _setmbcp(_MB_CP_LOCALE); // use same code page as multibyte code page
   #else // WIN32
   #ifdef CH_USE_UNICODE
   setlocale(LC_ALL,"en_US.UTF-8"); // POSIX-compliant OSes DO support UTF-8/Unicode for setlocale
   #endif
   #ifdef CH_USE_CP437
   setlocale(LC_ALL,"en_US.CP437");
   #endif
   #ifdef CH_USE_ASCII_HACK
   setlocale(LC_ALL,"en_US.CP437");
   #endif
   #endif // WIN32
   #ifdef CH_USE_UNICODE
   setup_unicode();
   #endif
}