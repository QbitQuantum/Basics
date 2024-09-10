/**
 * Library cleanup
 */
extern "C" void  R_unload_stringi(DllInfo*)
{
   // see http://bugs.icu-project.org/trac/ticket/10897
   // and https://github.com/Rexamine/stringi/issues/78
//   fprintf(stdout, "!NDEBUG: ************************************************\n");
//   fprintf(stdout, "!NDEBUG: Dynamic library 'stringi' unloaded.\n");
//   fprintf(stdout, "!NDEBUG: ************************************************\n");
   u_cleanup();
}