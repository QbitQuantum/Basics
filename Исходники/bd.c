int main(int argc, char **argv)
{
    int status = 0;

    ofp = stdout;  /* Where the output will go */
    Initialize(argc, argv);
    Compare();
    if (globals.files_are_different) {
        PrintResults();
    }
    Terminate();
    return status;
}