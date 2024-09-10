// ---------------------------------------------------------------------------
QgsPGLayerItem::QgsPGLayerItem( QgsDataItem *parent, const QString &name, const QString &path, QgsLayerItem::LayerType layerType, const QgsPostgresLayerProperty &layerProperty )
  : QgsLayerItem( parent, name, path, QString(), layerType, QStringLiteral( "postgres" ) )
  , mLayerProperty( layerProperty )
{
  mCapabilities |= Delete;
  mUri = createUri();
  setState( Populated );
  Q_ASSERT( mLayerProperty.size() == 1 );
}