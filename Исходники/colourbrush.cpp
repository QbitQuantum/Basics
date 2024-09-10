void ColourBrush::configureBrush(const QVector<QPoint> &list)
{
    if (!mStamp)
        return;

    QRegion reg;
    QRegion stampRegion;

    if (mIsRandom)
        stampRegion = brushItem()->colourLayer()->region();
    else
        stampRegion = mStamp->region();

    Map *map = mapDocument()->map();

    ColourLayer *stamp = new ColourLayer(QString(), 0, 0,
                                     map->width(), map->height());

    foreach (const QPoint p, list) {
        const QRegion update = stampRegion.translated(p.x() - mStampX,
                                                      p.y() - mStampY);
        if (!reg.intersects(update)) {
            reg += update;

            if (mIsRandom) {
                ColourLayer *newStamp = getRandomColourLayer();
                stamp->merge(p, newStamp);
                delete newStamp;
            } else {
                stamp->merge(p, mStamp);
            }

        }
    }

    brushItem()->setColourLayer(stamp);
    delete stamp;
}