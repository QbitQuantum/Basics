SFR_RetCode SequenceFileReader::getPosition(Int64& pos)
{
  QRLogger::log(CAT_SQL_HDFS_SEQ_FILE_READER, LL_DEBUG, "SequenceFileReader::getPosition(%ld) called.", pos);

  if (initJNIEnv() != JOI_OK)
     return SFR_ERROR_GETPOS_EXCEPTION;

  // long getPosition();
  tsRecentJMFromJNI = JavaMethods_[JM_GETPOS].jm_full_name;
  Int64 result = jenv_->CallLongMethod(javaObj_, JavaMethods_[JM_GETPOS].methodID);

  if (result == -1) 
  {
    logError(CAT_SQL_HDFS_SEQ_FILE_READER, "SequenceFileReader::getPosition()", getLastError());
    jenv_->PopLocalFrame(NULL);
    return SFR_ERROR_GETPOS_EXCEPTION;
  }

  pos = result;
  jenv_->PopLocalFrame(NULL);
  return SFR_OK;
}