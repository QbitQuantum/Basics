void JobManager::setRegionsFile(const QString &filename)
{
    QFile file(filename);
    file.open(QFile::ReadOnly);

    QDomDocument xml;
    if ( !xml.setContent( &file ) ) {
        qDebug() << "Cannot parse xml file with regions.";
        return;
    }

    QDomElement root = xml.documentElement();
    QDomNodeList regions = root.elementsByTagName( "region" );
    for ( unsigned int i = 0; i < regions.length(); ++i ) {
        Region region;
        QDomNode node = regions.item( i );
        if (!node.namedItem("continent").isNull()) {
            region.setContinent(node.namedItem("continent").toElement().text());
        }
        if (!node.namedItem("country").isNull()) {
            region.setCountry(node.namedItem("country").toElement().text());
        }
        if (!node.namedItem("name").isNull()) {
            region.setName(node.namedItem("name").toElement().text());
        }
        if (!node.namedItem("id").isNull()) {
            region.setId(node.namedItem("id").toElement().text());
        }
        if (!node.namedItem("path").isNull()) {
            region.setPath(node.namedItem("path").toElement().text());
        }
        if (!node.namedItem("pbf").isNull()) {
            region.setPbfFile(node.namedItem("pbf").toElement().text());
        }

        if (!region.continent().isEmpty() && !region.name().isEmpty()) {
            m_regions << region;
        }
    }
}