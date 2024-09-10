void TemporalConstraintView::paint(
        QPainter* painter,
        const QStyleOptionGraphicsItem*,
        QWidget*)
{
    qreal min_w = minWidth();
    qreal max_w = maxWidth();
    qreal def_w = defaultWidth();
    qreal play_w = playWidth();

    // Draw the stuff present if there is a rack *in the model* ?
    if(presenter().rack())
    {
        // Background
        auto rect = boundingRect();
        rect.adjust(0,15,0,-10);
        rect.setWidth(this->defaultWidth());
        painter->fillRect(rect, m_bgColor);

        // Fake timenode continuation
        auto color = ScenarioStyle::instance().RackSideBorder;
        QPen pen{color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin};
        painter->setPen(pen);
        painter->drawLine(rect.topLeft(), rect.bottomLeft());
        painter->drawLine(rect.topRight(), rect.bottomRight());
    }


    QPainterPath solidPath, dashedPath, leftBrace, rightBrace;

    // Paths
    if(infinite())
    {
        if(min_w != 0.)
        {
            solidPath.lineTo(min_w, 0);

            leftBrace.moveTo(min_w, -10);
            leftBrace.arcTo(min_w - 10, -10, 20, 20, 90, 180);
        }

        // TODO end state should be hidden
        dashedPath.moveTo(min_w, 0);
        dashedPath.lineTo(def_w, 0);
    }
    else if(min_w == max_w) // TODO rigid()
    {
        solidPath.lineTo(def_w, 0);
    }
    else
    {
        if(min_w != 0.)
            solidPath.lineTo(min_w, 0);

        dashedPath.moveTo(min_w, 0);
        dashedPath.lineTo(max_w, 0);

        leftBrace.moveTo(min_w + 10, -10);
        leftBrace.arcTo(min_w, -10, 20, 20, 90, 180);
        leftBrace.closeSubpath();

        rightBrace.moveTo(max_w, 10);
        rightBrace.arcTo(max_w - 10, -10, 20, 20, 270, 180);
        rightBrace.closeSubpath();
        rightBrace.translate(-10, 0); // TODO bleh.
    }

    QPainterPath playedPath;
    if(play_w != 0.)
    {
        playedPath.lineTo(play_w, 0);
    }

    // Colors
    QColor constraintColor;
    // TODO make a switch instead
    if(isSelected())
    {
        constraintColor = ScenarioStyle::instance().ConstraintSelected;
    }
    else if(warning())
    {
        constraintColor = ScenarioStyle::instance().ConstraintWarning;
    }
    else
    {
        constraintColor = ScenarioStyle::instance().ConstraintBase;
    }
    if(! isValid())
    {
        constraintColor = ScenarioStyle::instance().ConstraintInvalid;
        this->setZValue(this->zValue()+ 1);
    }
    else
    {
        this->setZValue(parentObject()->zValue() + 3);
    }

    m_solidPen.setColor(constraintColor);
    m_dashPen.setColor(constraintColor);

    // Drawing
    painter->setPen(m_solidPen);
    if(!solidPath.isEmpty())
        painter->drawPath(solidPath);
    if(!leftBrace.isEmpty())
        painter->drawPath(leftBrace);
    if(!rightBrace.isEmpty())
        painter->drawPath(rightBrace);

    painter->setPen(m_dashPen);
    if(!dashedPath.isEmpty())
        painter->drawPath(dashedPath);

    leftBrace.closeSubpath();
    rightBrace.closeSubpath();

    QPen anotherPen(Qt::transparent, 4);
    painter->setPen(anotherPen);
    QColor blueish = m_solidPen.color().lighter();
    blueish.setAlphaF(0.3);
    painter->setBrush(blueish);
    painter->drawPath(leftBrace);
    painter->drawPath(rightBrace);

    static const QPen playedPen{
        QBrush{ScenarioStyle::instance().ConstraintPlayFill},
        4,
        Qt::SolidLine,
                Qt::RoundCap,
                Qt::RoundJoin
    };

    painter->setPen(playedPen);
    if(!playedPath.isEmpty())
        painter->drawPath(playedPath);


    static const int fontSize = 12;
    QRectF labelRect{0,0, defaultWidth(), (-fontSize - 2.)};
    auto f = ProcessFonts::Sans();
    f.setPointSize(fontSize);

    painter->setFont(f);
    painter->setPen(m_labelColor);
    painter->drawText(labelRect, Qt::AlignCenter, m_label);

#if defined(ISCORE_SCENARIO_DEBUG_RECTS)
    painter->setPen(Qt::darkRed);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(boundingRect());
#endif
}