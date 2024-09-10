void DirManager::MakeBlockFileName(wxString inProjDir,
                                   wxString &outFileName,
                                   wxString &outPathName)
{
   do {
      outFileName.Printf("b%05d.auf", fileIndex++);
      outPathName = inProjDir + pathChar + outFileName;
   } while (wxFileExists(outPathName));
}