/*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ main() $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
int
main(int argc, char *argv[])
{
#ifdef _WITH_BURST_2
   int              cb2_ret;
#endif
   int              current_toggle,
                    exit_status = TRANSFER_SUCCESS,
                    j,
                    fd,
                    status,
                    loops,
                    rest,
                    blocksize,
                    *wmo_counter,
                    wmo_counter_fd = -1;
#ifdef WITH_ARCHIVE_COPY_INFO
   unsigned int     archived_copied = 0;
#endif
   off_t            no_of_bytes;
   time_t           connected,
#ifdef _WITH_BURST_2
                    diff_time,
#endif
                    end_transfer_time_file,
                    start_transfer_time_file = 0,
                    last_update_time,
                    now;
#ifdef _OUTPUT_LOG
   clock_t          end_time = 0,
                    start_time = 0;
   struct tms       tmsdummy;
#endif
   char             *p_file_name_buffer,
                    *buffer,
                    fullname[MAX_PATH_LENGTH + 1],
                    file_path[MAX_PATH_LENGTH];
   clock_t          clktck;
   struct stat      stat_buf;
   struct job       *p_db;
#ifdef SA_FULLDUMP
   struct sigaction sact;
#endif

   CHECK_FOR_VERSION(argc, argv);

#ifdef SA_FULLDUMP
   /*
    * When dumping core sure we do a FULL core dump!
    */
   sact.sa_handler = SIG_DFL;
   sact.sa_flags = SA_FULLDUMP;
   sigemptyset(&sact.sa_mask);
   if (sigaction(SIGSEGV, &sact, NULL) == -1)
   {
      system_log(ERROR_SIGN, __FILE__, __LINE__,
                 "sigaction() error : %s", strerror(errno));
      exit(INCORRECT);
   }
#endif

   /* Do some cleanups when we exit. */
   if (atexit(sf_wmo_exit) != 0)
   {
      system_log(ERROR_SIGN, __FILE__, __LINE__,
                 "Could not register exit function : %s", strerror(errno));
      exit(INCORRECT);
   }

   /* Initialise variables. */
   local_file_counter = 0;
   files_to_send = init_sf(argc, argv, file_path, WMO_FLAG);
   p_db = &db;
   if ((clktck = sysconf(_SC_CLK_TCK)) <= 0)
   {
      system_log(ERROR_SIGN, __FILE__, __LINE__,
                 "Could not get clock ticks per second : %s",
                 strerror(errno));
      exit(INCORRECT);
   }
   if (fsa->trl_per_process > 0)
   {
      if (fsa->trl_per_process < fsa->block_size)
      {
         blocksize = fsa->trl_per_process;
      }
      else
      {
         blocksize = fsa->block_size;
      }
   }
   else
   {
      blocksize = fsa->block_size;
   }

   if ((signal(SIGINT, sig_kill) == SIG_ERR) ||
       (signal(SIGQUIT, sig_exit) == SIG_ERR) ||
       (signal(SIGTERM, SIG_IGN) == SIG_ERR) ||
       (signal(SIGSEGV, sig_segv) == SIG_ERR) ||
       (signal(SIGBUS, sig_bus) == SIG_ERR) ||
       (signal(SIGHUP, SIG_IGN) == SIG_ERR) ||
       (signal(SIGPIPE, SIG_IGN) == SIG_ERR))
   {
      system_log(ERROR_SIGN, __FILE__, __LINE__,
                 "signal() error : %s", strerror(errno));
      exit(INCORRECT);
   }

   /* Now determine the real hostname. */
   if (db.toggle_host == YES)
   {
      if (fsa->host_toggle == HOST_ONE)
      {
         (void)strcpy(db.hostname, fsa->real_hostname[HOST_TWO - 1]);
         current_toggle = HOST_TWO;
      }
      else
      {
         (void)strcpy(db.hostname, fsa->real_hostname[HOST_ONE - 1]);
         current_toggle = HOST_ONE;
      }
   }
   else
   {
      (void)strcpy(db.hostname,
                   fsa->real_hostname[(int)(fsa->host_toggle - 1)]);
      current_toggle = (int)fsa->host_toggle;
   }

   /* Connect to remote WMO-server. */
#ifdef FTP_CTRL_KEEP_ALIVE_INTERVAL
   if (fsa->protocol_options & AFD_TCP_KEEPALIVE)
   {
      timeout_flag = transfer_timeout - 5;
      if (timeout_flag < MIN_KEEP_ALIVE_INTERVAL)
      {
         timeout_flag = MIN_KEEP_ALIVE_INTERVAL;
      }
   }
#else
   timeout_flag = OFF;
