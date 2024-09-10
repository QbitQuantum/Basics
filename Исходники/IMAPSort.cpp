      //Return true if s1 < s2; otherwise, return false.
      bool operator()(const std::pair<int, std::shared_ptr<Message> > p1, const std::pair<int, std::shared_ptr<Message> >  p2)
      {
         String sHeader1 = _mapHeaderFields[p1.second->GetID()];
         String sHeader2 = _mapHeaderFields[p2.second->GetID()];
         
         int compare_result = 0;

         if (character_set_.CompareNoCase(_T("US-ASCII")) == 0)
         {
            AnsiString ansi_1 = sHeader1;
            AnsiString ansi_2 = sHeader2;

            return ansi_1 < ansi_2;
         }
         else
         {
            // Use UTF8 as default.
            compare_result = CompareStringW(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE, sHeader1, -1, sHeader2, -1);
         }

         if (compare_result == 0)
            ErrorManager::Instance()->ReportError(ErrorManager::Medium, 5019, "IMAPSortHeaderField::operator()", "An error occurred while sorting. Check system locale settings.");

         if (compare_result == CSTR_LESS_THAN)
            return true;
         else
            return false;  
      }