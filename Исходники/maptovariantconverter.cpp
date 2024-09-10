QVariant MapToVariantConverter::toVariant(const MapObject &object) const
{
    QVariantMap objectVariant;
    const QString &name = object.name();
    const QString &type = object.type();

    addProperties(objectVariant, object.properties());

    if (const ObjectTemplate *objectTemplate = object.objectTemplate()) {
        QString relativeFileName = mMapDir.relativeFilePath(objectTemplate->fileName());
        objectVariant[QLatin1String("template")] = relativeFileName;
    }

    bool notTemplateInstance = !object.isTemplateInstance();

    int id = object.id();
    if (id != 0)
        objectVariant[QLatin1String("id")] = id;

    if (notTemplateInstance || object.propertyChanged(MapObject::NameProperty))
        objectVariant[QLatin1String("name")] = name;

    if (notTemplateInstance || object.propertyChanged(MapObject::TypeProperty))
        objectVariant[QLatin1String("type")] = type;


    if (notTemplateInstance || object.propertyChanged(MapObject::CellProperty))
        if (!object.cell().isEmpty())
            objectVariant[QLatin1String("gid")] = mGidMapper.cellToGid(object.cell());

    if (id != 0) {
        objectVariant[QLatin1String("x")] = object.x();
        objectVariant[QLatin1String("y")] = object.y();
    }

    if (notTemplateInstance || object.propertyChanged(MapObject::SizeProperty)) {
        objectVariant[QLatin1String("width")] = object.width();
        objectVariant[QLatin1String("height")] = object.height();
    }

    if (notTemplateInstance || object.propertyChanged(MapObject::RotationProperty))
        objectVariant[QLatin1String("rotation")] = object.rotation();

    if (notTemplateInstance || object.propertyChanged(MapObject::VisibleProperty))
        objectVariant[QLatin1String("visible")] = object.isVisible();

    /* Polygons are stored in this format:
     *
     *   "polygon/polyline": [
     *       { "x": 0, "y": 0 },
     *       { "x": 1, "y": 1 },
     *       ...
     *   ]
     */
    switch (object.shape()) {
    case MapObject::Rectangle:
        break;
    case MapObject::Polygon:
    case MapObject::Polyline: {
        if (notTemplateInstance || object.propertyChanged(MapObject::ShapeProperty)) {
            QVariantList pointVariants;
            for (const QPointF &point : object.polygon()) {
                QVariantMap pointVariant;
                pointVariant[QLatin1String("x")] = point.x();
                pointVariant[QLatin1String("y")] = point.y();
                pointVariants.append(pointVariant);
            }

            if (object.shape() == MapObject::Polygon)
                objectVariant[QLatin1String("polygon")] = pointVariants;
            else
                objectVariant[QLatin1String("polyline")] = pointVariants;
        }
        break;
    }
    case MapObject::Ellipse:
        if (notTemplateInstance || object.propertyChanged(MapObject::ShapeProperty))
            objectVariant[QLatin1String("ellipse")] = true;
        break;
    case MapObject::Text:
        if (notTemplateInstance || (object.propertyChanged(MapObject::TextProperty) ||
                                    object.propertyChanged(MapObject::TextFontProperty) ||
                                    object.propertyChanged(MapObject::TextAlignmentProperty) ||
                                    object.propertyChanged(MapObject::TextWordWrapProperty) ||
                                    object.propertyChanged(MapObject::TextColorProperty)))
            objectVariant[QLatin1String("text")] = toVariant(object.textData());
        break;
    case MapObject::Point:
        if (notTemplateInstance || object.propertyChanged(MapObject::ShapeProperty))
            objectVariant[QLatin1String("point")] = true;
        break;
    }

    return objectVariant;
}