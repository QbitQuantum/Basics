QRectF KPathShape::loadOdfViewbox(const KXmlElement & element) const
{
    QRectF viewbox;

    QString data = element.attributeNS(KOdfXmlNS::svg, "viewBox");
    if (! data.isEmpty()) {
        data.replace(',', ' ');
        QStringList coordinates = data.simplified().split(' ', QString::SkipEmptyParts);
        if (coordinates.count() == 4) {
            viewbox.setRect(coordinates[0].toDouble(), coordinates[1].toDouble(),
                            coordinates[2].toDouble(), coordinates[3].toDouble());
        }
    }

    return viewbox;
}