    QRegion KRITAIMAGE_EXPORT splitPath(const QPainterPath &path)
    {
        QRect totalRect = path.boundingRect().toAlignedRect();

        // adjust the rect for antialiasing to work
        totalRect = totalRect.adjusted(-1,-1,1,1);

        const int step = 64;
        const int right = totalRect.x() + totalRect.width();
        const int bottom = totalRect.y() + totalRect.height();

        QRegion dirtyRegion;


        for (int y = totalRect.y(); y < bottom;) {
            int nextY = qMin((y + step) & ~(step-1), bottom);

            for (int x = totalRect.x(); x < right;) {
                int nextX = qMin((x + step) & ~(step-1), right);

                QRect rect(x, y, nextX - x, nextY - y);

                if(path.intersects(rect)) {
                    dirtyRegion |= rect;
                }

                x = nextX;
            }
            y = nextY;
        }

        return dirtyRegion;
    }