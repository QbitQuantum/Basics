/* zipfile.replaceFile(nameInArchive, name, offset, len) */
Handle<Value> ZipFile::Replace_File(const Arguments& args)
{
    ZipFile* zf = ObjectWrap::Unwrap<ZipFile>(args.This());

    struct zip_source *source;

    if (zf->Busy())
      return ThrowException(Exception::Error(String::New("Zipfile already in use..")));

    if (!args[0]->IsString())
      return ThrowException(Exception::TypeError(
                 String::New("Argument must be a file name.")));
    std::string archive_file = TOSTR(args[0]);

    std::string name;
    if (args[1]->IsUndefined())
      name = archive_file;
    else
      if (!args[1]->IsString())
        return ThrowException(Exception::TypeError(
                   String::New("Argument must be a file name.")));
      name = TOSTR(args[1]);

    zip_int64_t off;
    if (args[2]->IsUndefined())
      off = 0;
    else
      off = args[2]->Int32Value();
    
    zip_int64_t len; 
    if (args[3]->IsUndefined()) 
      len = -1; 
    else 
      len = args[3]->Int32Value();

    int idx = -1;
    
    std::vector<std::string>::iterator it = std::find(zf->names.begin(), zf->names.end(), archive_file);
    if (it!=zf->names.end()) {
        idx = distance(zf->names.begin(), it);
    }

    if (idx == -1) {
        std::stringstream s;
        s << "No file found by the name of: '" << archive_file << "\n";
        return ThrowException(Exception::Error(String::New(s.str().c_str())));
    }

    source = zip_source_file(zf->archive, name.c_str(), off, len);
    if (source == NULL) {
      std::stringstream s;
      s << "Error while replacing file " << name << " in zip archive: " << zip_strerror(zf->archive) << "\n";
      return ThrowException(Exception::Error(String::New(s.str().c_str())));
    }

    int ret = zip_replace(zf->archive, idx, source);        
    if (ret < 0) {
      zip_source_free(source);
      std::stringstream s;
      s << "Error while replacing file " << name << " in zip archive: " << zip_strerror(zf->archive) << "\n";
      return ThrowException(Exception::Error(String::New(s.str().c_str())));
    }

    return Undefined();
}