int launch_mutator()
{
   unsigned i = 0, j = 0;
   const char *reason = NULL;
   char buf[STRING_MAX] = {0};
   BPatch_Vector< BPatch_module * > *appModules = NULL;
   BPatch_Vector< BPatch_function * > *appFunctions = NULL;
   BPatch_flowGraph *appCFG = NULL;

   dynHandle *dh = mutatorInit();
   if (!dh) return(-1);

   /**************************************************************
    * Parsing Phase
    */
   // Is this if redundant?  Will anybody run this without parsing the modules?
   if (config.parse_level >= PARSE_MODULE) {
      sendMsg(config.outfd, ID_PARSE_MODULE, INFO);
      appModules = dh->image->getModules();
      if (!appModules) {
         sendMsg(config.outfd, ID_PARSE_MODULE, INFO, ID_FAIL,
                 "Failure in BPatch_image::getModules()");
         return(-1);
      } else
         sendMsg(config.outfd, ID_PARSE_MODULE, INFO, ID_PASS,
                 appModules->size());
   }
   if (config.parse_level >= PARSE_FUNC) {
      for (i = 0; i < appModules->size(); ++i) {
         (*appModules)[i]->getName(buf, sizeof(buf));

         // Check module inclusion/exclusion regular expression rules.
         reason = config.mod_rules.getReason(buf);
         if (reason) sendMsg(config.outfd, ID_DATA_STRING, INFO, ID_INFO, reason);
         if (!config.mod_rules.isValid(buf)) continue;

         sendMsg(config.outfd, ID_PARSE_FUNC, INFO, ID_TEST, buf);
         appFunctions = (*appModules)[i]->getProcedures();
         if (!appFunctions) {
            sendMsg(config.outfd, ID_PARSE_FUNC, INFO, ID_FAIL,
                    "Failure in BPatch_module::getProcedures()");
            return(-1);
         } else
            sendMsg(config.outfd, ID_PARSE_FUNC, INFO, ID_PASS,
                    appFunctions->size());

         if (config.parse_level >= PARSE_CFG) {
            sendMsg(config.outfd, ID_PARSE_MODULE_CFG, INFO, ID_TEST,
                    (*appModules)[i]->getName(buf, sizeof(buf)));

            int cfg_warn_cnt = 0, cfg_pass_cnt = 0;
            for (j = 0; j < appFunctions->size(); ++j) {
               (*appFunctions)[j]->getName(buf, sizeof(buf));

               // Check function inclusion/exclusion regular expression rules.
               reason = config.func_rules.getReason(buf);
               if (reason) sendMsg(config.outfd, ID_DATA_STRING, INFO, ID_INFO, reason);
               if (!config.func_rules.isValid(buf)) continue;

               sendMsg(config.outfd, ID_PARSE_FUNC_CFG, VERB1, ID_TEST, buf);
               appCFG = (*appFunctions)[j]->getCFG();
               if (!appCFG) {
                  sendMsg(config.outfd, ID_PARSE_FUNC_CFG, VERB1, ID_WARN,
                          "Failure in BPatch_function::getCFG()");
                  ++cfg_warn_cnt;
               } else {
                  sendMsg(config.outfd, ID_PARSE_FUNC_CFG, VERB1, ID_PASS);
                  ++cfg_pass_cnt;
               }
            }
            if (cfg_warn_cnt)
               sendMsg(config.outfd, ID_PARSE_MODULE_CFG, INFO, ID_WARN,
                       sprintf_static("%d warning(s), %d passed.", cfg_warn_cnt, cfg_pass_cnt));
            else
               sendMsg(config.outfd, ID_PARSE_MODULE_CFG, INFO, ID_PASS);
         }
      }
   }

   /**************************************************************
    * Instrumentation Phase
    */

   /* Load the library, if specified */
   if (config.instType == USER_FUNC) {
       char instLibrary[1024];
       int offset = strcspn(config.inst_function, ":");
       strncpy (instLibrary, config.inst_function, offset);
       instLibrary[offset] = '\0';
       if(! dh->addSpace->loadLibrary(instLibrary)) {
          sendMsg(config.outfd, ID_INST_FIND_POINTS, VERB3, ID_FAIL,
                  "Failure in loading library");
          return false;
       }
   }

   if (config.trace_inst) 
   {
      errno = 0;
      sendMsg(config.outfd, ID_TRACE_INIT, INFO);
      sendMsg(config.outfd, ID_TRACE_OPEN_READER, VERB1);
	
      if (config.use_process)
      {
         config.pipefd = open(config.pipe_filename, O_RDONLY | O_RSYNC | O_NONBLOCK);
         if (config.pipefd < 0) {
            sendMsg(config.outfd, ID_TRACE_OPEN_READER, VERB1, ID_FAIL,
                    sprintf_static("Mutator could not open trace pipe (%s) for read: %s\n",
                                   config.pipe_filename, strerror(errno)));
            config.pipefd = -1;

         } else {
            sendMsg(config.outfd, ID_TRACE_OPEN_READER, VERB1, ID_PASS);
	      
            // Run mutatee side of trace initialization.
            sendMsg(config.outfd, ID_TRACE_INIT_MUTATEE, VERB1);
	      
            if (!initTraceInMutatee(dh)) {
               sendMsg(config.outfd, ID_TRACE_INIT_MUTATEE, VERB1, ID_FAIL);
               config.pipefd = -1;
            } else
               sendMsg(config.outfd, ID_TRACE_INIT_MUTATEE, VERB1, ID_PASS);
         }

         if (config.pipefd == -1) {
            sendMsg(config.outfd, ID_TRACE_INIT, INFO, ID_FAIL,
                    "Disabling instrumentation tracing.");
         } else
            sendMsg(config.outfd, ID_TRACE_INIT, INFO, ID_PASS);

         // We should remove the named pipe now, pass or fail.
         unlink(config.pipe_filename);
      }
   }

   if (config.inst_level >= INST_FUNC_ENTRY) {
      
      if (config.transMode == TRANS_PROCESS)
         if (!dynStartTransaction(dh)) return(-1);

      for (i = 0; i < appModules->size(); ++i) {
         int mod_warn_cnt = 0, mod_pass_cnt = 0;
         (*appModules)[i]->getName(buf, sizeof(buf));
         // Check module inclusion/exclusion regular expression rules.
         reason = config.mod_rules.getReason(buf);
         if (reason) 
            sendMsg(config.outfd, ID_DATA_STRING, INFO, ID_INFO, reason);
         if (!config.mod_rules.isValid(buf)) {
            continue;
         }

         if (config.transMode == TRANS_MODULE)
            if (!dynStartTransaction(dh)) {
               continue;
            }

         sendMsg(config.outfd, ID_INST_MODULE, INFO, ID_TEST, buf);

         sendMsg(config.outfd, ID_INST_GET_FUNCS, VERB1);
         appFunctions = (*appModules)[i]->getProcedures();
         if (!appFunctions) {
            sendMsg(config.outfd, ID_INST_GET_FUNCS, VERB1, ID_FAIL,
                    "Failure in BPatch_module::getProcedures()");
            return(-1);
         } else
            sendMsg(config.outfd, ID_INST_GET_FUNCS, VERB1, ID_PASS,
                    appFunctions->size());

         for (j = 0; j < appFunctions->size(); ++j) {
            int func_warn_cnt = 0, func_pass_cnt = 0;
            (*appFunctions)[j]->getName(buf, sizeof(buf));

            // Check function inclusion/exclusion regular expression rules.
            reason = config.func_rules.getReason(buf);
            if (reason) sendMsg(config.outfd, ID_DATA_STRING, INFO, ID_INFO, reason);
            if (!config.func_rules.isValid(buf)) continue;

            if (config.transMode == TRANS_FUNCTION)
               if (!dynStartTransaction(dh)) continue;

            sendMsg(config.outfd, ID_INST_FUNC, VERB1, ID_TEST, buf);

            if (config.inst_level == INST_FUNC_ENTRY) {
               if (!instrumentFunctionEntry(dh, (*appFunctions)[j]))
                  ++func_warn_cnt;
               else
                  ++func_pass_cnt;
            }

            if (config.inst_level == INST_FUNC_EXIT) {
               if (!instrumentFunctionExit(dh, (*appFunctions)[j]))
                  ++func_warn_cnt;
               else
                  ++func_pass_cnt;
            }

            if (config.inst_level == INST_BASIC_BLOCK) {
               if (!instrumentBasicBlocks(dh, (*appFunctions)[j]))
                  ++func_warn_cnt;
               else
                  ++func_pass_cnt;
            }

            if (config.inst_level == INST_MEMORY_READ) {
               if (!instrumentMemoryReads(dh, (*appFunctions)[j]))
                  ++func_warn_cnt;
               else
                  ++func_pass_cnt;
            }

            if (config.inst_level == INST_MEMORY_WRITE) {
               if (!instrumentMemoryWrites(dh, (*appFunctions)[j]))
                  ++func_warn_cnt;
               else
                  ++func_pass_cnt;
            }

            if (config.transMode == TRANS_FUNCTION)
               if (!dynEndTransaction(dh)) {
                  func_warn_cnt = func_pass_cnt;
                  func_pass_cnt = 0;
               }

            if (func_warn_cnt) {
               sendMsg(config.outfd, ID_INST_FUNC, VERB1, ID_WARN,
                       sprintf_static("%d warning(s), %d passed.", func_warn_cnt, func_pass_cnt));
               ++mod_warn_cnt;
            } else {
               sendMsg(config.outfd, ID_INST_FUNC, VERB1, ID_PASS);
               ++mod_pass_cnt;
            }
         }

         if (config.transMode == TRANS_MODULE)
            if (!dynEndTransaction(dh)) {
               mod_warn_cnt = mod_pass_cnt;
               mod_pass_cnt = 0;
            }

         if (mod_warn_cnt)
            sendMsg(config.outfd, ID_INST_MODULE, INFO, ID_WARN,
                    sprintf_static("%d warning(s), %d passed.", mod_warn_cnt, mod_pass_cnt));
         else
            sendMsg(config.outfd, ID_INST_MODULE, INFO, ID_PASS);
      }

      if (config.transMode == TRANS_PROCESS)
         dynEndTransaction(dh);
   }

   if (config.hunt_crashes) {
      sendMsg(config.outfd, ID_CRASH_HUNT_NUM_ACTIONS, INFO, ID_INFO, numInstsAllowed);
   }

   if (!config.use_process)
   {
      BPatch_binaryEdit *writeBE = dynamic_cast<BPatch_binaryEdit *>(dh->addSpace);

      // Load symbol libraries (if necessary)
      if( writeBE != NULL ) {
          deque<string>::iterator symLib_iter;
          for(symLib_iter = config.symbol_libraries.begin();
              symLib_iter != config.symbol_libraries.end();
              ++symLib_iter)
          {
              if( !writeBE->loadLibrary((*symLib_iter).c_str()) ) {
                  sendMsg(config.outfd, ID_INST_FIND_POINTS, VERB3, ID_FAIL,
                          "Unable to load symbol library");
                  return false;
              }
          }
      }

      writeBE->writeFile(config.writeFilePath);
   }

   if (config.use_process)
   {
      sendMsg(config.outfd, ID_RUN_CHILD, INFO);
      if (!dh->proc->continueExecution()) {
         sendMsg(config.outfd, ID_RUN_CHILD, INFO, ID_FAIL,
                 "Failure in BPatch_thread::continueExecution()");
         return false;
      }
      sendMsg(config.outfd, ID_RUN_CHILD, INFO, ID_PASS);
      
    
      //
      // Child continued.  Start reading from trace pipe, if enabled.
      //
      if (config.trace_inst) {
         while (config.pipefd != -1) {
            sendMsg(config.outfd, ID_POLL_STATUS_CHANGE, DEBUG);
            bool change = dh->bpatch->pollForStatusChange();
            sendMsg(config.outfd, ID_POLL_STATUS_CHANGE, DEBUG, ID_PASS);

            // Recheck conditional if a change was detected.
            if (change) continue;

            readTracePipe();

            // Eeeew.  I know.  But how else do you wait on a file descriptor,
            // AND BPatch::pollforStatusChange() == true at the same time?

            // We should probably have BPatch::registerStatusChangeCallback()
            // or something similar.
            sleep(1);
         }
      }
      

      //
      // All processing complete.  Loop indefinitly until exit handler called.
      //
      sendMsg(config.outfd, ID_WAIT_TERMINATION, INFO);
      while (1) {
         sendMsg(config.outfd, ID_CHECK_TERMINATION, INFO);
         bool dead = dh->proc->isTerminated();
         sendMsg(config.outfd, ID_CHECK_TERMINATION, INFO, ID_PASS);
         if (dead) break;

         sendMsg(config.outfd, ID_WAIT_STATUS_CHANGE, DEBUG);
         if (!dh->bpatch->waitForStatusChange())
            sendMsg(config.outfd, ID_WAIT_STATUS_CHANGE, DEBUG, ID_FAIL);
         else
            sendMsg(config.outfd, ID_WAIT_STATUS_CHANGE, DEBUG, ID_PASS);
      }
      sendMsg(config.outfd, ID_WAIT_TERMINATION, INFO, ID_PASS);
   }
   return 0;
}