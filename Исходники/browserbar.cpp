 Splitter( BrowserBar *w ) : QWidget( w, "divider" )
 {
     setCursor( QCursor(SplitHCursor) );
     styleChange( style() );
 }