void
MatrixElement::reconfigure(timeT time, timeT duration, int pitch, int velocity)
{
    const RulerScale *scale = m_scene->getRulerScale();
    int resolution = m_scene->getYResolution();

    double x0 = scale->getXForTime(time);
    double x1 = scale->getXForTime(time + duration);
    m_width = x1 - x0;

    m_velocity = velocity;

    // if the note has TIED_FORWARD or TIED_BACK properties, draw it with a
    // different fill pattern
    bool tiedNote = (event()->has(BaseProperties::TIED_FORWARD) ||
                     event()->has(BaseProperties::TIED_BACKWARD));
    Qt::BrushStyle brushPattern = (tiedNote ? Qt::Dense2Pattern : Qt::SolidPattern);

    QColor colour;
    if (event()->has(BaseProperties::TRIGGER_SEGMENT_ID)) {
        //!!! Using gray for trigger events and events from other, non-active
        // segments won't work.  This should be handled some other way, with a
        // color outside the range of possible velocity choices, which probably
        // leaves some kind of curious light blue or something
        colour = Qt::cyan;
    } else {
        colour = DefaultVelocityColour::getInstance()->getColour(velocity);
    }
    colour.setAlpha(160);

    double fres(resolution);

    if (m_drum) {
        fres = resolution + 1;
        QGraphicsPolygonItem *item = dynamic_cast<QGraphicsPolygonItem *>(m_item);
        if (!item) {
            delete m_item;
            item = new QGraphicsPolygonItem;
            m_item = item;
            m_scene->addItem(m_item);
        }
        QPolygonF polygon;
        polygon << QPointF(0, 0)
                << QPointF(fres/2, fres/2)
                << QPointF(0, fres)
                << QPointF(-fres/2, fres/2)
                << QPointF(0, 0);
        item->setPolygon(polygon);
        item->setPen
            (QPen(GUIPalette::getColour(GUIPalette::MatrixElementBorder), 0));
        item->setBrush(QBrush(colour, brushPattern));
    } else {
        QGraphicsRectItem *item = dynamic_cast<QGraphicsRectItem *>(m_item);
        if (!item) {
            delete m_item;
            item = new QGraphicsRectItem;
            m_item = item;
            m_scene->addItem(m_item);
        }
        float width = m_width;
        if (width < 1) width = 1;
        QRectF rect(0, 0, width, fres + 1);
        item->setRect(rect);
        item->setPen
            (QPen(GUIPalette::getColour(GUIPalette::MatrixElementBorder), 0));
        item->setBrush(QBrush(colour, brushPattern));
    }

    setLayoutX(x0);

    m_item->setData(MatrixElementData, QVariant::fromValue((void *)this));

    // set the Y position taking m_pitchOffset into account, subtracting the
    // opposite of whatever the originating segment transpose was

//    std::cout << "TRANSPOSITION TEST: event pitch: "
//              << (pitch ) << " m_pitchOffset: " << m_pitchOffset
//              << std::endl;

    m_item->setPos(x0, (127 - pitch - m_pitchOffset) * (resolution + 1));

    // set a tooltip explaining why this event is drawn in a different pattern
    if (tiedNote) m_item->setToolTip(QObject::tr("This event is tied to another event."));
}