int
do_aspawn(SV* really, SV **mark, SV **sp)
{
 char   **a,
        *tmps;
 struct inheritance inherit;
 pid_t  pid;
 int    status,
        fd,
        nFd,
        fdMap[3];
 SV     *sv,
        **p_sv;
 STRLEN	n_a;

    status = FAIL;
    if (sp > mark)
    {
       Newx(PL_Argv, sp - mark + 1, char*);
       a = PL_Argv;
       while (++mark <= sp)
       {
           if (*mark)
              *a++ = SvPVx(*mark, n_a);
           else
              *a++ = "";
       }
       inherit.flags        = SPAWN_SETGROUP;
       inherit.pgroup       = SPAWN_NEWPGROUP;
       fdMap[STDIN_FILENO]  = Perl_stdin_fd;
       fdMap[STDOUT_FILENO] = Perl_stdout_fd;
       fdMap[STDERR_FILENO] = STDERR_FILENO;
       nFd                  = 3;
       *a = NULL;
       /*-----------------------------------------------------*/
       /* Will execvp() use PATH?                             */
       /*-----------------------------------------------------*/
       if (*PL_Argv[0] != '/')
           TAINT_ENV();
       if (really && *(tmps = SvPV(really, n_a)))
           pid = spawnp(tmps, nFd, fdMap, &inherit,
                        (const char **) PL_Argv,
                        (const char **) environ);
       else
           pid = spawnp(PL_Argv[0], nFd, fdMap, &inherit,
                        (const char **) PL_Argv,
                        (const char **) environ);
       if (pid < 0)
       {
          status = FAIL;
          if (ckWARN(WARN_EXEC))
             warner(WARN_EXEC,"Can't exec \"%s\": %s",
                    PL_Argv[0],
                    Strerror(errno));
       }
       else
       {
          /*------------------------------------------------*/
          /* If the file descriptors have been remapped then*/
          /* we've been called following a my_popen request */
          /* therefore we don't want to wait for spawnned   */
          /* program to complete. We need to set the fdpid  */
          /* value to the value of the spawnned process' pid*/
          /*------------------------------------------------*/
          fd = 0;
          if (Perl_stdin_fd != STDIN_FILENO)
             fd = Perl_stdin_fd;
          else
             if (Perl_stdout_fd != STDOUT_FILENO)
                fd = Perl_stdout_fd;
          if (fd != 0)
          {
             /*---------------------------------------------*/
             /* Get the fd of the other end of the pipe,    */
             /* use this to reference the fdpid which will  */
             /* be used by my_pclose                        */
             /*---------------------------------------------*/
             close(fd);
             MUTEX_LOCK(&PL_fdpid_mutex);
             p_sv  = av_fetch(PL_fdpid,fd,TRUE);
             fd    = (int) SvIVX(*p_sv);
             SvREFCNT_dec(*p_sv);
             *p_sv = &PL_sv_undef;
             sv    = *av_fetch(PL_fdpid,fd,TRUE);
             MUTEX_UNLOCK(&PL_fdpid_mutex);
             (void) SvUPGRADE(sv, SVt_IV);
             SvIVX(sv) = pid;
             status    = 0;
          }
          else
             wait4pid(pid, &status, 0);
       }
       do_execfree();
    }