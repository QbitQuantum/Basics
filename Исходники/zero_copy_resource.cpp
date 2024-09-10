 RemoteCopyingFile::RemoteCopyingFile(std::string filename)
   : _filename(filename),
     _is_closed(false),
     _errno(0),
     _fileno(-1),
     _previous_seek_failed(false),
     _close_on_delete(true),
     _position(0) {
     if (filename.substr(0,7) == "rfio://") {
         fscalls.reset(new rfio_filesystem_calls());
     } else if (filename.substr(0,7) == "dcap://") {
         fscalls.reset(new dcap_filesystem_calls());
     } else if (filename.substr(0,7) == "hdfs://") {
         fscalls.reset(new hdfs_filesystem_calls());
         filename = filename.substr(8);
     } else {
         TERMINATE("Unknown remote file type: ", filename);
     }
     if (!fscalls->loaded) TERMINATE("Failure to load remote access library!");
     _fileno = fscalls->open(const_cast<char*>(filename.c_str()), O_RDONLY, 0);
     _errno = fscalls->last_errno();
     if (_errno != 0 or _fileno == -1) TERMINATE("Could not open '", filename, "': ", strerror(_errno));
 }