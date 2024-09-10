int CmdPull::execute (std::string& output)
{
  context.footnote ("The 'pull' command is deprecated, and will be removed in a subsequent release.");

  std::vector <std::string> words = context.a3.extract_words ();
  std::string file;
  if (words.size ())
    file = words[0];

  Uri uri (file, "pull");
  uri.parse ();

  if (uri._data.length ())
  {
		Directory location (context.config.get ("data.location"));

    if (! uri.append ("{pending,undo,completed}.data"))
      throw format (STRING_CMD_PULL_NOT_DIR, uri._path);

		Transport* transport;
		if ((transport = Transport::getTransport (uri)) != NULL)
		{
			transport->recv (location._data + "/");
			delete transport;
		}
		else
		{
      // Verify that files are not being copied from rc.data.location to the
      // same place.
      if (Directory (uri._path) == Directory (context.config.get ("data.location")))
        throw std::string (STRING_CMD_PULL_SAME);

      // copy files locally

      // remove {pending,undo,completed}.data
      uri._path = uri.parent();

      Path path1 (uri._path + "undo.data");
      Path path2 (uri._path + "pending.data");
      Path path3 (uri._path + "completed.data");

      if (path1.exists() && path2.exists() && path3.exists())
      {
//        if (confirm ("xxxxxxxxxxxxx"))
//        {
          std::ofstream ofile1 ((location._data + "/undo.data").c_str(), std::ios_base::binary);
          std::ifstream ifile1 (path1._data.c_str()                    , std::ios_base::binary);
          ofile1 << ifile1.rdbuf();

          std::ofstream ofile2 ((location._data + "/pending.data").c_str(), std::ios_base::binary);
          std::ifstream ifile2 (path2._data.c_str()                    , std::ios_base::binary);
          ofile2 << ifile2.rdbuf();

          std::ofstream ofile3 ((location._data + "/completed.data").c_str(), std::ios_base::binary);
          std::ifstream ifile3 (path3._data.c_str()                    , std::ios_base::binary);
          ofile3 << ifile3.rdbuf();
//        }
      }
      else
      {
        throw format (STRING_CMD_PULL_MISSING, uri._path);
      }
		}

    output += format (STRING_CMD_PULL_TRANSFERRED, uri.ToString ()) + "\n";
  }
  else
    throw std::string (STRING_CMD_PULL_NO_URI);

  return 0;
}