const QList<MapObject*> objectsInRegion(const ObjectGroup *layer,
                                        const QRegion &where)
{
    QList<MapObject*> ret;
    for (MapObject *obj : layer->objects()) {
        // TODO: we are checking bounds, which is only correct for rectangles and
        // tile objects. polygons and polylines are not covered correctly by this
        // erase method (we are in fact deleting too many objects)
        // TODO2: toAlignedRect may even break rects.
        const QRect rect = obj->boundsUseTile().toAlignedRect();

        // QRegion::intersects() returns false for empty regions even if they are
        // contained within the region, so we also check for containment of the
        // top left to include the case of zero size objects.
        if (where.intersects(rect) || where.contains(rect.topLeft()))
            ret += obj;
    }
    return ret;
}