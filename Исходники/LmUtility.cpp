//
// This is the LmUtility.nativeUtils method. It takes one string as
// input and produces one string as output. The output string gets
// written to the first element of the String[] array object passed in
// as the jobjectArray parameter.
//
// Although we do not document this method for customers, there is
// nothing preventing customer code from calling this method. So don't
// put anything in the method that you wouldn't want customers
// doing. Currently this function just serves as an entry point to
// various systems calls such as TMF operations and getting/setting
// environment variables. There is nothing here that customers could
// not do on their own if they wanted to.
//
JNIEXPORT void JNICALL Java_org_trafodion_sql_udr_LmUtility_nativeUtils
(JNIEnv * env, jclass jc, jstring js, jobjectArray joa)
{
  const char *input = env->GetStringUTFChars(js, NULL);
  if (input == NULL)
  {
    // OutOfMemory error already thrown
    return;
  }

  NAString action(input);
  TrimNAStringSpace(action);

  short error;
  NAString result("OK");

  static MXStatement staticStmt;

// LCOV_EXCL_START
  if (action.compareTo("GetTxName", NAString::ignoreCase) == 0)
  {
    Int64 transid;
    error = GETTRANSID((short *) &transid);
    if (error)
    {
      if (error == 75)
      {
        result = "No active transaction";
      }
      else
      {
        result = "GETTRANSID returned ";
        result += LongToNAString((Lng32) error);
      }
      Throw(env, result.data());
    }
    else
    {
      short actualLen;
      char text[256];
      error = TRANSIDTOTEXT(transid, text, 255, &actualLen);
      if (error)
      {
        result = "TRANSIDTOTEXT returned ";
        result += LongToNAString((Lng32) error);
        Throw(env, result);
      }
      else
      {
        text[actualLen] = 0;
        result = text;
      }
    }
  } // GetTxName

  else if (action.compareTo("BeginTx", NAString::ignoreCase) == 0)
  {
    Int32 tag;
    error = BEGINTRANSACTION(&tag);
    if (error)
    {
      result = "BEGINTRANSACTION returned ";
      result += LongToNAString((Lng32) error);
      Throw(env, result);
    }
  } // BeginTx

  else if (action.compareTo("CommitTx", NAString::ignoreCase) == 0)
  {
    error = ENDTRANSACTION();
    if (error)
    {
      if (error == 75)
      {
        result = "No active transaction";
      }
      else
      {
        result = "ENDTRANSACTION returned ";
        result += LongToNAString((Lng32) error);
      }
      Throw(env, result);
    }
  } // CommitTx

  else if (action.compareTo("RollbackTx", NAString::ignoreCase) == 0)
  {
    error = ABORTTRANSACTION();
    if (error)
    {
      if (error == 75)
      {
        result = "No active transaction";
      }
      else
      {
        result = "ABORTTRANSACTION returned ";
        result += LongToNAString((Lng32) error);
      }
      Throw(env, result);
    }
  } // RollbackTx

  else if (action.compareTo("GetProcessId", NAString::ignoreCase) == 0)
  {
    Lng32 pid = GETPID();
    result = LongToNAString(pid);
  } // GetProcessId

  else if (action.index("GetEnv ", 0, NAString::ignoreCase) == 0)
  {
    NAString name = action;
    name.remove(0, str_len("GetEnv "));
    TrimNAStringSpace(name);
    char *value = getenv(name.data());
    if (value != NULL)
    {
      result = value;
    }
    else
    {
      result = "";
    }
  } // GetEnv

  else if (action.index("PutEnv ", 0, NAString::ignoreCase) == 0)
  {
    NAString nameAndValue = action;
    nameAndValue.remove(0, str_len("PutEnv "));
    TrimNAStringSpace(nameAndValue);
    Int32 retcode = putenv((char *) nameAndValue.data());
    if (retcode != 0)
    {
      result = "putenv returned ";
      result += LongToNAString((Lng32) retcode);
      Throw(env, result);
    }
  } // PutEnv

  else if (action.index("LmDebug ", 0, NAString::ignoreCase) == 0)
  {
    NAString name = action;
    name.remove(0, str_len("LmDebug "));
    LM_DEBUG0(name.data());
  } // LmDebug

  else if (action.index("ExecSql ", 0, NAString::ignoreCase) == 0)
  {
    NAString stmtText = action.remove(0, str_len("ExecSql "));

    MXStatement s;
    const char *status = "OK";
    Lng32 retcode = 0;

    retcode = s.init(status);
  
    if (retcode == 0)
    {
      retcode = s.prepare(stmtText.data());
      if (retcode != 0)
      {
        status = "PREPARE failed";
      }
    }
  
    if (retcode == 0)
    {
      retcode = s.execute();
      if (retcode != 0)
      {
        status = "EXECUTE failed";
      }
    }
  
    if (retcode == 0)
    {
      retcode = s.fetchEOD();
      if (retcode != 0)
      {
        status = "FETCH failed";
      }
    }
  
    if (retcode == 0)
    {
      retcode = s.close();
      if (retcode != 0)
      {
        status = "CLOSE failed";
      }
    }

    if (retcode != 0)
    {
      char msg[256];
      sprintf(msg, "[UdrSqlException %d] %s", retcode, status);
      Throw(env, msg);
    }
  
  } // ExecSql

  else if (action.index("FetchSql ", 0, NAString::ignoreCase) == 0)
  {
    // The incoming string is SQL statement text. The code below will
    // prepare and execute the statement then fetch only the first
    // row. It will build one long multi-line string containing all
    // column values, one on each line. The multi-line string can be
    // split by the Java caller into an array of Strings with the
    // split("\n") method.

    Lng32 i;
    NAString stmtText = action.remove(0, str_len("FetchSql "));

    MXStatement s;
    const char *status = "OK";
    Lng32 retcode = 0;

    retcode = s.init(status);
  
    if (!retcode)
    {
      retcode = s.prepare(stmtText.data());
      if (retcode)
        status = "PREPARE failed";
    }
  
    if (!retcode)
    {
      retcode = s.execute();
      if (retcode)
        status = "EXECUTE failed";
    }

    Lng32 numOutColumns = s.getNumOutColumns();
    NABoolean stringsAllocated = FALSE;
    char **argv = NULL;

    if (!retcode && numOutColumns > 0)
    {
      argv = new char *[numOutColumns];
      Lng32 bufLen = 1000;
      for (i = 0; i < numOutColumns; i++)
        argv[i] = new char[bufLen + 1];

      stringsAllocated = TRUE;

      retcode = s.fetchStrings(argv, bufLen);
      if (retcode)
        status = "FETCH STRINGS failed";

      if (!retcode)
      {
        result = argv[0];
        for (i = 1; i < numOutColumns; i++)
        {
          result += "\n";
          result += argv[i];
        }
      }
    }
  
    if (!retcode)
    {
      retcode = s.fetchEOD();
      if (retcode)
        status = "FETCH EOD failed";
    }
  
    if (!retcode)
    {
      retcode = s.close();
      if (retcode)
        status = "CLOSE failed";
    }

    if (stringsAllocated)
    {
      for (i = 0; i < numOutColumns; i++)
        delete [] argv[i];
      delete [] argv;
    }

    if (retcode)
    {
      char msg[256];
      sprintf(msg, "[UdrSqlException %d] %s", retcode, status);
      Throw(env, msg);
    }
  
  } // FetchSql

  else if (action.index("Prepare ", 0, NAString::ignoreCase) == 0)
  {
    NAString stmtText = action.remove(0, str_len("Prepare "));

    const char *status = "OK";
    Lng32 retcode = 0;

    retcode = staticStmt.init(status);
  
    if (retcode == 0)
    {
      retcode = staticStmt.prepare(stmtText.data());
      if (retcode != 0)
      {
        status = "PREPARE failed";
      }
    }
  
    if (retcode)
    {
      char msg[256];
      sprintf(msg, "[UdrSqlException %d] %s", retcode, status);
      Throw(env, msg);
    }

  } // Prepare
  
  else if (action.index("ExecUsingString ", 0, NAString::ignoreCase) == 0)
  {
    NAString data = action.remove(0, str_len("ExecUsingString "));

    const char *status = "OK";
    Lng32 retcode = 0;

    if (retcode == 0)
    {
      retcode = staticStmt.executeUsingString(data.data(),
                                              (Lng32) data.length());
      if (retcode != 0)
      {
        status = "EXECUTE failed";
      }
    }
  
    if (retcode == 0)
    {
      retcode = staticStmt.fetchEOD();
      if (retcode != 0)
      {
        status = "FETCH failed";
      }
    }
  
    if (retcode == 0)
    {
      retcode = staticStmt.close();
      if (retcode != 0)
      {
        status = "CLOSE failed";
      }
    }

    if (retcode != 0)
    {
      char msg[256];
      sprintf(msg, "[UdrSqlException %d] %s", retcode, status);
      Throw(env, msg);
    }
  
  } // ExecUsingString

  else if (action.index("FetchUsingString ", 0, NAString::ignoreCase) == 0)
  {
    NAString data = action.remove(0, str_len("FetchUsingString "));
    const char *status = "OK";
    Lng32 retcode = 0;
    Int32 i = 0;

    if (!retcode)
    {
      retcode = staticStmt.executeUsingString(data.data(),
                                              (Lng32) data.length());
      if (retcode)
        status = "EXECUTE failed";
    }

    Lng32 numOutColumns = staticStmt.getNumOutColumns();
    NABoolean stringsAllocated = FALSE;
    char **argv = NULL;

    if (!retcode && numOutColumns > 0)
    {
      argv = new char *[numOutColumns];
      Lng32 bufLen = 1000;
      for (i = 0; i < numOutColumns; i++)
        argv[i] = new char[bufLen + 1];

      stringsAllocated = TRUE;

      retcode = staticStmt.fetchStrings(argv, bufLen);
      if (retcode)
        status = "FETCH STRINGS failed";

      if (!retcode)
      {
        result = argv[0];
        for (i = 1; i < numOutColumns; i++)
        {
          result += "\n";
          result += argv[i];
        }
      }
    }
  
    if (!retcode)
    {
      retcode = staticStmt.fetchEOD();
      if (retcode)
        status = "FETCH EOD failed";
    }
  
    if (!retcode)
    {
      retcode = staticStmt.close();
      if (retcode)
        status = "CLOSE failed";
    }

    if (stringsAllocated)
    {
      for (i = 0; i < numOutColumns; i++)
        delete [] argv[i];
      delete [] argv;
    }

    if (retcode)
    {
      char msg[256];
      sprintf(msg, "[UdrSqlException %d] %s", retcode, status);
      Throw(env, msg);
    }
  
  } // FetchUsingString

  else
  {
    //
    // Over time other operations can be supported
    //
    result = "Invalid action: ";
    result += action;
    Throw(env, result);
  }
// LCOV_EXCL_STOP

  //
  // Create the Java output string
  //
  if (env->ExceptionCheck() == JNI_FALSE)
  {
    jobject j = env->NewStringUTF(result.data());
    env->SetObjectArrayElement(joa, 0, j);
  }

}