void RegistrationDbTestContext::ConvertRelativeExpirations(
   OsFile* templateFile, ///< input
   OsFile* workingFile   ///< output
                                                           )
{
   // the files are already open
   UtlString line;
   long timeNow = OsDateTime::getSecsSinceEpoch();
   while (templateFile->readLine(line) == OS_SUCCESS)
   {
      timeShiftExpiresLine(line, timeNow);
      line.append("\n");
      size_t bytesWritten = 0;
      CPPUNIT_ASSERT_EQUAL(OS_SUCCESS, workingFile->write(line.data(), line.length(), bytesWritten));
      CPPUNIT_ASSERT_EQUAL(line.length(), bytesWritten);
   }
   // the files will be closed by the wrapper
}