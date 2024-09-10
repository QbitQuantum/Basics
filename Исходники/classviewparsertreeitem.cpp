void ParserTreeItem::convertTo(QStandardItem *item) const
{
    if (!item)
        return;

    QMap<SymbolInformation, ParserTreeItem::Ptr> map;

    // convert to map - to sort it
    CitSymbolInformations curHash = d->symbolInformations.constBegin();
    CitSymbolInformations endHash = d->symbolInformations.constEnd();
    while (curHash != endHash) {
        map.insert(curHash.key(), curHash.value());
        ++curHash;
    }

    typedef QMap<SymbolInformation, ParserTreeItem::Ptr>::const_iterator MapCitSymbolInformations;
    // add to item
    MapCitSymbolInformations cur = map.constBegin();
    MapCitSymbolInformations end = map.constEnd();
    while (cur != end) {
        const SymbolInformation &inf = cur.key();
        ParserTreeItem::Ptr ptr = cur.value();

        QStandardItem *add = new QStandardItem();
        Utils::setSymbolInformationToItem(inf, add);
        if (!ptr.isNull()) {
            // icon
            add->setIcon(ptr->icon());

            // draggable
            if (!ptr->symbolLocations().isEmpty())
                add->setFlags(add->flags() | Qt::ItemIsDragEnabled);

            // locations
            add->setData(Utils::locationsToRole(ptr->symbolLocations()),
                         Constants::SymbolLocationsRole);
        }
        item->appendRow(add);
        ++cur;
    }
}