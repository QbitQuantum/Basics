const QList<QPainterPath> TextItems::generateZones(const int Width,
        const int ToleranceR, const int ToleranceY,
        const int Columns) const
{ // Assumes that items are already in column, y, x order!
    // Phase #1: Generate the zones
    QList<QPainterPath> zones;
    foreach (const TextItem &item, items) {
        if (zones.isEmpty()) { // First word becomes first zone
            QPainterPath zone;
            zone.addRect(item.rect);
            zones << zone;
        } else { // Add to an existing zone within tolerance or a new one
            const QRectF tolerantRect = item.rect.adjusted(-ToleranceR,
                    -ToleranceR, ToleranceR, ToleranceR);
            bool found = false;
            for (int i = 0; i < zones.count(); ++i) {
                QPainterPath zone = zones.at(i);
                if (zone.intersects(tolerantRect)) {
                    zone.addRect(item.rect);
                    zones[i] = zone;
                    found = true;
                    break;
                }
            }
            if (!found) {
                QPainterPath zone;
                zone.addRect(item.rect);
                zones << zone;
            }
        }
    }

    // Phase #2: Order the zones by (column, y, x)
    const int Span = Width / Columns;
    QMultiMap<Key, QPainterPath> zonesForColumn;
    foreach (const QPainterPath &zone, zones) {
        const QRect &rect = zone.boundingRect().toRect();
        const int Column = ((Columns == 1) ? 0
            : (rect.width() > Span) ? Columns : rect.right() / Span);
        const int y = normalizedY(static_cast<int>(rect.y()), ToleranceY);
        zonesForColumn.insertMulti(Key(Column, y, rect.x()), zone);
    }
    return zonesForColumn.values();
}