   unsigned int
   DateTime::ToInt() const
   {
      struct tm tmTemp;

      if (GetStatus() == valid && TmFromOleDate(dt_, tmTemp))
      {
         tmTemp.tm_year -= 1900;
         tmTemp.tm_mon -= 1;

         time_t rawTime = _mkgmtime64(&tmTemp);

         int err = GetLastError();
         if (rawTime == -1)
            return 0;

         return (unsigned int) rawTime;
      }
      else
      {
         ErrorManager::Instance()->ReportError(ErrorManager::High, 5160, "DateTime::ToInt()", "Tried to convert non-date to integral representation.");
         return 0;
      }

   }