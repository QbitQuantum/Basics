void KWCopyShape::paint(QPainter &painter, const KoViewConverter &converter, KoShapePaintingContext &paintcontext)
{
    Q_ASSERT(m_original);

    //paint all child shapes
    KoShapeContainer* container = dynamic_cast<KoShapeContainer*>(m_original);
    if (container) {
        QList<KoShape*> sortedObjects = container->shapes();
        sortedObjects.append(m_original);
        qSort(sortedObjects.begin(), sortedObjects.end(), KoShape::compareShapeZIndex);

        // Do the following to revert the absolute transformation of the
        // container that is re-applied in shape->absoluteTransformation()
        // later on.  The transformation matrix of the container has already
        // been applied once before this function is called.
        QTransform baseMatrix = container->absoluteTransformation(&converter).inverted() * painter.transform();

        KWPage copypage = m_pageManager->page(this);
        Q_ASSERT(copypage.isValid());
        foreach(KoShape *shape, sortedObjects) {
            painter.save();
            if (shape != m_original) {
                painter.setTransform(shape->absoluteTransformation(&converter) * baseMatrix);
            }
            KoTextShapeData *data = qobject_cast<KoTextShapeData*>(shape->userData());
            if (data == 0) {
                shape->paint(painter, converter, paintcontext);
            }
            else {
                // Since the rootArea is shared between the copyShape and the originalShape we need to
                // temporary switch the used KoTextPage to be sure the proper page-numbers are displayed.
                KWPage originalpage = m_pageManager->page(shape);
                Q_ASSERT(originalpage.isValid());
                KoTextLayoutRootArea *area = data->rootArea();
                bool wasBlockChanges = false;
                if (area) {
                    // We need to block documentChanged() signals emitted cause for example page-variables
                    // may change there content to result in us marking root-areas dirty for relayout else
                    // we could end in an infinite relayout ping-pong.
                    wasBlockChanges = area->documentLayout()->changesBlocked();
                    area->documentLayout()->setBlockChanges(true);
                    area->setPage(new KWPage(copypage));
                }
                shape->paint(painter, converter, paintcontext);
                if (area) {
                    area->setPage(new KWPage(originalpage));
                    area->documentLayout()->setBlockChanges(wasBlockChanges);
                }
            }
            painter.restore();
            if (shape->stroke()) {
                painter.save();
                painter.setTransform(shape->absoluteTransformation(&converter) * baseMatrix);
                shape->stroke()->paint(shape, painter, converter);
                painter.restore();
            }
        }
    } else {