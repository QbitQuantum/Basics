  //reimplemented in order to handle index MzML
  bool MzMLFile::isValid(const String& filename, std::ostream& os)
  {
    //determine if this is indexed mzML or not
    bool indexed = false;
    TextFile file(filename, true, 4);
    String s;
    s.concatenate(file.begin(), file.end());
    if (s.hasSubstring("<indexedmzML"))
    {
      indexed = true;
    }
    // find the corresponding schema
    String current_location;
    if (indexed)
    {
      current_location = File::find(indexed_schema_location_);
    }
    else
    {
      current_location = File::find(schema_location_);
    }

    return XMLValidator().isValid(filename, current_location, os);
  }