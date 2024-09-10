  explicit HeaderInfo(const String& filename)
  {
    header_description = "-- empty --";
    TextFile tf;
    tf.load(filename);
    String content;
    content.concatenate(tf.begin(), tf.end(), ";");

    String search = "$$ Sample Description:";
    Size pos = content.find(search);
    if (pos != std::string::npos)
    {
      pos += search.size();
      Size pos_end = content.find("$$", pos);
      if (pos_end != std::string::npos)
      {
        String tmp = content.substr(pos, pos_end - pos - 1);
        if (!tmp.trim().empty()) header_description = tmp;
        //std::cerr << "Header info is: " << header_description << std::endl;
      }
    }
  }