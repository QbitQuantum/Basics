int file_rename(std::string oldname, std::string newname) {
    DWORD result = MoveFileA(oldname.c_str(), newname.c_str());

    switch(result) {
        case 0:
            return 0;
            break;
        default:
            return 1;
            break;
    }
}