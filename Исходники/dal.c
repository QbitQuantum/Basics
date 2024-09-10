// Upon return no more I/O is possible. The stream is closed.
//
// If ne_close indicates a recoverable error, then the object is
// logged to the "degraded object log".
int mc_sync(DAL_Context* ctx) {
   ENTRY();

   ObjectStream* os         = MC_OS(ctx);
   ne_handle     handle     = MC_HANDLE(ctx);
   MC_Config*    config     = MC_CONFIG(ctx);
   MC_Context*   mc_context = MC_CONTEXT(ctx);
   
   if(! (os->flags & OSF_OPEN)) {
      LOG(LOG_ERR, "%s isn't open\n", os->url);
      errno = EINVAL;
      return -1;
   }

   // the result of close for a handle opened for reading is an
   // indicator of whether the data is degraded and, if so, which
   // block is corrupt or missing.
   int error_pattern = ne_close(handle);
   if(error_pattern > 0) {
      // Keeping the log message as well as writing to the degraded
      // object file for debugging purposes.
      LOG(LOG_INFO, "WARNING: Object %s degraded. Error pattern: 0x%x."
          " (N: %d, E: %d, Start: %d).\n",
          mc_context->path_template, error_pattern,
          config->n, config->e, mc_context->start_block);
      // we shouldn't need more then 512 bytes to hold the extra data
      // needed for rebuild
      char buf[MC_MAX_LOG_LEN];
      snprintf(buf, MC_MAX_LOG_LEN,
               MC_DEGRADED_LOG_FORMAT, mc_context->path_template,
               config->n, config->e,
               mc_context->start_block, error_pattern,
               MC_FH(ctx)->info.pre.repo->name,
               mc_context->pod, mc_context->cap);
      WAIT(&config->lock);
      // If the degraded log file has not already been opened, open it now.
      if(config->degraded_log_fd == -1) {
         config->degraded_log_fd =
            open_degraded_object_log(config->degraded_log_path);
         if(config->degraded_log_fd < 0) {
            LOG(LOG_ERR, "failed to open degraded log file\n");
         }
         else {
            // If we successfully opened it, then free the resources
            // used to store the path.
            free(config->degraded_log_path);
            config->degraded_log_path = NULL;
         }
      }

      if(write(config->degraded_log_fd, buf, strlen(buf))
         != strlen(buf)) {
         LOG(LOG_ERR, "Failed to write to degraded object log\n");
         // theoretically the data is still safe, so we can just log
         // and ignore the failure.
      }
      POST(&config->lock);
   }
   else if(error_pattern < 0) {
      // close the stream, a failed sync renders the ne_handle
      // invalid calling mc_close should prevent marfs from ever
      // trying to use it again.
      mc_close(ctx);
      os->flags |= OSF_ERRORS;
      LOG(LOG_ERR, "ne_close failed on %s", mc_context->path_template);
      return -1;
   }

   EXIT();
   return 0;
}