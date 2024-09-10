int CmdMerge::execute (std::string& output)
{
  context.footnote ("The 'merge' command is deprecated, and will be removed in a subsequent release.");

  // invoke gc and commit before merging in order to update data files
  context.tdb2.gc ();
  context.tdb2.commit ();

  std::vector <std::string> words = context.a3.extract_words ();
  std::string file;
  if (words.size ())
    file = words[0];

  std::string pushfile = "";
  std::string tmpfile = "";

  std::string sAutopush = lowerCase (context.config.get        ("merge.autopush"));
  bool        bAutopush =            context.config.getBoolean ("merge.autopush");

  Uri uri (file, "merge");
  uri.parse();

  if (uri._data.length ())
  {
    Directory location (context.config.get ("data.location"));

    // be sure that uri points to a file
    uri.append ("undo.data");

    Transport* transport;
    if ((transport = Transport::getTransport (uri)) != NULL )
    {
      tmpfile = location._data + "/undo_remote.data";
      transport->recv (tmpfile);
      delete transport;

      file = tmpfile;
    }
    else
      file = uri._path;

    // XXX the following function could indicate whether a modification was
    // performed without an exception (by returning a boolean, within a status
    // object or with a specific function)
    try
    {
        context.tdb2.merge (file);
    }
    catch (const std::string& e) {
        if (e == STRING_TDB2_UP_TO_DATE)
        {
            output += e + "\n";
            return 0;
        }
        else
            throw e;
    }

    output += std::string (STRING_CMD_MERGE_COMPLETE) + "\n";

    if (tmpfile != "")
      remove (tmpfile.c_str ());

    if (((sAutopush == "ask") && (confirm (format (STRING_CMD_MERGE_CONFIRM, uri.ToString ()))))
       || (bAutopush))
    {
      // Derive autopush uri from merge.default.uri? otherwise: change prompt above

      // Change the "merge" command to "push".
      std::vector <Arg>::iterator i;
      for (i = context.a3.begin (); i != context.a3.end (); ++i)
      {
        if (i->_category == Arg::cat_command)
        {
          i->_raw = "push";
          break;
        }
      }

      // Append the URI argument.
      context.a3.push_back (Arg (uri._data, Arg::cat_literal));

      std::string out;
      assert (context.commands["push"]);
      context.commands["push"]->execute (out);
    }
  }
  else
    throw std::string (STRING_CMD_MERGE_NO_URI);

  return 0;
}