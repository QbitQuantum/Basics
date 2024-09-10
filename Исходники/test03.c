void createTestFiles(void)
{
    Dsetdrv(drive);             // switch to selected drive
    Dsetpath("\\");
    (void) Dcreate("TESTDIR");
    Dsetpath("\\TESTDIR");

    int i, f;
    char numString[8];
    char fileName[16];
    for(i=0; i<25; i++) {
        byteToHex(i + 1, numString);
        
        strcpy(fileName, "FILE_");
        strcat(fileName, numString);
        f = Fcreate(fileName, 0);
        Fwrite(f, 7, fileName);
        Fclose(f);
        
        strcpy(fileName, "FILENAME.X");
        strcat(fileName, numString);
        f = Fcreate(fileName, 0);
        Fwrite(f, 12, fileName);
        Fclose(f);
        
        strcpy(fileName, "DIR_");
        strcat(fileName, numString);
        (void) Dcreate(fileName);
    }
}