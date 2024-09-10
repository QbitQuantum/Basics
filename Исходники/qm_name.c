/*********************************************************************
 Write the actual qmaster into the master_file
 -> master_file and master_host
 <- return -1   error in err_str
            0   means OK
  
   NOTES
      MT-NOTE: write_qm_name() is MT safe
 *********************************************************************/
int write_qm_name(
const char *master_host,
const char *master_file,
char *err_str 
) {
   FILE *fp;

   if (!(fp = fopen(master_file, "w"))) {
      if (err_str)
         sprintf(err_str, MSG_GDI_OPENWRITEMASTERHOSTNAMEFAILED_SS, 
                 master_file, strerror(errno));
      return -1;
   }

   if (fprintf(fp, "%s\n", master_host) == EOF) {
      if (err_str)
         sprintf(err_str, MSG_GDI_WRITEMASTERHOSTNAMEFAILED_S , 
                 master_file);
      FCLOSE(fp);
      return -1;
   } 

   FCLOSE(fp);
   return 0;
FCLOSE_ERROR:
   return -1;
}