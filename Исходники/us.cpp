void US_Win::closeProcs( void )
{
  QString                    names;
  QList<procData*>::iterator p;
  
  for ( p = procs.begin(); p != procs.end(); p++ )
  {
    procData* d  = *p;
    names       += d->name + "\n";
  }

  QString isAre  = ( procs.size() > 1 ) ? "es are" : " is";
  QString itThem = ( procs.size() > 1 ) ? "them"   : "it";
  
  QMessageBox box;
  box.setWindowTitle( tr( "Attention" ) );
  box.setText( QString( tr( "The following process%1 still running:\n%2"
                            "Do you want to close %3?" )
                             .arg( isAre ).arg( names ).arg( itThem ) ) );

  QString killText  = tr( "&Kill" );
  QString closeText = tr( "&Close Gracefully" );
  QString leaveText = tr( "&Leave Running" );

  QPushButton* kill  = box.addButton( killText , QMessageBox::YesRole );
                       box.addButton( closeText, QMessageBox::YesRole );
  QPushButton* leave = box.addButton( leaveText, QMessageBox::NoRole  );

  box.exec();

  if ( box.clickedButton() == leave ) return;

  for ( p = procs.begin(); p != procs.end(); p++ )
  {
    procData* d       = *p;
    QProcess* process = d->proc;
    
    if ( box.clickedButton() == kill )
      process->kill();
    else
      process->terminate();
  }

  // We need to sleep slightly (one millisecond) so that the system can clean 
  // up and properly release shared memory.
  g.scheduleDelete();
  US_Sleep::msleep( 1 );
}