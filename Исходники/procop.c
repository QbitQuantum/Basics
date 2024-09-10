int exec_and_write(const char *proc, int *proc_stdout, pid_t *child,
                        char *const envp[])
{
        int fds[2];

        if (pipe(fds))
                dub_sysdie("Couldn't open pipe (exec_and_write)");
       
        signal(SIGCLD, SIG_IGN);
        
        if (!(*child = fork())){
                
                if (proc_stdout){
                        dup2(*proc_stdout, 1);
                        close(*proc_stdout);
                }
                
                close(fds[1]);
                
                dup2(fds[0], 0);
                close(fds[0]);
                
                if (envp){
                        if (execle(proc, proc, NULL, envp))
                                dub_sysdie("Exec failed");
                }else
                        if (execlp(proc, proc, NULL))
                                dub_sysdie("Exec failed");
                
        }else{
                if (proc_stdout)
                        close(*proc_stdout);
                
                close(fds[0]);
                return fds[1];
        }

        /* never happens */
        return 0;
}