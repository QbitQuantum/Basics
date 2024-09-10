void QgsLocatorFiltersModel::commitChanges()
{
  QgsSettings settings;

  QHash< QgsLocatorFilter *, QString >::const_iterator itp = mPrefixes.constBegin();
  for ( ; itp != mPrefixes.constEnd(); ++itp )
  {
    QgsLocatorFilter *filter = itp.key();
    QString activePrefix = itp.value();
    if ( !activePrefix.isEmpty() && activePrefix != filter->prefix() )
    {
      filter->setActivePrefix( activePrefix );
      settings.setValue( QStringLiteral( "locator_filters/prefix_%1" ).arg( filter->name() ), activePrefix, QgsSettings::Section::Gui );
    }
    else
    {
      filter->setActivePrefix( QString() );
      settings.remove( QStringLiteral( "locator_filters/prefix_%1" ).arg( filter->name() ), QgsSettings::Section::Gui );
    }
  }
  QHash< QgsLocatorFilter *, bool >::const_iterator it = mEnabledChanges.constBegin();
  for ( ; it != mEnabledChanges.constEnd(); ++it )
  {
    QgsLocatorFilter *filter = it.key();
    settings.setValue( QStringLiteral( "locator_filters/enabled_%1" ).arg( filter->name() ), it.value(), QgsSettings::Section::Gui );
    filter->setEnabled( it.value() );
  }
  it = mDefaultChanges.constBegin();
  for ( ; it != mDefaultChanges.constEnd(); ++it )
  {
    QgsLocatorFilter *filter = it.key();
    settings.setValue( QStringLiteral( "locator_filters/default_%1" ).arg( filter->name() ), it.value(), QgsSettings::Section::Gui );
    filter->setUseWithoutPrefix( it.value() );
  }
}