/****************************************************************************
#ifdef DOCUMENTATION
.MODULE       errorPrintf
.LIBRARY      portable
.TYPE         función
.DESCRIPTION  imprime y hace exit(1) de un modo portable
.SYSTEM       DOS, UNIX
.APPLICATION  portable
.ARGUMENTS    int errorPrintf(char *mens,...)
              mens:       formato printf
              ...:        argumentos variables
.NARRATIVE    Sustituye a la funcion 'printf', permitiendo
               salidas por pantallas portables
.RETURNS      EOF si hay error
              número de bytes, en caso contrario
.AUTHOR       JMMM Juan M. Montero Martínez
.LANGUAGE     C
.ENDOC        END DOCUMENTATION
#endif
****************************************************************************/
int errorPrintf(char *mens,...)
  {
  int auxiliar;
  va_list arg_ptr;

  va_start(arg_ptr, mens);
  auxiliar = vsprintf((char *) aux_str, mens, arg_ptr);
  va_end(arg_ptr);
#if defined(__WIN32__) && defined(__CONSOLE__)
  int valor_tonto=__CONSOLE__;
  printf("CONSOLA %d\nERROR\n%s\nPulse retorno para continuar", valor_tonto,aux_str);
  OurBioskey(0);
#elif defined(_Windows)
//  MessageBox(NULL, aux_str, "ERROR", /*MB_SYSTEMMODAL |*/ MB_OK);
  fcloseall();
  FatalAppExit(0,aux_str);
#else
  fprintf(stderr, "\nERROR\n%s\nPulse retorno para continuar", aux_str);
  OurBioskey(0);
#endif
  fcloseall();
  exit(1);
  return auxiliar;
  }