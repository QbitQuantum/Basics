Artifact DominoDocArtifact::CreateRelatedItem(const std::wstring& filenameToRelate, const std::wstring& type,const std::wstring& AvailableFileFormats,bool ShowUI)
{
// HACKETY
	UNREFERENCED_PARAMETER(AvailableFileFormats);
	UNREFERENCED_PARAMETER(ShowUI);
   if(0 != lstrcmpiW(type.c_str(), L"W3"))
      throw Workshare::ArgumentException(_T("type"), _T("We only support the W3 type"));

   if(filenameToRelate.empty())
      throw Workshare::ArgumentException(_T("filenameToRelate"), _T("We need a file name to create a related item."));

   if(!PathFileExistsW(filenameToRelate.c_str()))
      throw Workshare::System::IO::FileNotFoundException(_bstr_t(filenameToRelate.c_str()), _T("Only files that exist can be uploaded to a Lotus Domino Repository"));

   DominoDoc::IDocumentPtr spDocument = GetDocument();      

   wchar_t tempPath[MAX_PATH] = {0};
   if(0 == ::GetTempPathW(MAX_PATH, tempPath))
   {
      DWORD lastError = ::GetLastError();
      std::tostringstream msg;
      msg << _T("Failed to get the temporary path while uploading artifact, ") << m_documentId << _T(", version, ") << m_versionLabel << _T(" which came from repository, ") << m_libraryUrl << std::ends;
      throw Workshare::System::SystemException(msg.str().c_str(), lastError);
   }

   wchar_t tempFileName[_MAX_PATH] = {0};   
   if(0 == GetTempFileNameW(tempPath, L"WC", 0, tempFileName))
   {
      DWORD lastError = ::GetLastError();
      std::tostringstream msg;
      msg << _T("Failed to get the temporary filename while uploading artifact, ") << m_documentId << _T(", version, ") << m_versionLabel << _T(" which came from repository, ") << m_libraryUrl << std::ends;
      throw Workshare::System::SystemException(msg.str().c_str(), lastError);
   }
   DeleteFileW(tempFileName);  
   PathRemoveExtensionW(tempFileName);
   if(!::CreateDirectoryW(tempFileName, NULL))
   {
      DWORD lastError = ::GetLastError();
      std::tostringstream msg;
      msg << "Failed to create a temporary directory [" << tempFileName << ", to upload [" << filenameToRelate << "] for uploading artifact, " << m_documentId << ", version, " << m_versionLabel << " which came from repository, " << m_libraryUrl << std::ends;
	  throw Workshare::System::SystemException(msg.str().c_str(), lastError);
   }

   wchar_t fileName[MAX_PATH] = {0};
   lstrcpyW(fileName, tempFileName);
   if(spDocument->FileName.length() > 0)
      PathAppendW(fileName,spDocument->FileName);
   else
      PathAppendW(fileName, PathFindFileNameW(filenameToRelate.c_str()));

   PathRemoveExtensionW(fileName);
   lstrcatW(fileName, L".");
   lstrcatW(fileName, type.c_str());   

   if(!CopyFileW(filenameToRelate.c_str(), fileName, TRUE))
   {
      DWORD lastError = ::GetLastError();
      std::tostringstream msg;
      msg << _T("Failed to copy [") << filenameToRelate << _T("] to [") << fileName << _T("] while uploading artifact, ") << m_documentId << _T(", version, ") << m_versionLabel << _T(" which came from repository, ") << m_libraryUrl << std::ends;
      throw Workshare::System::SystemException(msg.str().c_str(), lastError);
   }

   try
   {
      DominoDoc::IBinderPtr spBinder = spDocument->Binder;
      DominoDoc::IDocumentsPtr spDocuments = spBinder->Documents;
      DominoDoc::IDocumentPtr spRelatedDocument = spDocuments->Add();

      std::wstring title = this->Name + L".W3";
      spRelatedDocument->Title = title.c_str();
      spRelatedDocument->Description = L"File Used by workshare during the collaboration process";
      spRelatedDocument->SetContents(fileName);
      spRelatedDocument->Save(); 
      spRelatedDocument->CheckIn(c_revisiontypeVersion, c_actionReplace, VARIANT_TRUE, _T("Workshare Collaboration Document")); 
      
      DeleteFileW(fileName);      
      RemoveDirectoryW(tempFileName);

      return new DominoDocArtifact(spRelatedDocument);
   }
   catch(...)
   {
      DeleteFileW(fileName);
      RemoveDirectoryW(tempFileName);
      throw;
   }  
}