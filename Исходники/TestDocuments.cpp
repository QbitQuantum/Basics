void TestDocuments::CreateTestDocument(const CStdString& sFileName, const CStdString& sFileNameToUse)
{
   std::tstring createSourceTestDocument = sFileNameToUse.IsEmpty() ? TEST_FILE_ALLMETADATA : sFileNameToUse;

   if(!Workshare::System::IO::File::Exists(createSourceTestDocument))
      throw Workshare::System::IO::FileNotFoundException(createSourceTestDocument.c_str(), _T("Test file not found"));
   
   if(!MakeSureDirectoryPathExists(CT2A(sFileName)))
      throw Workshare::System::IO::FileNotFoundException(sFileName, _T("Couldn't create directory"));
      
   Workshare::System::IO::File::Copy(createSourceTestDocument, sFileName, true);

   if(!::SetFileAttributes(sFileName, FILE_ATTRIBUTE_NORMAL))
      throw Workshare::System::SystemException(_T("Failed to set file attribute"));
}