#endif
   if ((status = wmo_connect(db.hostname, db.port, db.sndbuf_size)) != SUCCESS)
   {
      trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                "WMO connection to <%s> at port %d failed (%d).",
                db.hostname, db.port, status);
      exit(eval_timeout(CONNECT_ERROR));
   }
   else
   {
      if (fsa->debug > NORMAL_MODE)
      {
         trans_db_log(INFO_SIGN, __FILE__, __LINE__, NULL,
                      "Connected to port %d.", db.port);
      }
   }
   connected = time(NULL);

   /* Inform FSA that we have finished connecting and */
   /* will now start to transfer data.                */
   if (gsf_check_fsa(p_db) != NEITHER)
   {
#ifdef LOCK_DEBUG
      lock_region_w(fsa_fd, db.lock_offset + LOCK_CON, __FILE__, __LINE__);
#else
      lock_region_w(fsa_fd, db.lock_offset + LOCK_CON);
#endif
      fsa->job_status[(int)db.job_no].connect_status = WMO_ACTIVE;
      fsa->job_status[(int)db.job_no].no_of_files = files_to_send;
      fsa->connections += 1;
#ifdef LOCK_DEBUG
      unlock_region(fsa_fd, db.lock_offset + LOCK_CON, __FILE__, __LINE__);
#else
      unlock_region(fsa_fd, db.lock_offset + LOCK_CON);
#endif
   }

   /* Allocate buffer to read data from the source file. */
   if ((buffer = malloc(blocksize + 1 + 4 /* For bulletin end. */)) == NULL)
   {
      system_log(ERROR_SIGN, __FILE__, __LINE__,
                 "malloc() error : %s", strerror(errno));
      exit(ALLOC_ERROR);
   }

   if (db.special_flag & WITH_SEQUENCE_NUMBER)
   {
      char counter_file_name[MAX_FILENAME_LENGTH];

      (void)snprintf(counter_file_name, MAX_FILENAME_LENGTH, "/%s.%d", db.host_alias, db.port);
      if ((wmo_counter_fd = open_counter_file(counter_file_name, &wmo_counter)) < 0)
      {
         system_log(ERROR_SIGN, __FILE__, __LINE__,
                    "Failed to open counter file `%s'.", counter_file_name);
      }
   }

