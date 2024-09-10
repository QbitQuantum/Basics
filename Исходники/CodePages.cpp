   int 
   CodePages::GetCodePage(const AnsiString &sName) const
   {
      AnsiString lowerCaseCharSet = sName;
      lowerCaseCharSet.ToLower();

      std::map<AnsiString, int>::const_iterator iter = m_mapCodePages.find(lowerCaseCharSet);

      if (iter == m_mapCodePages.end())
         return 0;

      return (*iter).second;
   }