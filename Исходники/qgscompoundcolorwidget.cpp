void QgsCompoundColorWidget::schemeIndexChanged( int index )
{
  //save changes to scheme
  if ( mSchemeList->isDirty() )
  {
    mSchemeList->saveColorsToScheme();
  }

  //get schemes with ShowInColorDialog set
  QList<QgsColorScheme *> schemeList = QgsApplication::colorSchemeRegistry()->schemes( QgsColorScheme::ShowInColorDialog );
  if ( index >= schemeList.length() )
  {
    return;
  }

  QgsColorScheme *scheme = schemeList.at( index );
  mSchemeList->setScheme( scheme );

  updateActionsForCurrentScheme();

  //copy action defaults to disabled
  mActionCopyColors->setEnabled( false );
}