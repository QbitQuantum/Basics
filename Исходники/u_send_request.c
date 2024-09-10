static size_t smtp_payload_source(void * ptr, size_t size, size_t nmemb, void * userp) {
  struct upload_status *upload_ctx = (struct upload_status *)userp;
  char * data = NULL;
  size_t len = 0;

  if ((size == 0) || (nmemb == 0) || ((size*nmemb) < 1)) {
    return 0;
  }

  if (upload_ctx->lines_read == MAIL_DATE) {
    time_t now;
    time(&now);
    data = malloc(128*sizeof(char));
    if (data == NULL) {
      y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error allocating memory for MAIL_DATE\n");
      return 0;
    } else {
      strftime(data, 128, "Date: %a, %d %b %Y %T %z\r\n", gmtime(&now));
      len = strlen(data);
    }
  } else if (upload_ctx->lines_read == MAIL_TO) {
    data = msprintf("To: %s\r\n", upload_ctx->to);
    if (data == NULL) {
      y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error allocating memory for MAIL_TO\n");
      return 0;
    }
    len = strlen(data);
  } else if (upload_ctx->lines_read == MAIL_FROM) {
    data = msprintf("From: %s\r\n", upload_ctx->from);
    if (data == NULL) {
      y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error allocating memory for MAIL_FROM\n");
      return 0;
    }
    len = strlen(data);
  } else if (upload_ctx->lines_read == MAIL_CC && upload_ctx->cc) {
    data = msprintf("Cc: %s\r\n", upload_ctx->cc);
    if (data == NULL) {
      y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error allocating memory for MAIL_CC\n");
      return 0;
    }
    len = strlen(data);
  } else if (upload_ctx->lines_read == MAIL_SUBJECT) {
    data = msprintf("Subject: %s\r\n", upload_ctx->subject);
    if (data == NULL) {
      y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error allocating memory for MAIL_SUBJECT\n");
      return 0;
    }
    len = strlen(data);
  } else if (upload_ctx->lines_read == MAIL_DATA) {
    data = msprintf("Content-Type: text/plain; charset=utf-8\r\n\r\n%s\r\n", upload_ctx->data);
    if (data == NULL) {
      y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error allocating memory for MAIL_DATA\n");
      return 0;
    }
    len = strlen(data);
  }

  if (upload_ctx->lines_read != MAIL_END) {
    memcpy(ptr, data, (len+1));
    upload_ctx->lines_read++;
    
    // Skip next if it's cc and there is no cc
    if (upload_ctx->lines_read == MAIL_CC && !upload_ctx->cc) {
      upload_ctx->lines_read++;
    }
    free(data);
 
    return len;
  } else if (upload_ctx->lines_read == MAIL_END) {
    return 0;
  }

  y_log_message(Y_LOG_LEVEL_ERROR, "Ulfius - Error setting mail payload, len is %d, lines_read is %d", len, upload_ctx->lines_read);
  return 0;
}