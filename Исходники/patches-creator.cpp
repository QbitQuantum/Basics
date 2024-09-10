set<string> compareWithStorageFile(const string& path) {
  map<string, time_t> storage;
	
  XMLDocument doc;
  if (doc.LoadFile(gStorage.c_str())!=XML_NO_ERROR) {
    cerr << "Error reading XML!" << endl;
    doc.PrintError();
  }
  auto root  = doc.FirstChildElement();
  auto file = root->FirstChildElement();
  while (file) {
    string name = file->FirstAttribute()->Value();
    auto time = file->Attribute("last_modif");
    storage[name] = stoll(time);
    file = file->NextSiblingElement();
  }

  set<string> dst;
  fs::path current(path);
  fs::recursive_directory_iterator end;
  cout << "Go to directory iterator: " << current.string() << " -> " << endl;
  for (fs::recursive_directory_iterator item(current); item != end; ++item) {
    if (!fs::is_directory(item->status())) {
      fs::path filename = item->path();

      time_t time = fs::last_write_time(filename);
      auto sfile = filename.string().substr(current.string().size());
      if (storage.count(sfile)>0) {
	if (storage[sfile]!=time) {
          dst.insert(sfile);
	  cout << "[mod] " << sfile << endl;
	}
      }
      else {
	dst.insert(sfile);
	cout << "[new] " << sfile << endl; 
      }
    }
  }

  return dst;
}