#ifdef _WITH_BURST_2
   do
   {
      if (burst_2_counter > 0)
      {
         if (fsa->debug > NORMAL_MODE)
         {
            trans_db_log(INFO_SIGN, __FILE__, __LINE__, NULL, "WMO Bursting.");
         }
      }
#endif

      /* Send all files. */
      p_file_name_buffer = file_name_buffer;
      p_file_size_buffer = file_size_buffer;
      last_update_time = time(NULL);
      local_file_size = 0;
      for (files_send = 0; files_send < files_to_send; files_send++)
      {
         (void)snprintf(fullname, MAX_PATH_LENGTH + 1, "%s/%s",
                        file_path, p_file_name_buffer);

         if (*p_file_size_buffer > 0)
         {
            int end_length = 0,
                header_length = 0,
                length_type_indicator = 10;

            if (gsf_check_fsa(p_db) != NEITHER)
            {
               fsa->job_status[(int)db.job_no].file_size_in_use = *p_file_size_buffer;
               (void)strcpy(fsa->job_status[(int)db.job_no].file_name_in_use,
                            p_file_name_buffer);
            }

            /* Open local file. */
#ifdef O_LARGEFILE
            if ((fd = open(fullname, O_RDONLY | O_LARGEFILE)) == -1)
#else
            if ((fd = open(fullname, O_RDONLY)) == -1)
#endif
            {
               trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                         "Failed to open local file `%s' : %s",
                         fullname, strerror(errno));
               wmo_quit();
               exit(OPEN_LOCAL_ERROR);
            }
            if (fsa->debug > NORMAL_MODE)
            {
                  trans_db_log(INFO_SIGN, __FILE__, __LINE__, NULL,
                               "Open local file `%s'", fullname);
            }

#ifdef _OUTPUT_LOG
            if (db.output_log == YES)
            {
               start_time = times(&tmsdummy);
            }
#endif

            /*
             * When the contents does not contain a bulletin header
             * it must be stored in the file name.
             */
            if (db.special_flag & FILE_NAME_IS_HEADER)
            {
               int  space_count;
               char *ptr = p_file_name_buffer;

               buffer[length_type_indicator] = 1; /* SOH */
               buffer[length_type_indicator + 1] = '\015'; /* CR */
               buffer[length_type_indicator + 2] = '\015'; /* CR */
               buffer[length_type_indicator + 3] = '\012'; /* LF */
               header_length = 4;
               space_count = 0;

               if (wmo_counter_fd > 0)
               {
                  if (next_counter(wmo_counter_fd, wmo_counter,
                                   MAX_WMO_COUNTER) < 0)
                  {
                     close_counter_file(wmo_counter_fd, &wmo_counter);
                     wmo_counter_fd = -1;
                     wmo_counter = NULL;
                     system_log(ERROR_SIGN, __FILE__, __LINE__,
                                "Failed to get next WMO counter.");
                  }
                  else
                  {
                     if (*wmo_counter < 10)
                     {
                        buffer[length_type_indicator + header_length] = '0';
                        buffer[length_type_indicator + header_length + 1] = '0';
                        buffer[length_type_indicator + header_length + 2] = *wmo_counter + '0';
                     }
                     else if (*wmo_counter < 100)
                          {
                             buffer[length_type_indicator + header_length] = '0';
                             buffer[length_type_indicator + header_length + 1] = (*wmo_counter / 10) + '0';
                             buffer[length_type_indicator + header_length + 2] = (*wmo_counter % 10) + '0';
                          }
                     else if (*wmo_counter < 1000)
                          {
                             buffer[length_type_indicator + header_length] = ((*wmo_counter / 100) % 10) + '0';
                             buffer[length_type_indicator + header_length + 1] = ((*wmo_counter / 10) % 10) + '0';
                             buffer[length_type_indicator + header_length + 2] = (*wmo_counter % 10) + '0';
                          }
                     buffer[length_type_indicator + header_length + 3] = '\015'; /* CR */
                     buffer[length_type_indicator + header_length + 4] = '\015'; /* CR */
                     buffer[length_type_indicator + header_length + 5] = '\012'; /* LF */
                     header_length += 6;
                  }
               } /* if (wmo_counter_fd > 0) */

               for (;;)
               {
                  while ((*ptr != '_') && (*ptr != '-') && (*ptr != ' ') &&
                         (*ptr != '\0') && (*ptr != '.') && (*ptr != ';'))
                  {
                     buffer[length_type_indicator + header_length] = *ptr;
                     header_length++; ptr++;
                  }
                  if ((*ptr == '\0') || (*ptr == '.') || (*ptr == ';'))
                  {
                     break;
                  }
                  else
                  {
                     if (space_count == 2)
                     {
                        if ((isalpha((int)(*(ptr + 1)))) &&
                            (isalpha((int)(*(ptr + 2)))) &&
                            (isalpha((int)(*(ptr + 3)))))
                        {
                           buffer[length_type_indicator + header_length] = ' ';
                           buffer[length_type_indicator + header_length + 1] = *(ptr + 1);
                           buffer[length_type_indicator + header_length + 2] = *(ptr + 2);
                           buffer[length_type_indicator + header_length + 3] = *(ptr + 3);
                           header_length += 4;
                        }
                        break;
                     }
                     else
                     {
                        buffer[length_type_indicator + header_length] = ' ';
                        header_length++; ptr++; space_count++;
                     }
                  }
               } /* for (;;) */
               buffer[length_type_indicator + header_length] = '\015'; /* CR */
               buffer[length_type_indicator + header_length + 1] = '\015'; /* CR */
               buffer[length_type_indicator + header_length + 2] = '\012'; /* LF */
               header_length += 3;
               end_length = 4;
            }

            /* Read (local) and write (remote) file. */
            no_of_bytes = 0;
            loops = (length_type_indicator + header_length + *p_file_size_buffer) / blocksize;
            rest = (length_type_indicator + header_length + *p_file_size_buffer) % blocksize;

            if ((db.special_flag & FILE_NAME_IS_HEADER) && (rest == 0))
            {
               loops--;
               rest = blocksize;
            }

            /* Write length and type indicator. */
            (void)snprintf(buffer, 9, "%08lu",
                           (unsigned long)(*p_file_size_buffer + header_length + end_length));
            if (db.transfer_mode == 'I')
            {
               buffer[length_type_indicator - 2] = 'B';
               buffer[length_type_indicator - 1] = 'I';
            }
            else if (db.transfer_mode == 'A')
                 {
                    buffer[length_type_indicator - 2] = 'A';
                    buffer[length_type_indicator - 1] = 'N';
                 }
                 else
                 {
                    buffer[length_type_indicator - 2] = 'F';
                    buffer[length_type_indicator - 1] = 'X';
                 }

            if (fsa->trl_per_process > 0)
            {
               init_limit_transfer_rate();
            }
            if (fsa->protocol_options & TIMEOUT_TRANSFER)
            {
               start_transfer_time_file = time(NULL);
            }

            for (;;)
            {
               for (j = 0; j < loops; j++)
               {
#ifdef _SIMULATE_SLOW_TRANSFER
                  (void)sleep(_SIMULATE_SLOW_TRANSFER);
#endif
                  if ((status = read(fd,
                                     (buffer + length_type_indicator + header_length),
                                     (blocksize - length_type_indicator - header_length))) != (blocksize - length_type_indicator - header_length))
                  {
                     trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                               "Could not read() local file `%s' : %s",
                               fullname, strerror(errno));
                     wmo_quit();
                     exit(READ_LOCAL_ERROR);
                  }
                  if ((status = wmo_write(buffer, blocksize)) != SUCCESS)
                  {
                     trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                               "Failed to write block from file `%s' to remote port %d [%d].",
                               p_file_name_buffer, db.port, status);
                     wmo_quit();
                     exit(eval_timeout(WRITE_REMOTE_ERROR));
                  }
                  if (fsa->trl_per_process > 0)
                  {
                     limit_transfer_rate(blocksize, fsa->trl_per_process,
                                         clktck);
                  }

                  no_of_bytes += blocksize;

                  if (gsf_check_fsa(p_db) != NEITHER)
                  {
                     fsa->job_status[(int)db.job_no].file_size_in_use_done = no_of_bytes;
                     fsa->job_status[(int)db.job_no].file_size_done += blocksize;
                     fsa->job_status[(int)db.job_no].bytes_send += blocksize;
                     if (fsa->protocol_options & TIMEOUT_TRANSFER)
                     {
                        end_transfer_time_file = time(NULL);
                        if (end_transfer_time_file < start_transfer_time_file)
                        {
                           start_transfer_time_file = end_transfer_time_file;
                        }
                        else
                        {
                           if ((end_transfer_time_file - start_transfer_time_file) > transfer_timeout)
                           {
                              trans_log(INFO_SIGN, __FILE__, __LINE__, NULL, NULL,
#if SIZEOF_TIME_T == 4
                                        "Transfer timeout reached for `%s' after %ld seconds.",
#else
                                        "Transfer timeout reached for `%s' after %lld seconds.",
#endif
                                        fsa->job_status[(int)db.job_no].file_name_in_use,
                                        (pri_time_t)(end_transfer_time_file - start_transfer_time_file));
                              wmo_quit();
                              exitflag = 0;
                              exit(STILL_FILES_TO_SEND);
                           }
                        }
                     }
                  }
                  if (length_type_indicator > 0)
                  {
                     length_type_indicator = 0;
                     header_length = 0;
                  }
               } /* for (j = 0; j < loops; j++) */

               if (rest > 0)
               {
                  if ((status = read(fd,
                                     (buffer + length_type_indicator + header_length),
                                     (rest - length_type_indicator - header_length))) != (rest - length_type_indicator - header_length))
                  {
                     trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                               "Could not read() local file `%s' : %s",
                               fullname, strerror(errno));
                     wmo_quit();
                     exit(READ_LOCAL_ERROR);
                  }
                  if (end_length == 4)
                  {
                     buffer[rest] = '\015';
                     buffer[rest + 1] = '\015';
                     buffer[rest + 2] = '\012';
                     buffer[rest + 3] = 3;  /* ETX */
                  }
                  if ((status = wmo_write(buffer, rest + end_length)) != SUCCESS)
                  {
                     trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                               "Failed to write rest of file to remote port %d [%d].",
                               p_file_name_buffer, db.port, status);
                     wmo_quit();
                     exit(eval_timeout(WRITE_REMOTE_ERROR));
                  }
                  if (fsa->trl_per_process > 0)
                  {
                     limit_transfer_rate(rest + end_length,
                                         fsa->trl_per_process, clktck);
                  }

                  no_of_bytes += rest + end_length;

                  if (gsf_check_fsa(p_db) != NEITHER)
                  {
                     fsa->job_status[(int)db.job_no].file_size_in_use_done = no_of_bytes;
                     fsa->job_status[(int)db.job_no].file_size_done += rest;
                     fsa->job_status[(int)db.job_no].bytes_send += rest;
                  }
               }

               /*
                * Since there are always some users sending files to the
                * AFD not in dot notation, lets check here if this is really
                * the EOF.
                * If not lets continue so long until we hopefully have reached
                * the EOF.
                * NOTE: This is NOT a fool proof way. There must be a better
                *       way!
                */
               if (fstat(fd, &stat_buf) == -1)
               {
                  (void)rec(transfer_log_fd, DEBUG_SIGN,
                            "Hmmm. Failed to stat() `%s' : %s (%s %d)\n",
                            fullname, strerror(errno), __FILE__, __LINE__);
                  break;
               }
               else
               {
                  if (stat_buf.st_size > *p_file_size_buffer)
                  {
                     char sign[LOG_SIGN_LENGTH];

                     if (db.special_flag & SILENT_NOT_LOCKED_FILE)
                     {
                        (void)memcpy(sign, DEBUG_SIGN, LOG_SIGN_LENGTH);
                     }
                     else
                     {
                        (void)memcpy(sign, WARN_SIGN, LOG_SIGN_LENGTH);
                     }

                     loops = (stat_buf.st_size - *p_file_size_buffer) / blocksize;
                     rest = (stat_buf.st_size - *p_file_size_buffer) % blocksize;
                     *p_file_size_buffer = stat_buf.st_size;

                     /*
                      * Give a warning in the receive log, so some action
                      * can be taken against the originator.
                      */
                     receive_log(sign, __FILE__, __LINE__, 0L, db.id.job,
                                 "File `%s' for host %s was DEFINITELY send without any locking. #%x",
                                 p_file_name_buffer, fsa->host_dsp_name, db.id.job);
                  }
                  else
                  {
                     break;
                  }
               }
            } /* for (;;) */

            if (db.special_flag & WMO_CHECK_ACKNOWLEDGE)
            {
               int ret;

               if ((ret = wmo_check_reply()) == INCORRECT)
               {
                  trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                            "Failed to receive reply from port %d for file %s.",
                            db.port, p_file_name_buffer);
                  wmo_quit();
                  exit(eval_timeout(CHECK_REPLY_ERROR));
               }
               else if (ret == NEGATIV_ACKNOWLEDGE)
                    {
                       trans_log(ERROR_SIGN, __FILE__, __LINE__, NULL, NULL,
                                 "Received negative acknowledge from remote port %d for file %s.",
                                 db.port, p_file_name_buffer);
                    }
            }

