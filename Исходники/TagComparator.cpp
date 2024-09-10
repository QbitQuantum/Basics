void TagComparator::mergeNames(Tags& t1, Tags& t2, Tags& result)
{
  set<QString> altNames, nonAltNames;
  set<QString> toRemove;

  toRemove.insert("alt_name");

  for (Tags::const_iterator it1 = t1.begin(); it1 != t1.end(); it1++)
  {
    if (it1.key() == "alt_name")
    {
      QStringList sl = Tags::split(it1.value());
      altNames.insert(sl.begin(), sl.end());
    }
    else
    {
      if (OsmSchema::getInstance().isAncestor(it1.key(), "abstract_name"))
      {
        result[it1.key()] = it1.value();
        QStringList sl = Tags::split(it1.value());
        // keep track of all the names we've used
        nonAltNames.insert(sl.begin(), sl.end());
        toRemove.insert(it1.key());
      }
    }
  }

  for (Tags::const_iterator it2 = t2.begin(); it2 != t2.end(); it2++)
  {
    if (it2.key() == "alt_name")
    {
      QStringList sl = Tags::split(it2.value());
      altNames.insert(sl.begin(), sl.end());
    }
    else if (result.contains(it2.key()))
    {
      const Qt::CaseSensitivity caseSensitivity =
        _caseSensitive ? Qt::CaseSensitive : Qt::CaseInsensitive;
      if (result[it2.key()].compare(it2.value(), caseSensitivity) != 0)
      {
        QStringList sl = Tags::split(it2.value());
        altNames.insert(sl.begin(), sl.end());
      }
    }
    else
    {
      if (OsmSchema::getInstance().isAncestor(it2.key(), "abstract_name"))
      {
        result[it2.key()] = it2.value();
        QStringList sl = Tags::split(it2.value());
        nonAltNames.insert(sl.begin(), sl.end());
        toRemove.insert(it2.key());
      }
    }
  }

  for (set<QString>::const_iterator it = toRemove.begin(); it != toRemove.end(); it++)
  {
    t1.remove(*it);
    t2.remove(*it);
  }

  // add all the altNames that don't exist in nonAltNames
  QStringList l;
  for (set<QString>::const_iterator it = altNames.begin(); it != altNames.end(); it++)
  {
    if (nonAltNames.find(*it) == nonAltNames.end())
    {
      l.append(*it);
    }
  }

  if (l.size() > 0)
  {
    result.setList("alt_name", l);
  }
}