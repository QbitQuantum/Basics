static FILE* fopenZIPped(const char* filename, const char* mode)
{
    // check mode
    if (mode[0] == 'r')
    {
        // create the pipe
        int hPipe[2];
        if (_pipe(hPipe, 2048, ((mode[1] =='b') ? _O_BINARY : _O_TEXT) | _O_NOINHERIT) == -1)
        {
            fprintf(stderr, "could not create pipe\n");
            return NULL;
        }

        // duplicate stdin/stdout handle so we can restore them later
        int hStdOut = _dup(_fileno(stdout));

        // make the write end of pipe go to stdout
        if (_dup2(hPipe[WRITE_HANDLE], _fileno(stdout)) != 0)
        {
            fprintf(stderr, "could not set pipe output\n");
            return NULL;
        }

        // redirect read end of pipe to input file
        if (_dup2(hPipe[READ_HANDLE], _fileno(stdin)) != 0)
        {
            fprintf(stderr, "could not redirect input file\n");
            return NULL;
        }

        // close original write end of pipe
        close(hPipe[WRITE_HANDLE]);

        // Spawn process
        HANDLE hProcess = (HANDLE) spawnlp(P_NOWAIT, "unzip", "unzip", "-p", filename, NULL);

        // redirect stdout back into stdout
        if (_dup2(hStdOut, _fileno(stdout)) != 0)
        {
            fprintf(stderr, "could not reconstruct stdout\n");
            return NULL;
        }

        // return redirected stdin
        return stdin;
    }
    else
    {
        return NULL;
    }
}