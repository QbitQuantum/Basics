void CKeyboardLayoutConfiguration::readCharMapFromXML(const TiXmlElement* pXMLMap, map<WCHAR, WCHAR>& charToCharMap, const char* mapRootElement)
{
  if (pXMLMap && !pXMLMap->NoChildren())
  { // map keys
    const TiXmlElement* pEntry = pXMLMap->FirstChildElement();
    while (pEntry)
    {
      CStdString strInChar = pEntry->Attribute("inchar");
      CStdString strOutChar = pEntry->Attribute("outchar");
      if (strInChar.length() > 0 && strOutChar.length() > 0)
      {
        CStdStringW fromStr;
        g_charsetConverter.utf8ToW(strInChar, fromStr);
        CStdStringW toStr;
        g_charsetConverter.utf8ToW(strOutChar, toStr);
        if (fromStr.size()==1 && toStr.size()==1)
        {
          charToCharMap.insert(pair<WCHAR, WCHAR>(fromStr[0], toStr[0]));
          CLog::Log(LOGDEBUG, "insert map entry from %c to %c ", fromStr[0], toStr[0]);
        }
        else
        {
          CLog::Log(LOGERROR, "String from %ls or to %ls does not have the expected length of 1", fromStr.c_str(), toStr.c_str());
        }
      }
      else
      {
        CLog::Log(LOGERROR, "map entry misses attribute <inchar> or <outchar> or content of them");
      }
      pEntry = pEntry->NextSiblingElement();
    }
  }
  else
  {
    CLog::Log(LOGDEBUG, "XML-Configuration doesn't contain expected map root element %s", mapRootElement);
  }
}