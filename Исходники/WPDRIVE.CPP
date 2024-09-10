//---------------------------------------------------------------------
// DropTarget():
//    This function is called when this container object is acting as
// a drop target for a Drag & Drop operation.  The first paremeter
// "pwpobjDropSource" is the object in that is being "dropped" into
// this container.
// The second parameter, "nFunction", is the function code for the
// Drag & Drop operation the user chose to do (move, copy, etc..).
//---------------------------------------------------------------------
BOOL WPDIRECTORY::DropTarget(WPOBJECT *pwpobjDropSource,int nFunction)
{
   HCURSOR  hcurOriginal;

   // Check if object class accepts object "pwpobjDropSource" being dropped on it.
   if (TestDropTarget(pwpobjDropSource,nFunction)==TRUE)
   {
      // Depending on which drop operation is being performed...
      switch (nFunction)
      {
         case DROP_MOVE:
         case DROP_COPY:
            // Load custom "wait" cursor (i.e. clock) and set current cursor to it.
            hcurOriginal = SetCursor(LoadCursor(g_wpEnvironment.hInst,MAKEINTRESOURCE(IDC_WAITCURSOR)));
            // Copy actual file(s) represented in object to this directory.
            if (pwpobjDropSource->CopyObjectToFileSystem(GetPath())==TRUE)
            {
               // Update directory folder contents.
               LoadDirectoryFiles();
               // Arrange loaded icons.
               ArrangeIcons();
            }
            // Check if original cursor was not the same as our "wait" cursor...
            if (hcurOriginal!=GetCursor())
               // Restore original cursor and destroy custom wait cursor.
               DestroyCursor(SetCursor(hcurOriginal));
            // Return result.
            return (TRUE);
      }
   }

   // Failed dropping source object into this directory object.
   return (FALSE);
}