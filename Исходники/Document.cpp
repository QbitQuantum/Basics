  const DOMString Document::getNsPrefixForNsUriImplicit(const DOMString nsUriStr) const
  {
    DOMString explicitNsPrefix = getNsPrefixForNsUriExplicit(nsUriStr);
    if(explicitNsPrefix.length()>0) {
      return explicitNsPrefix;
    }

    list<DOMString>::const_iterator it = _unprefixedNamepspaces.begin();
    unsigned int i = _prefixedNamespaces.size() + 1;
    for( ; it != _unprefixedNamepspaces.end(); it++, i++)
    {
      if(*it != nsUriStr) {
        continue;
      }

      ostringstream oss;
      oss << "ns" << i;
      DOMString nsPrefix = oss.str();
      while(1) 
      {
        ostringstream oss;
        oss << "ns" << i;
        nsPrefix = oss.str();
        if(!isPrefixTaken(nsPrefix)) {
          return nsPrefix;
        }
        i++;
      }
      return DOMString(oss.str());
    }
    return "";
  }