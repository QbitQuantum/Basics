/*--------------------------------------------------------------
 * Name:   get_qmaster_heartbeat
 * Descr:  get number found in qmaster heartbeat file
 * Return: > 0 number found in given heartbeat file 
 *         -1   can't open file 
 *         -2   can't read entry
 *         -3   read timeout
 *         -4   fclose error
 *-------------------------------------------------------------*/
int get_qmaster_heartbeat( char *file, int read_timeout ) {
   FILE *fp   = NULL;
   int hb     = 0; 
   struct timeval start_time;
   struct timeval end_time;
   unsigned long read_time;

   DENTER(TOP_LAYER, "get_qmaster_heartbeat");

   if (file == NULL) {
      ERROR((SGE_EVENT, SFNMAX, MSG_HEART_NO_FILENAME));
      DEXIT;
      return -1;
   }

   gettimeofday(&start_time,NULL);

   fp = fopen(file, "r");
   if (!fp) {
      ERROR((SGE_EVENT, MSG_HEART_CANNOTOPEN_SS, file, strerror(errno))); 
      DEXIT;
      return -1;
   }

   if (fscanf(fp, "%d", &hb) != 1) {
      FCLOSE(fp);
      ERROR((SGE_EVENT, MSG_HEART_CANNOT_READ_FILE_S, strerror(errno)));
      DEXIT;
      return -2;
   }

   FCLOSE(fp);

   /* This is only for testsuite testing */
   if (sge_testmode_timeout_value > 0 && hb == sge_testmode_timeout_at_heartbeat ) {
      sleep(sge_testmode_timeout_value);
   }

   gettimeofday(&end_time,NULL);
   read_time = end_time.tv_sec - start_time.tv_sec;
   if (read_time > read_timeout) {
      ERROR((SGE_EVENT, MSG_HEART_READ_TIMEOUT_S, file));
      DEXIT;
      return -3;
   }

   DEXIT;
   return hb;
FCLOSE_ERROR:
   ERROR((SGE_EVENT, MSG_HEART_CLOSE_ERROR_SS, file, strerror(errno)));
   DEXIT;
   return -4;
}