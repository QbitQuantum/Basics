bool MonitorItem::get_job_defaults(struct JobDefaults &job_defs)
{
   int stat;
   char *def;
   BSOCK *dircomm;
   bool rtn = false;
   QString scmd = QString(".defaults job=\"%1\"").arg(job_defs.job_name);

   if (job_defs.job_name == "") {
      return rtn;
   }

   if (!doconnect()) {
      return rtn;
   }
   dircomm = d->DSock;
   dircomm->fsend("%s", scmd.toUtf8().data());

   while ((stat = dircomm->recv()) > 0) {
      def = strchr(dircomm->msg, '=');
      if (!def) {
         continue;
      }
      /* Pointer to default value */
      *def++ = 0;
      strip_trailing_newline(def);

      if (strcmp(dircomm->msg, "job") == 0) {
         if (strcmp(def, job_defs.job_name.toUtf8().data()) != 0) {
            goto bail_out;
         }
         continue;
      }
      if (strcmp(dircomm->msg, "pool") == 0) {
         job_defs.pool_name = def;
         continue;
      }
      if (strcmp(dircomm->msg, "messages") == 0) {
         job_defs.messages_name = def;
         continue;
      }
      if (strcmp(dircomm->msg, "client") == 0) {
         job_defs.client_name = def;
         continue;
      }
      if (strcmp(dircomm->msg, "storage") == 0) {
         job_defs.store_name = def;
         continue;
      }
      if (strcmp(dircomm->msg, "where") == 0) {
         job_defs.where = def;
         continue;
      }
      if (strcmp(dircomm->msg, "level") == 0) {
         job_defs.level = def;
         continue;
      }
      if (strcmp(dircomm->msg, "type") == 0) {
         job_defs.type = def;
         continue;
      }
      if (strcmp(dircomm->msg, "fileset") == 0) {
         job_defs.fileset_name = def;
         continue;
      }
      if (strcmp(dircomm->msg, "catalog") == 0) {
         job_defs.catalog_name = def;
         continue;
      }
      if (strcmp(dircomm->msg, "enabled") == 0) {
         job_defs.enabled = *def == '1' ? true : false;
         continue;
      }
   }
   rtn = true;
   /* Fall through wanted */
bail_out:
   return rtn;
}