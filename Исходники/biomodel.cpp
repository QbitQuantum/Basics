/****************************************************************************************
TASK:   Add a file to the hidden directory
PRE :   source - source of the file to add
POST:   File has been added to hidden directory
****************************************************************************************/
void BioModel::addFile(QString source)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];

    _splitpath_s(source.toStdString().c_str(), drive, dir, fname, ext);

    std::string outputDirectory = getCurrDirectory() + "\\bioguised-testfolder";

    if(CreateDirectoryA(outputDirectory.c_str(), NULL) ||
            ERROR_ALREADY_EXISTS == GetLastError()){
        std::stringstream stringStream;
        stringStream << outputDirectory << "\\" << fname << ext;
        std::string newFileLocation = stringStream.str();
        LPCSTR destination = newFileLocation.c_str();
        BOOL successful = MoveFileA(source.toStdString().c_str(), destination);
        if(!successful){
            GetLastError();
        } else {
            printf("Success!!!!!!!!");
        }
    } else {
        printf("Destination File does not exist");
    }

}