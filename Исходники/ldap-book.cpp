int
OPENLDAP::BookFormInfo (Ekiga::Form &result,
			struct BookInfo &bookinfo,
			std::string &errmsg)
{
  LDAPURLDesc *url_base = NULL, *url_host = NULL;
  char *url_str;

  std::string name = result.text ("name");
  std::string uri = result.text ("uri");
  std::string nameAttr = result.text ("nameAttr");
  std::string callAttr = result.text ("callAttr");
  std::string filter = result.text ("filter");

  errmsg = "";

  if (name.empty())
    errmsg += _("Please provide a Book Name for this directory\n");

  if (uri.empty())
    errmsg += _("Please provide a Server URI\n");

  if (nameAttr.empty())
    errmsg += _("Please provide a DisplayName attribute\n");

  if (callAttr.empty())
    errmsg += _("Please provide a Call attribute\n");

  if (ldap_url_parse (uri.c_str(), &url_host))
    errmsg += _("Invalid Server URI\n");

  if (!errmsg.empty()) {
    return -1;
  }

  if (filter.empty())
    filter = "(cn=$)";

  bookinfo.name = name;
  std::string base = result.text ("base");
  std::string new_bits = "ldap:///?" +
    result.text ("nameAttr") + "," +
    result.text ("callAttr") + "?" +
    result.single_choice ("scope") + "?" +
    result.text ("filter");
  bookinfo.authcID = result.text ("authcID");
  bookinfo.password = result.text ("password");
  bookinfo.starttls = result.boolean ("startTLS");
  bookinfo.sasl = result.boolean ("sasl");
  bookinfo.saslMech = result.single_choice ("saslMech");

  if (bookinfo.sasl || bookinfo.starttls) {
    new_bits += "?";
    if (bookinfo.starttls)
      new_bits += "StartTLS";
    if (bookinfo.sasl) {
      if (bookinfo.starttls)
        new_bits += ",";
      new_bits += "SASL";
      if (!bookinfo.saslMech.empty())
        new_bits += "=" + bookinfo.saslMech;
    }
  }

  if (ldap_url_parse (new_bits.c_str(), &url_base))
    errmsg += _("Invalid Server URI\n");

  if (!errmsg.empty()) {
    return -1;
  }

  url_host->lud_dn = ldap_strdup (base.c_str());
  url_host->lud_attrs = url_base->lud_attrs;
  url_host->lud_scope = url_base->lud_scope;
  url_host->lud_filter = url_base->lud_filter;
  if (!url_host->lud_exts) {
    url_host->lud_exts = url_base->lud_exts;
    url_base->lud_exts = NULL;
  }
  url_base->lud_attrs = NULL;
  url_base->lud_filter = NULL;
  ldap_free_urldesc (url_base);

  bookinfo.urld = boost::shared_ptr<LDAPURLDesc> (url_host, ldap_url_desc_deleter ());
  url_str = ldap_url_desc2str (url_host);
  bookinfo.uri = std::string(url_str);
  ldap_memfree (url_str);

  {
    size_t pos;
    pos = bookinfo.uri.find ('/', strlen(url_host->lud_scheme) + 3);
    if (pos != std::string::npos)
      bookinfo.uri_host = bookinfo.uri.substr (0,pos);
    else
      bookinfo.uri_host = bookinfo.uri;
  }
  return 0;
}