UniValue
name_filter (const UniValue& params, bool fHelp)
{
  if (fHelp || params.size () > 5)
    throw std::runtime_error (
        "name_filter (\"regexp\" (\"maxage\" (\"from\" (\"nb\" (\"stat\")))))\n"
        "\nScan and list names matching a regular expression.\n"
        "\nArguments:\n"
        "1. \"regexp\"      (string, optional) filter names with this regexp\n"
        "2. \"maxage\"      (numeric, optional, default=36000) only consider names updated in the last \"maxage\" blocks; 0 means all names\n"
        "3. \"from\"        (numeric, optional, default=0) return from this position onward; index starts at 0\n"
        "4. \"nb\"          (numeric, optional, default=0) return only \"nb\" entries; 0 means all\n"
        "5. \"stat\"        (string, optional) if set to the string \"stat\", print statistics instead of returning the names\n"
        "\nResult:\n"
        "[\n"
        + getNameInfoHelp ("  ", ",") +
        "  ...\n"
        "]\n"
        "\nExamples:\n"
        + HelpExampleCli ("name_filter", "\"\" 5")
        + HelpExampleCli ("name_filter", "\"^id/\"")
        + HelpExampleCli ("name_filter", "\"^id/\" 36000 0 0 \"stat\"")
        + HelpExampleRpc ("name_scan", "\"^d/\"")
      );

  if (IsInitialBlockDownload ())
    throw JSONRPCError(RPC_CLIENT_IN_INITIAL_DOWNLOAD,
                       "Namecoin is downloading blocks...");

  /* ********************** */
  /* Interpret parameters.  */

  bool haveRegexp(false);
  boost::xpressive::sregex regexp;

  int maxage(36000), from(0), nb(0);
  bool stats(false);

  if (params.size () >= 1)
    {
      haveRegexp = true;
      regexp = boost::xpressive::sregex::compile (params[0].get_str ());
    }

  if (params.size () >= 2)
    maxage = params[1].get_int ();
  if (maxage < 0)
    throw JSONRPCError (RPC_INVALID_PARAMETER,
                        "'maxage' should be non-negative");
  if (params.size () >= 3)
    from = params[2].get_int ();
  if (from < 0)
    throw JSONRPCError (RPC_INVALID_PARAMETER, "'from' should be non-negative");

  if (params.size () >= 4)
    nb = params[3].get_int ();
  if (nb < 0)
    throw JSONRPCError (RPC_INVALID_PARAMETER, "'nb' should be non-negative");

  if (params.size () >= 5)
    {
      if (params[4].get_str () != "stat")
        throw JSONRPCError (RPC_INVALID_PARAMETER,
                            "fifth argument must be the literal string 'stat'");
      stats = true;
    }

  /* ******************************************* */
  /* Iterate over names to build up the result.  */

  UniValue names(UniValue::VARR);
  unsigned count(0);

  LOCK (cs_main);

  valtype name;
  CNameData data;
  std::unique_ptr<CNameIterator> iter(pcoinsTip->IterateNames ());
  while (iter->next (name, data))
    {
      const int age = chainActive.Height () - data.getHeight ();
      assert (age >= 0);
      if (maxage != 0 && age >= maxage)
        continue;

      if (haveRegexp)
        {
          const std::string nameStr = ValtypeToString (name);
          boost::xpressive::smatch matches;
          if (!boost::xpressive::regex_search (nameStr, matches, regexp))
            continue;
        }

      if (from > 0)
        {
          --from;
          continue;
        }
      assert (from == 0);

      if (stats)
        ++count;
      else
        names.push_back (getNameInfo (name, data));

      if (nb > 0)
        {
          --nb;
          if (nb == 0)
            break;
        }
    }

  /* ********************************************************** */
  /* Return the correct result (take stats mode into account).  */

  if (stats)
    {
      UniValue res(UniValue::VOBJ);
      res.push_back (Pair ("blocks", chainActive.Height ()));
      res.push_back (Pair ("count", static_cast<int> (count)));

      return res;
    }

  return names;
}