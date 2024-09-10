static void sig_alrm(int signo){
    longjmp(env_alrm,1);
}