#ifdef _OUTPUT_LOG
            if (db.output_log == YES)
            {
               end_time = times(&tmsdummy);
            }
#endif

            /* Close local file. */
            if (close(fd) == -1)
            {
               (void)rec(transfer_log_fd, WARN_SIGN,
                         "%-*s[%d]: Failed to close() local file %s : %s (%s %d)\n",
                         MAX_HOSTNAME_LENGTH, tr_hostname, (int)db.job_no,
                         p_file_name_buffer, strerror(errno),
                         __FILE__, __LINE__);
               /*
                * Since we usually do not send more then 100 files and
                * sf_wmo() will exit(), there is no point in stopping
                * the transmission.
                */
            }
         }
         else
         {
            trans_log(INFO_SIGN, __FILE__, __LINE__, NULL, NULL,
                      "File `%s' is of zero length, ignoring.",
                      p_file_name_buffer);
         }

         /* Update FSA, one file transmitted. */
         if (gsf_check_fsa(p_db) != NEITHER)
         {
            fsa->job_status[(int)db.job_no].file_name_in_use[0] = '\0';
            fsa->job_status[(int)db.job_no].no_of_files_done++;
            fsa->job_status[(int)db.job_no].file_size_in_use = 0;
            fsa->job_status[(int)db.job_no].file_size_in_use_done = 0;
            local_file_size += *p_file_size_buffer;
            local_file_counter += 1;

            now = time(NULL);
            if (now >= (last_update_time + LOCK_INTERVAL_TIME))
            {
               last_update_time = now;
               update_tfc(local_file_counter, local_file_size,
                          p_file_size_buffer, files_to_send,
                          files_send, now);
               local_file_size = 0;
               local_file_counter = 0;
            }
         }

