HttpCache::HttpCache(const std::string& directory)
{
    struct stat s;
    d_directory = directory; 
    int err = stat(d_directory.c_str(), &s);
    if(-1 == err) 
    {
        if(ENOENT == errno) {
            mkdir(d_directory.c_str() , 0766);
        } else {
            Perror("stat", errno);
        }
    }
}