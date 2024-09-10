static void
handle_drop( HDROP hDrop )
{
  size_t bufsize;
  char *namebuf;

  /* Check that only one file was dropped */
  if( DragQueryFile( hDrop, ~0UL, NULL, 0 ) == 1) {
    bufsize = DragQueryFile( hDrop, 0, NULL, 0 ) + 1;
    if( ( namebuf = malloc( bufsize ) ) ) {
      DragQueryFile( hDrop, 0, namebuf, bufsize );

      fuse_emulation_pause();

      utils_open_file( namebuf, tape_can_autoload(), NULL );

      free( namebuf );

      display_refresh_all();

      fuse_emulation_unpause();
    }
  }
  DragFinish( hDrop );
}