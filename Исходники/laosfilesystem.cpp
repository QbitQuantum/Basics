int check_sd()
{
    extern LaosStatus *state;
    extern LaosFileSystem sd;
    char val[]="wb";
    char name[]="test.txt";
    FILE *fp = sd.openfile(name, val);
    if ( fp == NULL )
    {
        state->setState(ERROR);
        state->setErrorMessage("SD not ready\n\r");
        return false;
    }
    else
    {
        fclose(fp);
        removefile(name);
        return true;
    }
}