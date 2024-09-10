/** @brief Processes a single line from a LOF text file, doing whatever is
 * indicated on the line.
 *
 * This function should just return for lines it cannot deal with, and the
 * caller will continue to the next line of the input file
 */
void LOFImportFileHandle::lofOpenFiles(wxString* ln)
{  
   wxStringTokenizer tok(*ln, wxT(" "));
   wxStringTokenizer temptok1(*ln, wxT("\""));
   wxStringTokenizer temptok2(*ln, wxT(" "));
   int tokenplace = 0;
   
   wxString targetfile;
   wxString tokenholder = tok.GetNextToken();
   
   if (tokenholder.IsSameAs(wxT("window"), false))
   {
      // set any duration/offset factors for last window, as all files were called
      doDuration();
      doScrollOffset();
      
      if (windowCalledOnce)
      {
         mProject = CreateNewAudacityProject();
      }

      windowCalledOnce = true;
      
      while (tok.HasMoreTokens())
      {
         tokenholder = tok.GetNextToken();
         
         if (tokenholder.IsSameAs(wxT("offset"), false))
         {
            if (tok.HasMoreTokens())
               tokenholder = tok.GetNextToken();
            
            if (Internat::CompatibleToDouble(tokenholder, &scrollOffset))
            {
               callScrollOffset = true;
            }
            else
            {
               /* i18n-hint: You do not need to translate "LOF" */
               wxMessageBox(_("Invalid window offset in LOF file."),
                            /* i18n-hint: You do not need to translate "LOF" */
                            _("LOF Error"), wxOK | wxCENTRE);
            }
               
            if (tok.HasMoreTokens())
               tokenholder = tok.GetNextToken();
         }
         
         if (tokenholder.IsSameAs(wxT("duration"), false))
         {
            if (tok.HasMoreTokens())
               tokenholder = tok.GetNextToken();
            
            if (Internat::CompatibleToDouble(tokenholder, &durationFactor))
            {
               callDurationFactor = true;
            }
            else
            {
               /* i18n-hint: You do not need to translate "LOF" */
               wxMessageBox(_("Invalid duration in LOF file."),
                            /* i18n-hint: You do not need to translate "LOF" */
                            _("LOF Error"), wxOK | wxCENTRE);
            }
         }     // End if statement

         if (tokenholder.IsSameAs(wxT("#")))
         {
            // # indicates comments; ignore line
            tok = wxStringTokenizer(wxT(""), wxT(" "));
         }
      }     // End while loop
   }        // End if statement handling "window" lines
   
   else if (tokenholder.IsSameAs(wxT("file"), false))
   {

      // To identify filename and open it
      tokenholder = temptok1.GetNextToken();
      targetfile = temptok1.GetNextToken();

      // If path is relative, make absolute path from LOF path
      if(!wxIsAbsolutePath(targetfile)) {
         wxFileName fName(targetfile);
         fName.Normalize(wxPATH_NORM_ALL, mLOFFileName->GetPath(wxPATH_GET_VOLUME | wxPATH_GET_SEPARATOR));
         if(fName.FileExists()) {
            targetfile = fName.GetFullPath();
         }
      }
     
      #ifdef USE_MIDI
      // If file is a midi
      if (targetfile.AfterLast(wxT('.')).IsSameAs(wxT("mid"), false)
          ||  targetfile.AfterLast(wxT('.')).IsSameAs(wxT("midi"), false))
      {
         NoteTrack *nTrack = new NoteTrack(mProject->GetDirManager());
         
         if (::ImportMIDI(targetfile, nTrack))
            mProject->GetTracks()->Add(nTrack);
         else
            delete nTrack;
      }
      
      // If not a midi, open audio file
      else
      {
      #else // !USE_MIDI
         /* if we don't have midi support, go straight on to opening as an
          * audio file. TODO: Some sort of message here? */
      {
      #endif // USE_MIDI
         mProject->OpenFile(targetfile);
      }

      // Set tok to right after filename
      temptok2.SetString(targetfile);
      tokenplace = temptok2.CountTokens();
      
      for (int i = 0; i < tokenplace; i++)
         tokenholder = tok.GetNextToken();
      
      if (tok.HasMoreTokens())
      {
         tokenholder = tok.GetNextToken();
         
         if (tokenholder.IsSameAs(wxT("#")))
         {
            // # indicates comments; ignore line
            tok = wxStringTokenizer(wxT(""), wxT(" "));
         }
         
         if (tokenholder.IsSameAs(wxT("offset"), false))
         {
            if (tok.HasMoreTokens())
               tokenholder = tok.GetNextToken();
            double offset;
           
            // handle an "offset" specifier
            if (Internat::CompatibleToDouble(tokenholder, &offset))
            {
               Track *t;
               TrackListIterator iter(mProject->GetTracks());
               
               t = iter.First();
               
               for (int i = 1; i < CountNumTracks(mProject) - 1; i++)
                  t = iter.Next();

               // t is now the last track in the project, unless the import of
               // all tracks failed, in which case it will be null. In that
               // case we return because we cannot offset a non-existent track.
               if (t == NULL) return;
#ifdef USE_MIDI
               if (targetfile.AfterLast(wxT('.')).IsSameAs(wxT("mid"), false) ||
                   targetfile.AfterLast(wxT('.')).IsSameAs(wxT("midi"), false))
               {
                  wxMessageBox(_("MIDI tracks cannot be offset individually, only audio files can be."),
                               _("LOF Error"), wxOK | wxCENTRE);
               }
               else
#endif
               {
                  if (CountNumTracks(mProject) == 1)
                     t->SetOffset(offset);
                  else
                  {
                     if (t->GetLinked())
                        t->SetOffset(offset);
                     
                     t = iter.Next();
                     t->SetOffset(offset);
                  }
               }
            } // end of converting "offset" argument
            else
            {
               /* i18n-hint: You do not need to translate "LOF" */
               wxMessageBox(_("Invalid track offset in LOF file."),
                            _("LOF Error"), wxOK | wxCENTRE);
            }
         }     // End if statement for "offset" parameters
      }     // End if statement (more tokens after file name)
   }     // End if statement "file" lines
   
   else if (tokenholder.IsSameAs(wxT("#")))