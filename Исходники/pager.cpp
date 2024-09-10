    void Pager::paintEvent(QPaintEvent * event)
    {
        QFrame::paintEvent(event);

        if (d->images.size() == 0) { return; }

        // Maximum bounding box of a single page image
        QSize box = clampedBoundingBox();

        // In parametric equation of a circle, the offset from the centre is:
        //     x = a sin t
        // Spread determines how the index of page maps to the above t.

        double h = (double) box.height();
        double w = (double) box.width();
        double a = (width() - w - d->marginLeft - d->marginRight - (d->orientation == Qt::Vertical && d->scrollBar->isVisible() ? d->scrollBar->width() : 0)) / 2.0;
        double _1 = asin(w/a);
        double s = spread();
        double t1 = _1 + s * ((_PI / 2) - _1);

        int limitGrace = 5;
        //int upperLimit = (int) (d->guiIndex + _PI / (2.0 * t1)) + limitGrace + 1; // FIXME shuffle
        int upperLimit = (int) (d->guiIndex + width() / w + 1);
        //int lowerLimit = (int) (d->guiIndex - _PI / (2.0 * t1)) - limitGrace; // FIXME shuffle
        int lowerLimit = (int) (d->guiIndex - width() / w - 1);
        QPainter painter(this);
        painter.setClipRect(rect().adjusted(0, 1, -1, 0));
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.setRenderHint(QPainter::TextAntialiasing, true);
        painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
        QFont f(painter.font());
        f.setPixelSize(9);
        painter.setFont(f);
        painter.translate(width() / 2, 0);
        painter.translate(-box.width() / 2, 0);
        // FIXME shuffle
        double lower = a;
        double upper = (count() - 1) * w - lower;
        double clamp = qBound(lower, d->guiIndex * w, upper);
        painter.translate(-clamp, 0);
        // end FIXME shuffle
        painter.translate(0, d->marginTop);

        painter.setPen(Qt::NoPen);
        if (isActiveWindow())
        {
            painter.setPen(QApplication::palette().highlight().color());
            painter.setBrush(QApplication::palette().highlight());
        }
        else
        {
            int gray = qGray(QApplication::palette().highlight().color().rgb());
            painter.setPen(QColor(gray, gray, gray));
            painter.setBrush(QColor(gray, gray, gray));
        }

        double radius = 4.0;
        double transientWidth = 0.0;
        double transientHeight = 0.0;
        double transientLabelWidth = 0.0;
        double transientLabelBottom = 0.0;
        if (d->images.size() == 1)
        {
            QSize imageSize = d->images[0].size();
            imageSize.scale(box, Qt::KeepAspectRatio);
            transientWidth = imageSize.width();
            transientHeight = imageSize.height();
            if (d->drawLabels && !labelAt(0).isEmpty())
            {
                QRect labelRect(QPoint((box.width() - transientWidth) / 2.0, radius), QPoint(box.width() - (box.width() - transientWidth) / 2.0, 12 + radius));
                QString elidedLabel = painter.fontMetrics().elidedText(labelAt(0), Qt::ElideMiddle, labelRect.width());
                QRect bb(painter.fontMetrics().boundingRect(labelRect, Qt::AlignCenter, elidedLabel));
                transientLabelWidth = (double) bb.width();
                transientLabelBottom = (double) bb.bottom();
            }
        }
        else
        {
            int previousIndex = clampIndex((int) floor(d->guiIndex));
            int nextIndex = clampIndex((int) ceil(d->guiIndex));
            QSize previousSize = box;
            if (!d->images[previousIndex].isNull())
            {
                previousSize = d->images[previousIndex].size();
                previousSize.scale(box, Qt::KeepAspectRatio);
            }
            QSize nextSize = box;
            if (!d->images[nextIndex].isNull())
            {
                nextSize = d->images[nextIndex].size();
                nextSize.scale(box, Qt::KeepAspectRatio);
            }
            transientWidth = previousSize.width() + (nextSize.width() - previousSize.width()) * (d->guiIndex - previousIndex);
            transientHeight = previousSize.height() + (nextSize.height() - previousSize.height()) * (d->guiIndex - previousIndex);
            if (d->drawLabels && !labelAt(previousIndex).isEmpty() && !labelAt(nextIndex).isEmpty())
            {
                double previousLabelWidth = 0.0;
                double previousLabelBottom = 0.0;
                {
                    QRect labelRect(0, box.height() + radius, previousSize.width(), 12);
                    QString elidedLabel = painter.fontMetrics().elidedText(labelAt(previousIndex), Qt::ElideMiddle, labelRect.width());
                    QRect bb(painter.fontMetrics().boundingRect(labelRect, Qt::AlignCenter, elidedLabel));
                    previousLabelWidth = (double) bb.width();
                    previousLabelBottom = (double) bb.bottom();
                }
                double nextLabelWidth = 0.0;
                double nextLabelBottom = 0.0;
                {
                    QRect labelRect(0, box.height() + radius, nextSize.width(), 12);
                    QString elidedLabel = painter.fontMetrics().elidedText(labelAt(nextIndex), Qt::ElideMiddle, labelRect.width());
                    QRect bb(painter.fontMetrics().boundingRect(labelRect, Qt::AlignCenter, elidedLabel));
                    nextLabelWidth = (double) bb.width();
                    nextLabelBottom = (double) bb.bottom();
                }
                transientLabelWidth = previousLabelWidth + (nextLabelWidth - previousLabelWidth) * (d->guiIndex - previousIndex);
                transientLabelBottom = previousLabelBottom + (nextLabelBottom - previousLabelBottom) * (d->guiIndex - previousIndex);
            }
        }
        painter.drawRoundedRect(QRectF(d->guiIndex * w + (box.width() - transientWidth) / 2.0 - radius, box.height() - transientHeight - radius, transientWidth + radius * 2, transientHeight + radius * 2), radius, radius);
        if (d->drawLabels && transientLabelWidth > 0.0 && transientLabelBottom > 0.0)
        {
            painter.drawRoundedRect(QRectF(d->guiIndex * w + (box.width() - transientLabelWidth) / 2.0 - radius, box.height(), transientLabelWidth + radius * 2, transientLabelBottom - box.height() + radius / 2.0), radius, radius);
        }

        painter.setPen(Qt::NoPen);
        QPen pen(QColor(115, 115, 115));
        pen.setJoinStyle(Qt::MiterJoin);
        pen.setWidthF(0.5);
        painter.setPen(pen);
        painter.setBrush(Qt::NoBrush);

        static QVector< double > sin_ts; // FIXME Make a member, not a static variable
        sin_ts.resize(count());

        // Iterate through pages
        double offset = 0.0;
        for (int i = (int) ceil(d->guiIndex); i < count(); ++i)
        {
            if (i < lowerLimit || i > upperLimit) continue;

            double preModifier = d->indexPreModifiers.value(i, 0.0);
            double postModifier = d->indexPostModifiers.value(i, 0.0);
            offset += preModifier;
            if (preModifier >= 0.0)
            {
                double t = (i - (d->guiIndex - offset)) * t1;
                t = qBound(-_PI/2.0, t, _PI/2);
                sin_ts[i] = sin(t);
            }
            else
            {
                sin_ts[i] = 10.0;
            }
            offset += postModifier;
        }

        offset = 0.0;
        for (int i = (int) ceil(d->guiIndex) - 1; i >= 0; --i)
        {
            if (i < lowerLimit || i > upperLimit) continue;

            double preModifier = d->indexPreModifiers.value(i, 0.0);
            double postModifier = d->indexPostModifiers.value(i, 0.0);
            offset += postModifier;
            if (preModifier >= 0.0)
            {
                double t = (i - (d->guiIndex + offset)) * t1;
                t = qBound(-_PI/2.0, t, _PI/2);
                sin_ts[i] = sin(t);
            }
            else
            {
                sin_ts[i] = 10.0;
            }
            offset += preModifier;
        }

        for (int i = 0; i < d->guiIndex; ++i)
        {
            if (i < lowerLimit || i > upperLimit) continue;
            double sin_t = sin_ts.at(i);
            if (sin_t > 1.0) continue;

            double opacity = 1.0;
            if (d->transitionTimes.contains(i) && !d->transitionTimes[i].isNull())
            {
                opacity *= d->transitionTimes[i].elapsed() / 500.0;
            }
            if (i < lowerLimit + limitGrace)
            {
                // opacity *= (i - lowerLimit) / (double) limitGrace; // FIXME shuffle
            }
            painter.setOpacity(opacity);
            QPixmap image = d->images[i].isNull() ? QPixmap(":/images/pager_loading.png") : d->images[i];
            QSize size = image.size();
            size.scale(box, Qt::KeepAspectRatio);
            //double x = sin_t * (a + (w - size.width()) / 2.0) + (w - size.width()) / 2.0; // FIXME shuffle
            double x = w * i + (w - size.width()) / 2.0;
            double y = h - size.height();
            QRect rect((int) x, (int) y, size.width(), size.height());
            painter.drawPixmap(rect, image);
            painter.drawRect(rect);

            if (d->drawLabels)
            {
                QString label = labelAt(i);
                if (!label.isEmpty())
                {
                    QRect labelRect(rect.bottomLeft() + QPoint(0, radius), rect.bottomRight() + QPoint(0, 12 + radius));
                    QString elidedLabel = painter.fontMetrics().elidedText(label, Qt::ElideMiddle, rect.width());

                    painter.save();
                    painter.setPen(QColor(0, 0, 0));

                    QFontMetrics fm(painter.font());

                    QSize numSize = fm.boundingRect(elidedLabel).size();
                    double lozengeRadius = 1 + numSize.height() / 2.0;
                    numSize += QSize(numSize.height(), 0);
                    QRect numRect(0, 0, numSize.width() + 2, numSize.height() + 2);

                    numRect.moveCenter(rect.center());
                    numRect.moveBottom(rect.bottom() + radius + 1);

                    painter.setBrush(Qt::yellow);
                    painter.setPen(QColor(140, 140, 0));
                    painter.drawRoundedRect(numRect, lozengeRadius, lozengeRadius);

                    painter.setPen(Qt::black);
                    painter.drawText(numRect, Qt::AlignCenter, elidedLabel);

                    painter.restore();

                }
            }

            if (d->hasAnnotation.value(i, 0) > 0)
            {
                drawAnnotationTag(&painter, rect);
            }

            if (!d->spotlightsHidden && !d->searchHits.isEmpty())
            {
                drawSearchHits(&painter, d->searchHits.value(i, 0), rect);
            }

            painter.setOpacity(1.0);
        }

        for (int i = count() - 1; i >= d->guiIndex; --i)
        {
            if (i < lowerLimit || i > upperLimit) continue;
            double sin_t = sin_ts.at(i);
            if (sin_t > 1.0) continue;

            double opacity = 1.0;
            if (d->transitionTimes.contains(i) && !d->transitionTimes[i].isNull())
            {
                opacity *= d->transitionTimes[i].elapsed() / 500.0;
            }
            if (i > upperLimit - limitGrace)
            {
                // opacity *= (limitGrace + i - upperLimit) / (double) limitGrace; // FIXME shuffle
            }
            painter.setOpacity(opacity);
            QPixmap image = d->images[i].isNull() ? QPixmap(":/images/pager_loading.png") : d->images[i];
            QSize size = image.size();
            size.scale(box, Qt::KeepAspectRatio);
            //double x = sin_t * (a + (w - size.width()) / 2.0) + (w - size.width()) / 2.0; // FIXME shuffle
            double x = w * i + (w - size.width()) / 2.0;
            double y = h - size.height();
            QRect rect((int) x, (int) y, size.width(), size.height());
            painter.drawPixmap(rect, image);
            painter.drawRect(rect);

            if (d->drawLabels)
            {
                QString label = labelAt(i);
                if (!label.isEmpty())
                {
                    QRect labelRect(rect.bottomLeft() + QPoint(0, radius), rect.bottomRight() + QPoint(0, 12 + radius));
                    QString elidedLabel = painter.fontMetrics().elidedText(label, Qt::ElideMiddle, labelRect.width());
                    painter.save();
                    painter.setPen(QColor(200, 200, 200));
                    painter.setPen(QColor(0, 0, 0));
                    painter.drawText(labelRect, Qt::AlignCenter, elidedLabel);
                    painter.restore();
                }
            }

            if (d->hasAnnotation.value(i, 0) > 0)
            {
                drawAnnotationTag(&painter, rect);
            }

            if (!d->spotlightsHidden && !d->searchHits.isEmpty())
            {
                drawSearchHits(&painter, d->searchHits.value(i, 0), rect);
            }

            painter.setOpacity(1.0);
        }

        sin_ts.clear();
    }