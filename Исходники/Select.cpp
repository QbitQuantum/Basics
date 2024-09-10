 int64 find( Mailbox * m, int64 ms ) {
     if ( !m || !m->id() )
         return 0;
     MailboxInfo * mi = c.find( m->id() );
     if ( !mi )
         return 0;
     if ( mi->ms < ms )
         c.remove( m->id() );
     if ( mi->ms != ms )
         return 0;
     return mi->fu;
 }