#ifdef _WITH_TRANS_EXEC
         if (db.special_flag & TRANS_EXEC)
         {
            trans_exec(file_path, fullname, p_file_name_buffer, clktck);
         }
#endif

#ifdef _OUTPUT_LOG
         if (db.output_log == YES)
         {
            if (ol_fd == -2)
            {
# ifdef WITHOUT_FIFO_RW_SUPPORT
               output_log_fd(&ol_fd, &ol_readfd, &db.output_log);
# else
               output_log_fd(&ol_fd, &db.output_log);
# endif
            }
            if ((ol_fd > -1) && (ol_data == NULL))
            {
               output_log_ptrs(&ol_retries,
                               &ol_job_number,
                               &ol_data,              /* Pointer to buffer.      */
                               &ol_file_name,
                               &ol_file_name_length,
                               &ol_archive_name_length,
                               &ol_file_size,
                               &ol_unl,
                               &ol_size,
                               &ol_transfer_time,
                               &ol_output_type,
                               db.host_alias,
                               (current_toggle - 1),
                               WMO,
                               &db.output_log);
            }
         }
#endif

         /* Now archive file if necessary. */
         if ((db.archive_time > 0) &&
             (p_db->archive_dir[0] != FAILED_TO_CREATE_ARCHIVE_DIR))
         {
#ifdef WITH_ARCHIVE_COPY_INFO
            int ret;
#endif

            /*
             * By telling the function archive_file() that this
             * is the first time to archive a file for this job
             * (in struct p_db) it does not always have to check
             * whether the directory has been created or not. And
             * we ensure that we do not create duplicate names
             * when adding db.archive_time to msg_name.
             */
#ifdef WITH_ARCHIVE_COPY_INFO
            if ((ret = archive_file(file_path, p_file_name_buffer, p_db)) < 0)
#else
            if (archive_file(file_path, p_file_name_buffer, p_db) < 0)
#endif
            {
               if (fsa->debug > NORMAL_MODE)
               {
                  trans_db_log(ERROR_SIGN, __FILE__, __LINE__, NULL,
                               "Failed to archive file `%s'",
                               p_file_name_buffer);
               }

               /*
                * NOTE: We _MUST_ delete the file we just send,
                *       else the file directory will run full!
                */
               if (unlink(fullname) == -1)
               {
                  system_log(ERROR_SIGN, __FILE__, __LINE__,
                             "Could not unlink() local file `%s' after sending it successfully : %s",
                             fullname, strerror(errno));
               }

#ifdef _OUTPUT_LOG
               if (db.output_log == YES)
               {
                  (void)memcpy(ol_file_name, db.p_unique_name, db.unl);
                  (void)strcpy(ol_file_name + db.unl, p_file_name_buffer);
                  *ol_file_name_length = (unsigned short)strlen(ol_file_name);
                  ol_file_name[*ol_file_name_length] = SEPARATOR_CHAR;
                  ol_file_name[*ol_file_name_length + 1] = '\0';
                  (*ol_file_name_length)++;
                  *ol_file_size = *p_file_size_buffer;
                  *ol_job_number = fsa->job_status[(int)db.job_no].job_id;
                  *ol_retries = db.retries;
                  *ol_unl = db.unl;
                  *ol_transfer_time = end_time - start_time;
                  *ol_archive_name_length = 0;
                  *ol_output_type = OT_NORMAL_DELIVERED + '0';
                  ol_real_size = *ol_file_name_length + ol_size;
                  if (write(ol_fd, ol_data, ol_real_size) != ol_real_size)
                  {
                     system_log(ERROR_SIGN, __FILE__, __LINE__,
                                "write() error : %s", strerror(errno));
                  }
               }
#endif
            }
            else
            {
               if (fsa->debug > NORMAL_MODE)
               {
                  trans_db_log(INFO_SIGN, __FILE__, __LINE__, NULL,
                               "Archived file `%s'", p_file_name_buffer);
               }
#ifdef WITH_ARCHIVE_COPY_INFO
               if (ret == DATA_COPIED) 
               {
                  archived_copied++;
               }
#endif

#ifdef _OUTPUT_LOG
               if (db.output_log == YES)
               {
                  (void)memcpy(ol_file_name, db.p_unique_name, db.unl);
                  (void)strcpy(ol_file_name + db.unl, p_file_name_buffer);
                  *ol_file_name_length = (unsigned short)strlen(ol_file_name);
                  ol_file_name[*ol_file_name_length] = SEPARATOR_CHAR;
                  ol_file_name[*ol_file_name_length + 1] = '\0';
                  (*ol_file_name_length)++;
                  (void)strcpy(&ol_file_name[*ol_file_name_length + 1],
                               &db.archive_dir[db.archive_offset]);
                  *ol_file_size = *p_file_size_buffer;
                  *ol_job_number = fsa->job_status[(int)db.job_no].job_id;
                  *ol_retries = db.retries;
                  *ol_unl = db.unl;
                  *ol_transfer_time = end_time - start_time;
                  *ol_archive_name_length = (unsigned short)strlen(&ol_file_name[*ol_file_name_length + 1]);
                  *ol_output_type = OT_NORMAL_DELIVERED + '0';
                  ol_real_size = *ol_file_name_length +
                                 *ol_archive_name_length + 1 + ol_size;
                  if (write(ol_fd, ol_data, ol_real_size) != ol_real_size)
                  {
                     system_log(ERROR_SIGN, __FILE__, __LINE__,
                                "write() error : %s", strerror(errno));
                  }
               }
#endif
            }
         }
         else
         {
#ifdef WITH_UNLINK_DELAY
            int unlink_loops = 0;

try_again_unlink:
#endif
            /* Delete the file we just have send. */
            if (unlink(fullname) == -1)
            {
#ifdef WITH_UNLINK_DELAY
               if ((errno == EBUSY) && (unlink_loops < 20))
               {
                  (void)my_usleep(100000L);
                  unlink_loops++;
                  goto try_again_unlink;
               }
#endif
               system_log(ERROR_SIGN, __FILE__, __LINE__,
                          "Could not unlink() local file %s after sending it successfully : %s",
                          fullname, strerror(errno));
            }

#ifdef _OUTPUT_LOG
            if (db.output_log == YES)
            {
               (void)memcpy(ol_file_name, db.p_unique_name, db.unl);
               (void)strcpy(ol_file_name + db.unl, p_file_name_buffer);
               *ol_file_name_length = (unsigned short)strlen(ol_file_name);
               ol_file_name[*ol_file_name_length] = SEPARATOR_CHAR;
               ol_file_name[*ol_file_name_length + 1] = '\0';
               (*ol_file_name_length)++;
               *ol_file_size = *p_file_size_buffer;
               *ol_job_number = fsa->job_status[(int)db.job_no].job_id;
               *ol_retries = db.retries;
               *ol_unl = db.unl;
               *ol_transfer_time = end_time - start_time;
               *ol_archive_name_length = 0;
               *ol_output_type = OT_NORMAL_DELIVERED + '0';
               ol_real_size = *ol_file_name_length + ol_size;
               if (write(ol_fd, ol_data, ol_real_size) != ol_real_size)
               {
                  system_log(ERROR_SIGN, __FILE__, __LINE__,
                             "write() error : %s", strerror(errno));
               }
            }
#endif
         }

         /*
          * After each successful transfer set error
          * counter to zero, so that other jobs can be
          * started.
          */
         if (gsf_check_fsa(p_db) != NEITHER)
         {
            if ((*p_file_size_buffer > 0) && (fsa->error_counter > 0))
            {
               int  fd,
#ifdef WITHOUT_FIFO_RW_SUPPORT
                    readfd,
#endif
                    j;
               char fd_wake_up_fifo[MAX_PATH_LENGTH];

#ifdef LOCK_DEBUG
               lock_region_w(fsa_fd, db.lock_offset + LOCK_EC, __FILE__, __LINE__);
#else
               lock_region_w(fsa_fd, db.lock_offset + LOCK_EC);
#endif
               fsa->error_counter = 0;

               /*
                * Wake up FD!
                */
               (void)snprintf(fd_wake_up_fifo, MAX_PATH_LENGTH, "%s%s%s",
                              p_work_dir, FIFO_DIR, FD_WAKE_UP_FIFO);
#ifdef WITHOUT_FIFO_RW_SUPPORT
               if (open_fifo_rw(fd_wake_up_fifo, &readfd, &fd) == -1)
#else
               if ((fd = open(fd_wake_up_fifo, O_RDWR)) == -1)
#endif
               {
                  system_log(WARN_SIGN, __FILE__, __LINE__,
                             "Failed to open() FIFO %s : %s",
                             fd_wake_up_fifo, strerror(errno));
               }
               else
               {
                  if (write(fd, "", 1) != 1)
                  {
                     system_log(WARN_SIGN, __FILE__, __LINE__,
                                "Failed to write() to FIFO %s : %s",
                                fd_wake_up_fifo, strerror(errno));
                  }
#ifdef WITHOUT_FIFO_RW_SUPPORT
                  if (close(readfd) == -1)
                  {
                     system_log(DEBUG_SIGN, __FILE__, __LINE__,
                                "Failed to close() FIFO %s (read) : %s",
                                fd_wake_up_fifo, strerror(errno));
                  }
#endif
                  if (close(fd) == -1)
                  {
                     system_log(DEBUG_SIGN, __FILE__, __LINE__,
                                "Failed to close() FIFO %s : %s",
                                fd_wake_up_fifo, strerror(errno));
                  }
               }

               /*
                * Remove the error condition (NOT_WORKING) from all jobs
                * of this host.
                */
               for (j = 0; j < fsa->allowed_transfers; j++)
               {
                  if ((j != db.job_no) &&
                      (fsa->job_status[j].connect_status == NOT_WORKING))
                  {
                     fsa->job_status[j].connect_status = DISCONNECT;
                  }
               }
               fsa->error_history[0] = 0;
               fsa->error_history[1] = 0;
#ifdef LOCK_DEBUG
               unlock_region(fsa_fd, db.lock_offset + LOCK_EC, __FILE__, __LINE__);
#else
               unlock_region(fsa_fd, db.lock_offset + LOCK_EC);
#endif

#ifdef LOCK_DEBUG
               lock_region_w(fsa_fd, db.lock_offset + LOCK_HS, __FILE__, __LINE__);
#else
               lock_region_w(fsa_fd, db.lock_offset + LOCK_HS);
#endif
               now = time(NULL);
               if (now > fsa->end_event_handle)
               {
                  fsa->host_status &= ~(EVENT_STATUS_FLAGS | AUTO_PAUSE_QUEUE_STAT);
                  if (fsa->end_event_handle > 0L)
                  {
                     fsa->end_event_handle = 0L;
                  }
                  if (fsa->start_event_handle > 0L)
                  {
                     fsa->start_event_handle = 0L;
                  }
               }
               else
               {
                  fsa->host_status &= ~(EVENT_STATUS_STATIC_FLAGS | AUTO_PAUSE_QUEUE_STAT);
               }
#ifdef LOCK_DEBUG
               unlock_region(fsa_fd, db.lock_offset + LOCK_HS, __FILE__, __LINE__);
#else
               unlock_region(fsa_fd, db.lock_offset + LOCK_HS);
#endif

               /*
                * Since we have successfully transmitted a file, no need to
                * have the queue stopped anymore.
                */
               if (fsa->host_status & AUTO_PAUSE_QUEUE_STAT)
               {
                  char sign[LOG_SIGN_LENGTH];

                  error_action(fsa->host_alias, "stop", HOST_ERROR_ACTION);
                  event_log(0L, EC_HOST, ET_EXT, EA_ERROR_END, "%s",
                            fsa->host_alias);
                  if ((fsa->host_status & HOST_ERROR_OFFLINE_STATIC) ||
                      (fsa->host_status & HOST_ERROR_OFFLINE) ||
                      (fsa->host_status & HOST_ERROR_OFFLINE_T))
                  {
                     (void)memcpy(sign, OFFLINE_SIGN, LOG_SIGN_LENGTH);
                  }
                  else
                  {
                     (void)memcpy(sign, INFO_SIGN, LOG_SIGN_LENGTH);
                  }
                  trans_log(sign, __FILE__, __LINE__, NULL, NULL,
                            "Starting input queue that was stopped by init_afd.");
                  event_log(0L, EC_HOST, ET_AUTO, EA_START_QUEUE, "%s",
                            fsa->host_alias);
               }
            } /* if (fsa->error_counter > 0) */
#ifdef WITH_ERROR_QUEUE
            if (fsa->host_status & ERROR_QUEUE_SET)
            {
               remove_from_error_queue(db.id.job, fsa, db.fsa_pos, fsa_fd);
            }
#endif
            if (fsa->host_status & HOST_ACTION_SUCCESS)
            {
               error_action(fsa->host_alias, "start", HOST_SUCCESS_ACTION);
            }
         }

         p_file_name_buffer += MAX_FILENAME_LENGTH;
         p_file_size_buffer++;
      } /* for (files_send = 0; files_send < files_to_send; files_send++) */

