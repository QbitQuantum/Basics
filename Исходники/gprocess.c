/**
 * g_process_perform_supervise:
 *
 * Supervise process, returns only in the context of the daemon process, the
 * supervisor process exits here.
 **/
static void
g_process_perform_supervise(void)
{
  pid_t pid;
  gboolean first = TRUE, exited = FALSE;
  gchar proc_title[PROC_TITLE_SPACE];
  struct sigaction sa;

  g_snprintf(proc_title, PROC_TITLE_SPACE, "supervising %s", process_opts.name);
  g_process_setproctitle(proc_title);
  
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = SIG_IGN;
  sigaction(SIGHUP, &sa, NULL);

  while (1)
    {
      if (pipe(init_result_pipe) != 0)
        {
          g_process_message("Error daemonizing process, cannot open pipe; error='%s'", g_strerror(errno));
          g_process_startup_failed(1, TRUE);
        }
        
      /* fork off a child process */
      if ((pid = fork()) < 0)
        {
          g_process_message("Error forking child process; error='%s'", g_strerror(errno));
          g_process_startup_failed(1, TRUE);
        }
      else if (pid != 0)
        {
          gint rc;
          gboolean deadlock = FALSE;
          
          /* this is the supervisor process */

          /* shut down init_result_pipe write side */
          close(init_result_pipe[1]);
          init_result_pipe[1] = -1;
          
          rc = g_process_recv_result();
          if (first)
            {
              /* first time encounter, we have a chance to report back, do it */
              g_process_send_result(rc);
              if (rc != 0)
                break;
              g_process_detach_stdio();
            }
          first = FALSE;
          if (rc != 0)
            {
              gint i = 0;
              /* initialization failed in daemon, it will probably exit soon, wait and restart */
              
              while (i < 6 && waitpid(pid, &rc, WNOHANG) == 0)
                {
                  if (i > 3)
                    kill(pid, i > 4 ? SIGKILL : SIGTERM);
                  sleep(1);
                  i++;
                }
              if (i == 6)
                g_process_message("Initialization failed but the daemon did not exit, even when forced to, trying to recover; pid='%d'", pid);
              continue;
            }
          
          if (process_opts.check_fn && (process_opts.check_period >= 0))
            {
              gint i = 1;
              while (!(exited = waitpid(pid, &rc, WNOHANG)))
                {
                  if (i >= process_opts.check_period)
                    {
                      if (!process_opts.check_fn())
                        break;
                      i = 0;
                    }
                  sleep(1);
                  i++;
                }

              if (!exited)
                {
                  gint j = 0;
                  g_process_message("Daemon deadlock detected, killing process;");
                  deadlock = TRUE;
              
                  while (j < 6 && waitpid(pid, &rc, WNOHANG) == 0)
                    {
                      if (j > 3)
                        kill(pid, j > 4 ? SIGKILL : SIGABRT);
                      sleep(1);
                      j++;
                    }
                  if (j == 6)
                    g_process_message("The daemon did not exit after deadlock, even when forced to, trying to recover; pid='%d'", pid);
                }
            }
          else
            {
              waitpid(pid, &rc, 0);
            }

          if (deadlock || WIFSIGNALED(rc) || (WIFEXITED(rc) && WEXITSTATUS(rc) != 0))
            {
              gchar argbuf[64];

              if (!access(G_PROCESS_FAILURE_NOTIFICATION, R_OK | X_OK)) 
                {
                  const gchar *notify_reason;
                  pid_t npid = fork();
                  gint nrc;
                  switch (npid)
                    {
                    case -1:
                      g_process_message("Could not fork for external notification; reason='%s'", strerror(errno));
                      break;
    
                    case 0:
                      switch(fork())
                        {
                        case -1:
                          g_process_message("Could not fork for external notification; reason='%s'", strerror(errno));
                          exit(1);
                          break;
                        case 0: 
			  if (deadlock)
			    {
			      notify_reason = "deadlock detected";
			      argbuf[0] = 0;
			    }
			  else 
			    {
			      snprintf(argbuf, sizeof(argbuf), "%d", WIFSIGNALED(rc) ? WTERMSIG(rc) : WEXITSTATUS(rc));
			      if (WIFSIGNALED(rc))
				notify_reason = "signalled";
			      else
				notify_reason = "non-zero exit code";
			    }
			  execlp(G_PROCESS_FAILURE_NOTIFICATION, G_PROCESS_FAILURE_NOTIFICATION, 
				 SAFE_STRING(process_opts.name),
				 SAFE_STRING(process_opts.chroot_dir),
				 SAFE_STRING(process_opts.pidfile_dir),
				 SAFE_STRING(process_opts.pidfile),
				 SAFE_STRING(process_opts.cwd),
				 SAFE_STRING(process_opts.caps),
				 notify_reason,
				 argbuf,
				 (deadlock || !WIFSIGNALED(rc) || WTERMSIG(rc) != SIGKILL) ? "restarting" : "not-restarting",
				 (gchar*) NULL);
			  g_process_message("Could not execute external notification; reason='%s'", strerror(errno));
			  break;
			  
			default:
			  exit(0);
			  break;
			} /* child process */
                    default:
                      waitpid(npid, &nrc, 0);
                      break;
                    }
                }
              if (deadlock || !WIFSIGNALED(rc) || WTERMSIG(rc) != SIGKILL)
                {
                  g_process_message("Daemon exited due to a deadlock/signal/failure, restarting; exitcode='%d'", rc);
                  sleep(1);
                }
              else
                {
                  g_process_message("Daemon was killed, not restarting; exitcode='%d'", rc);
                  break;
                }
            }
          else
            {
              g_process_message("Daemon exited gracefully, not restarting; exitcode='%d'", rc);
              break;
            }
        }
      else
        {
          /* this is the daemon process, thus we should return to the caller of g_process_start() */
          /* shut down init_result_pipe read side */
          process_kind = G_PK_DAEMON;
          close(init_result_pipe[0]);
          init_result_pipe[0] = -1;

          /* update systemd socket activation pid */
          inherit_systemd_activation();

          memcpy(process_opts.argv_start, process_opts.argv_orig, process_opts.argv_env_len);
          return;
        }
    }
  exit(0);
}