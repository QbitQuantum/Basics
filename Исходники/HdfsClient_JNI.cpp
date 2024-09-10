HDFS_Client_RetCode HdfsClient::getHiveTableMaxModificationTs( Int64& maxModificationTs, const char * tableDirPaths,  int levelDeep)
{
  QRLogger::log(CAT_SQL_HBASE, LL_DEBUG, "Enter HDFSClient_JNI::getHiveTableMaxModificationTs(%s) called.",tableDirPaths);
  if (initJNIEnv() != JOI_OK)
     return HDFS_CLIENT_ERROR_HIVE_TBL_MAX_MODIFICATION_TS_PARAM;
  if (getInstance() == NULL)
     return HDFS_CLIENT_ERROR_HIVE_TBL_MAX_MODIFICATION_TS_PARAM; 
  jstring js_tableDirPaths = jenv_->NewStringUTF(tableDirPaths);
  if (js_tableDirPaths == NULL)
  {
    GetCliGlobals()->setJniErrorStr(getErrorText(HDFS_CLIENT_ERROR_HIVE_TBL_MAX_MODIFICATION_TS_PARAM));
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HIVE_TBL_MAX_MODIFICATION_TS_PARAM;
  }

  jint jlevelDeep = levelDeep;
  tsRecentJMFromJNI = JavaMethods_[JM_HIVE_TBL_MAX_MODIFICATION_TS].jm_full_name;
  jlong jresult = jenv_->CallStaticLongMethod(javaClass_,
                                          JavaMethods_[JM_HIVE_TBL_MAX_MODIFICATION_TS].methodID,
										  js_tableDirPaths, jlevelDeep);
  jenv_->DeleteLocalRef(js_tableDirPaths);
  if (jenv_->ExceptionCheck())
  {
    getExceptionDetails(jenv_);
    logError(CAT_SQL_HBASE, __FILE__, __LINE__);
    logError(CAT_SQL_HBASE, "HDFSClientI::getHiveTableMaxModificationTs()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return HDFS_CLIENT_ERROR_HIVE_TBL_MAX_MODIFICATION_TS_EXCEPTION;
  }
  QRLogger::log(CAT_SQL_HBASE, LL_DEBUG,
       "Exit HDFSClient_JNI::getHiveTableMaxModificationTs() called.");
  maxModificationTs = jresult;
  jenv_->PopLocalFrame(NULL);

  return HDFS_CLIENT_OK;
}