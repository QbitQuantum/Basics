/*
 * This function sets the information inside the file selector.
 */
void setCDKFselect (CDKFSELECT *fselect, char *directory, chtype fieldAttrib, chtype filler, chtype highlight, char *dirAttribute, char *fileAttribute, char *linkAttribute, char *sockAttribute, boolean Box GCC_UNUSED)
{
   /* Declare local variables. */
   CDKSCROLL *fscroll	= fselect->scrollField;
   CDKENTRY *fentry	= fselect->entryField;
   char *tempDir	= 0;
   char *mesg[10], newDirectory[2000], temp[100];
   int ret;

   /* Keep the info sent to us. */
   fselect->fieldAttribute	= fieldAttrib;
   fselect->fillerCharacter	= filler;
   fselect->highlight		= highlight;
   strcpy (newDirectory, directory);

   /* Set the attributes of the entry field/scrolling list. */
   setCDKEntryFillerChar (fentry, filler);
   setCDKScrollHighlight (fscroll, highlight);

   /* Only do the directory stuff if the directory is not null. */
   if (directory != 0)
   {
      /* Try to expand the directory if it starts with a ~ */
      if (directory[0] == '~')
      {
	 tempDir = expandFilename (directory);
	 if (tempDir != 0)
	 {
	    strcpy (newDirectory, tempDir);
	    freeChar (tempDir);
	 }
      }

      /* Change directories. */
      ret = chdir (newDirectory);
      if (ret != 0)
      {
	 /* Beep at them. */
	 Beep();

	 /* Couldn't get into the directory, pop up a little message. */
	 sprintf (temp, "<C>Could not change into %s", newDirectory);
	 mesg[0] = copyChar (temp);

#ifdef HAVE_STRERROR
	 sprintf (temp, "<C></U>%s", strerror(errno));
	 mesg[1] = copyChar (temp);
#else
	 sprintf (temp, "<C></U>Unknown reason.");
	 mesg[1] = copyChar (temp);
#endif

	 mesg[2] = " ";
	 mesg[3] = "<C>Press Any Key To Continue.";

	 /* Pop Up a message. */
	 popupLabel (ScreenOf(fselect), mesg, 4);

	 /* Clean up some memory. */
	 freeCharList (mesg, 4);

	 /* Get out of here. */
	 eraseCDKFselect (fselect);
	 drawCDKFselect (fselect, ObjOf(fselect)->box);
	 return;
      }
   }

   /*
    * If the information coming in is the same as the information
    * that is already there, there is no need to destroy it.
    */
   if (fselect->pwd != directory)
   {
      setPWD(fselect);
   }
   if (fselect->fileAttribute != fileAttribute)
   {
      /* Remove the old pointer and set the new value. */
      freeChar (fselect->fileAttribute);
      fselect->fileAttribute = copyChar (fileAttribute);
   }
   if (fselect->dirAttribute != dirAttribute)
   {
      /* Remove the old pointer and set the new value. */
      freeChar (fselect->dirAttribute);
      fselect->dirAttribute = copyChar (dirAttribute);
   }
   if (fselect->linkAttribute != linkAttribute)
   {
      /* Remove the old pointer and set the new value. */
      freeChar (fselect->linkAttribute);
      fselect->linkAttribute = copyChar (linkAttribute);
   }
   if (fselect->sockAttribute != sockAttribute)
   {
      /* Remove the old pointer and set the new value. */
      freeChar (fselect->sockAttribute);
      fselect->sockAttribute = copyChar (sockAttribute);
   }

   /* Set the contents of the entry field. */
   setCDKEntryValue (fentry, fselect->pwd);
   drawCDKEntry (fentry, ObjOf(fentry)->box);

   /* Get the directory contents. */
   if (setCDKFselectDirContents (fselect) == 0)
   {
      Beep();
      return;
   }

   /* Set the values in the scrolling list. */
   setCDKScrollItems (fscroll,
			fselect->dirContents,
			fselect->fileCounter,
			FALSE);
}