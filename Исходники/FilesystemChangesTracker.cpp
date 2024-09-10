void FilesystemChangesRunnable::processChanges()
{
   DWORD dwWaitStatus = WaitForSingleObject( m_dwChangeHandle, 1000 );

   switch ( dwWaitStatus )
   {
      case WAIT_OBJECT_0:
      {
         m_section->enter();
         m_changeFound |= true;
         m_section->leave();

         if ( FindNextChangeNotification( m_dwChangeHandle ) == FALSE )
         {
            LOG( "FilesystemChangesTracker: Error (%d): FindNextChangeNotification function failed.", GetLastError() );
         }
         break;
      }

      case WAIT_TIMEOUT:
      {
         // restart the listener
         if ( FindNextChangeNotification( m_dwChangeHandle ) == FALSE )
         {
            LOG( "FilesystemChangesTracker: Error (%d): FindNextChangeNotification function failed.", GetLastError() );
         }
         break;
      }
   }

}