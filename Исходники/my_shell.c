int my_execvpe(char* full, char* args[])
{
    struct stat access;
    if (stat(full, &access) == 0)
        if(execvpe(full, args, NULL) == -1)
            shell_error("execvpe");
    return 0;
}