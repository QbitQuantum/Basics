/* load a file */
BOOL MyAppWindow :: LoadFile ( char * p)
{
   // is there already a file loaded or has the user entered some text?
   if(loaded == FALSE && saved == TRUE)
      {
         //no, we load the file in the window of the current thread
         XFile loadfile;

         /* now open the file, fail if given filename is not existing */
         /* open the file for read-access, dont allow any other programm to use the file while it is open*/
         if( loadfile.Open( p, XFILE_FAIL_IF_NEW | XFILE_OPEN_EXISTING, XFILE_SHARE_DENYWRITE | XFILE_READONLY ) == 0)
           {
              XString s;

              loading = TRUE;

              //how large is the file?
              XFileInfo info;
              loadfile.GetFileInfo( &info );
              LONG size = info.GetFileSize();

              //read the complete file
              loadfile.Read ( (PVOID) s.GetBuffer(info.GetFileSize() + 1), size);
              s.ReleaseBuffer( info.GetFileSize() );

              //set the XString content to the mle
              mle->SetText( s );
              //dontïforget to close the file
              loadfile.Close();
              loaded = TRUE;
              path = p;
              mle->SetFocus();
              GetText( &s );
              s+= " - ";
              s+= p;
              SetText( s );

              loading = FALSE;

              return TRUE;
            }
         else
            {
               XMessageBox( p, "couldnït open File!", MB_OK|MB_ERROR);
               return FALSE;
            }
      }
   else
     {
         //there is a file loaded, or the user has entered some text, so
         // we create a new window and load the file
//         XResource res( IDM_MAIN, ((MyApp*) GetProcess())->GetResourceLibrary());
         MyAppWindow * win = new MyAppWindow( IDM_MAIN );
         win->LoadFile(p);
         return TRUE;
     }
}