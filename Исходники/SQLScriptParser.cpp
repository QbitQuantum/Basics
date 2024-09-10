   bool 
   SQLScriptParser::PreprocessLine_(String &sLine)
   {
      // Do some basic preprocessing...
      while (sLine.Left(2).Compare(_T("\r\n")) == 0)
         sLine = sLine.Mid(2);
      
      while (sLine.Left(1).Compare(_T(" ")) == 0)
         sLine = sLine.Mid(1);
     
      while (sLine.Left(1).Compare(_T("\t")) == 0)
         sLine = sLine.Mid(1);


      String sTempLine = sLine;

      if (settings_->GetType() == HM::DatabaseSettings::TypeMSSQLCompactEdition)
      {
         if (sTempLine.ToLower().Left(3).Compare(_T("if ")) == 0)
         {
            return false;
         }
         else if (sLine.FindNoCase(_T(" CLUSTERED ")) >= 0)
         {
            sLine.ReplaceNoCase(_T(" CLUSTERED "), _T(" "));
         }
         else if (sLine.FindNoCase(_T("CREATE PROC")) >= 0)
         {
            // Procedures not supported by SQL CE
            return false;
         }

         sLine.Replace(_T("\t"), _T(" "));
         sLine.Replace(_T(" varchar"), _T(" nvarchar"));

      }

      if (sLine.IsEmpty())
         return false;


      return true;
   }