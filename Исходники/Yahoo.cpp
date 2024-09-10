void Yahoo::parseFundamental ()
{
  if (! data.length())
    return;

  if (data.contains("no data available"))
    return;

  QStringList l = QStringList::split("yfnc_tablehead1", data, FALSE);
  int loop;
  Setting fund;
  for (loop = 1; loop < (int) l.count(); loop++)
  {
    QString k = l[loop];
    int p = k.find(">", 0, TRUE);
    if (p == -1)
      continue;
    p++;
    k.remove(0, p);
    p = k.find("<", 0, TRUE);
    if (p == -1)
      continue;
    k.truncate(p);

    if (k.contains("&sup"))
      k.truncate(k.length() - 6);
    if (k.contains("&amp"))
      k.remove(k.find("&", 0, TRUE), 5);
    k = k.stripWhiteSpace();
    if (! k.length())
      continue;

    QString d = l[loop];
    p = d.find("yfnc_tabledata1", 0, TRUE);
    if (p == -1)
      continue;
    p = d.find(">", p, TRUE);
    if (p == -1)
      continue;
    p++;
    d.remove(0, p);
    p = d.find("<", 0, TRUE);
    if (p == -1)
      continue;
    d.truncate(p);
    d = d.stripWhiteSpace();
    if (! d.length())
      continue;

    fund.setData(k, d);
  }

  QString s = dataPath + "/";
  QString ts = "symbol";
  QString ts2;
  currentUrl->getData(ts, ts2);
  QFileInfo fi(ts2);
  if (fi.extension(FALSE).length())
    s.append(fi.extension(FALSE).upper());
  else
    s.append("US");
  s.append("/");
  s.append(ts2);

  if (plug.open(s, chartIndex))
  {
    QString ss(tr("Could not open db"));
    printStatusLogMessage(ss);
    return;
  }

  QString fn = ts2;

  // verify if this chart can be updated by this plugin
  DBIndexItem item;
  chartIndex->getIndexItem(fn, item);
  item.getSymbol(s);
  if (! s.length())
  {
    if(plug.createNewStock())
    {
      plug.close();
      return;
    }

    chartIndex->getIndexItem(fn, item);

    item.setQuotePlugin(pluginName);
    item.setSymbol(ts2);
    QString title = ts2;
    int p = data.find("yfnc_leftnav1", 0, TRUE);
    if (p != -1)
    {
      p = data.find("b>", p, TRUE);
      if (p != -1)
      {
        p = p + 2;
        int p2 = data.find("<", p, TRUE);
        if (p2 != -1)
	{
	  s = data.mid(p, p2 - p);
	  if (s.length())
            title = s;
	}
      }
    }
    item.setTitle(title);

    chartIndex->setIndexItem(fn, item);
  }
  else
  {
    QString s2;
    item.getTitle(s2);
    if (! s.compare(s2))
    {
      int p = data.find("yfnc_leftnav1", 0, TRUE);
      if (p != -1)
      {
        p = data.find("b>", p, TRUE);
        if (p != -1)
        {
          p = p + 2;
          int p2 = data.find("<", p, TRUE);
          if (p2 != -1)
	  {
            s = data.mid(p, p2 - p);
	    if (s.length())
            {
              item.setTitle(s);
              chartIndex->setIndexItem(fn, item);
            }
	  }
	}
      }
    }
  }

//  item.getQuotePlugin(s);
//  if (s.compare(pluginName))
//  {
//    s = ts2 + " - " + tr("skipping update. Source does not match destination");
//    printStatusLogMessage(s);
//    plug.close();
//    return;
//  }

  // include date of this update
  QDate dt = QDate::currentDate();
  ts = "updateDate";
  ts2 = dt.toString("yyyy-MM-dd");
  fund.setData(ts, ts2);
  fund.getString(ts2);
  ts = "Fundamentals";
  chartIndex->setFundamentals(fn, ts2);

  plug.close();

  emit signalWakeup();
}