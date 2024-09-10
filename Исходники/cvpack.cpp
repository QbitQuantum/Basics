int main(int argc, char* argv[])
/******************************/
{
    char tmpFile[L_tmpnam];
    bool quiet;

    quiet = false;
    set_new_handler(outOfMemory);
    try {
        if( argc != 2 ) {
            if( argc == 3 && stricmp( argv[1], "/nologo" ) == 0 ) {
                quiet = true;
                argv[1] = argv[2];
            } else {
                cerr << CVpackUsage;
                return 1;
            }
        }
        if( !quiet ) {
            cout << CVpackHeader << endl;
        }
        ::ConvertFName(argv[1]);
        ifstream  fd(fName, ios::in | ios::binary);
        if ( !fd ) {
            throw FileError(fName);
        }
        tmpnam(tmpFile);
        CVpack packMaker(fd,tmpFile);
        //cerr << "calling packMaker.CreatePackExe()\n";
        //cerr.flush();

        packMaker.CreatePackExe();
        //cout << "cvpack, packMaker.CreatePackExe() OK\n";
        //cout.flush();

        fd.close();
        if ( remove(fName) ) {
            throw MiscError(strerror(errno));
        }
        if ( rename(tmpFile,fName) ) {
            throw MiscError(strerror(errno));
        }
    }
    catch (CVpackError& CVerr) {
        CVerr.ErrorPrint();
        remove(tmpFile);
        exit(1);
    }
    return 0;
}