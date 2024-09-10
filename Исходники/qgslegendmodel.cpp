void QgsLegendModel::addLayer( QgsMapLayer* theMapLayer )
{
    if ( !theMapLayer )
    {
        return;
    }

    QgsComposerLayerItem* layerItem = new QgsComposerLayerItem( theMapLayer->name() );
    layerItem->setLayerID( theMapLayer->id() );
    layerItem->setDefaultStyle();
    layerItem->setFlags( Qt::ItemIsEnabled | Qt::ItemIsSelectable );

    QList<QStandardItem *> itemsList;
    itemsList << layerItem << new QgsComposerStyleItem( layerItem );
    invisibleRootItem()->appendRow( itemsList );

    switch ( theMapLayer->type() )
    {
    case QgsMapLayer::VectorLayer:
    {
        QgsVectorLayer* vl = dynamic_cast<QgsVectorLayer*>( theMapLayer );
        if ( vl )
        {
            addVectorLayerItemsV2( layerItem, vl );
        }
        break;
    }
    case QgsMapLayer::RasterLayer:
        addRasterLayerItems( layerItem, theMapLayer );
        break;
    default:
        break;
    }
    emit layersChanged();
}