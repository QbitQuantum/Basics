/*----------------------------------------------------------------------
 * host_in_file
 * look if resolved host is in "file"
 * return  
 *         0 if present 
 *         1 if not
 *        -1 error occured
 *----------------------------------------------------------------------*/
static int host_in_file(
const char *host,
const char *file 
) {
   FILE *fp;
   char buf[512], *cp;

   DENTER(TOP_LAYER, "host_in_file");

   fp = fopen(file, "r");
   if (!fp) {
      DRETURN(-1);
   }

   while (fgets(buf, sizeof(buf), fp)) {
      for (cp = strtok(buf, " \t\n,"); cp; cp = strtok(NULL, " \t\n,")) {
         char* resolved_host = NULL;
         cl_com_cached_gethostbyname(cp,&resolved_host,NULL,NULL,NULL);
         if (resolved_host) {
            if (!sge_hostcmp(host, resolved_host )) {
               FCLOSE(fp);
               sge_free(&resolved_host);
               DRETURN(0);
            }
            sge_free(&resolved_host);
         }
      }      
   }

   FCLOSE(fp);
   DRETURN(1);

FCLOSE_ERROR:
   DRETURN(0);
}