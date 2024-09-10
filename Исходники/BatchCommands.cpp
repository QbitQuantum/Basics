wxString BatchCommands::BuildCleanFileName(const wxString &fileName, const wxString &extension)
{
   const wxFileName newFileName{ fileName };
   wxString justName = newFileName.GetName();
   wxString pathName = newFileName.GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR);

   if (justName == wxT("")) {
      wxDateTime now = wxDateTime::Now();
      int year = now.GetYear();
      wxDateTime::Month month = now.GetMonth();
      wxString monthName = now.GetMonthName(month);
      int dom = now.GetDay();
      int hour = now.GetHour();
      int minute = now.GetMinute();
      int second = now.GetSecond();
      justName = wxString::Format(wxT("%d-%s-%02d-%02d-%02d-%02d"),
           year, monthName.c_str(), dom, hour, minute, second);

//      SetName(cleanedFileName);
//      bool isStereo;
//      double endTime = project->mTracks->GetEndTime();
//      double startTime = 0.0;
      //OnSelectAll();
      pathName = gPrefs->Read(wxT("/DefaultOpenPath"), ::wxGetCwd());
      ::wxMessageBox(wxString::Format(wxT("Export recording to %s\n/cleaned/%s%s"),
                                      pathName.c_str(), justName.c_str(), extension.c_str()),
                     wxT("Export recording"),
                  wxOK | wxCENTRE);
      pathName += wxT("/");
   }
   wxString cleanedName = pathName;
   cleanedName += wxT("cleaned");
   bool flag  = ::wxFileName::FileExists(cleanedName);
   if (flag == true) {
      ::wxMessageBox(wxT("Cannot create directory 'cleaned'. \nFile already exists that is not a directory"));
      return wxT("");
   }
   ::wxFileName::Mkdir(cleanedName, 0777, wxPATH_MKDIR_FULL); // make sure it exists

   cleanedName += wxT("/");
   cleanedName += justName;
   cleanedName += extension;
   wxGetApp().AddFileToHistory(cleanedName);

   return cleanedName;
}