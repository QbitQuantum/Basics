void OsmTagEditorWidgetPrivate::populateCurrentTagsList()
{
    // Name tag
    if ( !m_placemark->name().isEmpty() ) {
        QStringList itemText;

        // "name" is a standard OSM tag, don't translate
        itemText<< "name" << m_placemark->name();
        QTreeWidgetItem *nameTag = new QTreeWidgetItem( itemText );
        nameTag->setDisabled( true );
        m_currentTagsList->addTopLevelItem( nameTag );
    }

    // Multipolygon type tag
    if ( m_placemark->geometry()->nodeType() == GeoDataTypes::GeoDataPolygonType ) {
        QStringList itemText;
        // "type" is a standard OSM tag, don't translate
        itemText<< "type" << "multipolygon";
        QTreeWidgetItem *typeTag = new QTreeWidgetItem( itemText );
        typeTag->setDisabled( true );
        m_currentTagsList->addTopLevelItem( typeTag );
    }

    // Other tags
    if( m_placemark->hasOsmData() ) {
        OsmPlacemarkData osmData = m_placemark->osmData();
        QHash< QString, QString>::const_iterator it = osmData.tagsBegin();
        QHash< QString, QString>::const_iterator end = osmData.tagsEnd();
        for ( ; it != end; ++it ) {
            QTreeWidgetItem *tagItem = tagWidgetItem( OsmPresetLibrary::OsmTag( it.key(), it.value() ) );
            m_currentTagsList->addTopLevelItem( tagItem );
        }
    }

    // Custom tag adder item
    QTreeWidgetItem *adderItem = new QTreeWidgetItem();
    adderItem->setText( 0, m_customTagAdderText );
    adderItem->setTextColor( 0, Qt::gray );
    adderItem->setIcon( 0, QIcon( ":marble/list-add.png" ) );
    adderItem->setFlags( adderItem->flags() | Qt::ItemIsEditable );
    m_currentTagsList->addTopLevelItem( adderItem );
    m_currentTagsList->resizeColumnToContents( 0 );
    m_currentTagsList->resizeColumnToContents( 1 );


}