#ifdef WITH_ARCHIVE_COPY_INFO
      if (archived_copied > 0)
      {
         trans_log(DEBUG_SIGN, __FILE__, __LINE__, NULL, NULL,
                   "Copied %u files to archive.", archived_copied);
         archived_copied = 0;
      }
#endif

      if (local_file_counter)
      {
         if (gsf_check_fsa(p_db) != NEITHER)
         {
            update_tfc(local_file_counter, local_file_size,
                       p_file_size_buffer, files_to_send, files_send,
                       time(NULL));
            local_file_size = 0;
            local_file_counter = 0;
         }
      }

      /*
       * Remove file directory, but only when all files have
       * been transmitted.
       */
      if ((files_to_send == files_send) || (files_to_send < 1))
      {
         if (rmdir(file_path) < 0)
         {
            system_log(ERROR_SIGN, __FILE__, __LINE__,
                       "Failed to remove directory %s : %s",
                       file_path, strerror(errno));
         }
      }
      else
      {
         system_log(WARN_SIGN, __FILE__, __LINE__,
                    "There are still %d files for %s. Will NOT remove this job!",
                    files_to_send - files_send, file_path);
         exit_status = STILL_FILES_TO_SEND;
      }

#ifdef _WITH_BURST_2
      burst_2_counter++;
      diff_time = time(NULL) - connected;
      if (((fsa->protocol_options & KEEP_CONNECTED_DISCONNECT) &&
           (db.keep_connected > 0) && (diff_time > db.keep_connected)) ||
          ((db.disconnect > 0) && (diff_time > db.disconnect)))
      {
         cb2_ret = NO;
         break;
      }
   } while ((cb2_ret = check_burst_sf(file_path, &files_to_send, 0,
# ifdef _WITH_INTERRUPT_JOB
                                      0,
# endif
# ifdef _OUTPUT_LOG
                                      &ol_fd,
# endif
# ifndef AFDBENCH_CONFIG
                                      NULL,
# endif
                                      NULL)) == YES);
   burst_2_counter--;

   if (cb2_ret == NEITHER)
   {
      exit_status = STILL_FILES_TO_SEND;
   }
#endif /* _WITH_BURST_2 */

   free(buffer);

   /* Disconnect from remote port. */
   wmo_quit();
   if ((fsa != NULL) && (fsa->debug > NORMAL_MODE))
   {
      trans_db_log(INFO_SIGN, __FILE__, __LINE__, NULL,
                   "Disconnected from port %d.", db.port);
   }

   if (wmo_counter_fd > 0)
   {
      close_counter_file(wmo_counter_fd, &wmo_counter);
   }

   exitflag = 0;
   exit(exit_status);
}