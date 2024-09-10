bool CommandRm::exe(tfs::api::FileSystem& fs, string parameter)
{
    FilePath pathGenerator;
    istringstream input(parameter);
    string path;
    string commandType;
    input >> commandType >>path;
    /**
     * if there is only one parameter,it should be the filepath 
     * which will be removed later, or romove the directory
     */
    if(path == ""){
        path = commandType;
        path = pathGenerator.getPath(m_currentDir, path);
        path = pathGenerator.change(path);
        return removeFile(fs, path);
    }
    else if(commandType == "-rf"){
        path = pathGenerator.getPath(m_currentDir, path);
        path = pathGenerator.change(path);
        return removeDirectory(fs, path);
    }
    cout << "<USAGE> rm <filepath>" << endl;
    cout << "<USAGE> rm -rf <filepath>" << endl;
    return false;
}