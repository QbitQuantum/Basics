   DALConnection::ExecutionResult
   PGConnection::TryExecute(const SQLCommand &command, String &sErrorMessage, __int64 *iInsertID, int iIgnoreErrors) 
   {
      String SQL = command.GetQueryString();

      try
      {
         // PG_query-doc:
         // Zero if the query was successful. Non-zero if an error occurred.
         // 
         AnsiString sQuery;
         if (!Unicode::WideToMultiByte(SQL, sQuery))
         {
            ErrorManager::Instance()->ReportError(ErrorManager::Critical, 5106, "PGConnection::TryExecute", "Could not convert string into multi-byte.");
            return DALConnection::DALUnknown;
         }

         PGresult *pResult = PQexec(m_pDBConn, sQuery);

         bool bIgnoreErrors = SQL.Find(_T("[IGNORE-ERRORS]")) >= 0;

         if (!bIgnoreErrors)
         {
            DALConnection::ExecutionResult result = CheckError(pResult, SQL, sErrorMessage);
            if (result != DALSuccess)
            {
               if (pResult != 0)
                  PQclear(pResult);

               return result;
            }
         }

         ExecStatusType iExecResult = PQresultStatus(pResult);
         
         // Check if a value has been returned. Will only occur if we've
         // inserted a value.
         if (iInsertID > 0 && iExecResult == PGRES_TUPLES_OK)
         {
            // pick the ID from the first row.
            char *pRetVal = PQgetvalue(pResult, 0, 0);
            *iInsertID = pRetVal ? _atoi64(pRetVal) : 0;
         }

         if (pResult != 0)
            PQclear(pResult);
        
      }
      catch (...)
      {
         sErrorMessage = "Source: PGConnection::TryExecute, Code: HM5084, Description: An unhanded error occurred while executing: " + SQL;
         return DALConnection::DALUnknown;
      }

      return DALConnection::DALSuccess;
   }