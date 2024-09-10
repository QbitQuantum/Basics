static int 
ux_startp (const char *shell, const char *command, const char *parm) 
{
    if (parm) {
         spawnlp (P_WAIT, 
              (char *) shell, 
              (char *) shell, 
              "/c", 
              (char *) command, 
              (char *) parm,
              (char *) 0);
    } else {
         spawnlp (P_WAIT, 
              (char *) shell, 
              (char *) shell, 
              "/c", 
              (char *) command, 
              (char *) 0);
    }
    return 0;
}