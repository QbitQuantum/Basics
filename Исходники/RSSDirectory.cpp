static void ParseItemRSS(CFileItem* item, SResources& resources, TiXmlElement* item_child, const CStdString& name, const CStdString& xmlns, const CStdString& path)
{
  CStdString text = item_child->GetText();
  if (name == "title")
  {
    if(text.length() > item->m_strTitle.length())
      item->m_strTitle = text;
  }
  else if (name == "pubDate")
  {
    CDateTime pubDate(ParseDate(text));
    item->m_dateTime = pubDate;
  }
  else if (name == "link")
  {
    SResource res;
    res.tag  = "rss:link";
    res.path = text;
    resources.push_back(res);
  }
  else if(name == "enclosure")
  {
    const char * len  = item_child->Attribute("length");

    SResource res;
    res.tag = "rss:enclosure";
    res.path = XMLUtils::GetAttribute(item_child, "url");
    res.mime = XMLUtils::GetAttribute(item_child, "type");
    if(len)
      res.size = _atoi64(len);

    resources.push_back(res);
  }
  else if(name == "description")
  {
    CStdString description = text;
    HTML::CHTMLUtil::RemoveTags(description);
    item->SetProperty("description", description);
  }
  else if(name == "guid")
  {
    if(IsPathToMedia(text))
    {
      SResource res;
      res.tag  = "rss:guid";
      res.path = text;
      resources.push_back(res);
    }
  }
}