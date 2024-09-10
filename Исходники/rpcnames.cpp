json_spirit::Value
name_scan (const json_spirit::Array& params, bool fHelp)
{
  if (fHelp || params.size () > 2)
    throw std::runtime_error (
        "name_scan (\"start\" (\"count\"))\n"
        "\nList names in the database.\n"
        "\nArguments:\n"
        "1. \"start\"       (string, optional) skip initially to this name\n"
        "2. \"count\"       (numeric, optional, default=500) stop after this many names\n"
        "\nResult:\n"
        "[\n"
        + getNameInfoHelp ("  ", ",") +
        "  ...\n"
        "]\n"
        "\nExamples:\n"
        + HelpExampleCli ("name_scan", "")
        + HelpExampleCli ("name_scan", "\"d/abc\"")
        + HelpExampleCli ("name_scan", "\"d/abc\" 10")
        + HelpExampleRpc ("name_scan", "\"d/abc\"")
      );

  if (IsInitialBlockDownload ())
    throw JSONRPCError(RPC_CLIENT_IN_INITIAL_DOWNLOAD,
                       "Namecoin is downloading blocks...");

  valtype start;
  if (params.size () >= 1)
    start = ValtypeFromString (params[0].get_str ());

  int count = 500;
  if (params.size () >= 2)
    count = params[1].get_int ();

  json_spirit::Array res;
  if (count <= 0)
    return res;

  {
    LOCK (cs_main);
    pcoinsTip->Flush ();

    valtype name;
    CNameData data;
    for (std::auto_ptr<CNameIterator> iter(pcoinsTip->IterateNames (start));
         count > 0 && iter->next (name, data); --count)
      res.push_back (getNameInfo (name, data));
  }

  return res;
}