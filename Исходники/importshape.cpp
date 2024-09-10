void ShapePlug::parseGroup(QDomNode &DOC)
{
    QString tmp = "";
    QString FillCol = "White";
    QString StrokeCol = "Black";
    QString defFillCol = "White";
    QString defStrokeCol = "Black";
    QColor stroke = Qt::black;
    QColor fill = Qt::white;
//	Qt::PenStyle Dash = Qt::SolidLine;
    Qt::PenCapStyle LineEnd = Qt::FlatCap;
    Qt::PenJoinStyle LineJoin = Qt::MiterJoin;
//	int fillStyle = 1;
    double strokewidth = 0.1;
//	bool poly = false;
    while(!DOC.isNull())
    {
        double x1, y1, x2, y2;
        StrokeCol = defStrokeCol;
        FillCol = defFillCol;
        stroke = Qt::black;
        fill = Qt::white;
        //	fillStyle = 1;
        strokewidth = 1.0;
        //	Dash = Qt::SolidLine;
        LineEnd = Qt::FlatCap;
        LineJoin = Qt::MiterJoin;
        FPointArray PoLine;
        PoLine.resize(0);
        QDomElement pg = DOC.toElement();
        QString STag = pg.tagName();
        QString style = pg.attribute( "style", "" ).simplified();
        if (style.isEmpty())
            style = pg.attribute( "svg:style", "" ).simplified();
        QStringList substyles = style.split(';', QString::SkipEmptyParts);
        for( QStringList::Iterator it = substyles.begin(); it != substyles.end(); ++it )
        {
            QStringList substyle = (*it).split(':', QString::SkipEmptyParts);
            QString command(substyle[0].trimmed());
            QString params(substyle[1].trimmed());
            if (command == "fill")
            {
                if (!((params == "foreground") || (params == "background") || (params == "fg") || (params == "bg") || (params == "none") || (params == "default") || (params == "inverse")))
                {
                    if (params == "nofill")
                        FillCol = CommonStrings::None;
                    else
                    {
                        fill.setNamedColor( params );
                        FillCol = "FromDia"+fill.name();
                        ScColor tmp;
                        tmp.fromQColor(fill);
                        tmp.setSpotColor(false);
                        tmp.setRegistrationColor(false);
                        QString fNam = m_Doc->PageColors.tryAddColor(FillCol, tmp);
                        if (fNam == FillCol)
                            importedColors.append(FillCol);
                        FillCol = fNam;
                    }
                }
            }
            else if (command == "stroke")
            {
                if (!((params == "foreground") || (params == "background") || (params == "fg") || (params == "bg") || (params == "none") || (params == "default")) || (params == "inverse"))
                {
                    stroke.setNamedColor( params );
                    StrokeCol = "FromDia"+stroke.name();
                    ScColor tmp;
                    tmp.fromQColor(stroke);
                    tmp.setSpotColor(false);
                    tmp.setRegistrationColor(false);
                    QString fNam = m_Doc->PageColors.tryAddColor(StrokeCol, tmp);
                    if (fNam == StrokeCol)
                        importedColors.append(StrokeCol);
                    StrokeCol = fNam;
                }
            }
            else if (command == "stroke-width")
                strokewidth = ScCLocale::toDoubleC(params);
            else if( command == "stroke-linejoin" )
            {
                if( params == "miter" )
                    LineJoin = Qt::MiterJoin;
                else if( params == "round" )
                    LineJoin = Qt::RoundJoin;
                else if( params == "bevel" )
                    LineJoin = Qt::BevelJoin;
            }
            else if( command == "stroke-linecap" )
            {
                if( params == "butt" )
                    LineEnd = Qt::FlatCap;
                else if( params == "round" )
                    LineEnd = Qt::RoundCap;
                else if( params == "square" )
                    LineEnd = Qt::SquareCap;
            }
        }
        if (STag == "svg:line")
        {
            x1 = ScCLocale::toDoubleC(pg.attribute("x1")) * Conversion;
            y1 = ScCLocale::toDoubleC(pg.attribute("y1")) * Conversion;
            x2 = ScCLocale::toDoubleC(pg.attribute("x2")) * Conversion;
            y2 = ScCLocale::toDoubleC(pg.attribute("y2")) * Conversion;
            PoLine.addPoint(x1, y1);
            PoLine.addPoint(x1, y1);
            PoLine.addPoint(x2, y2);
            PoLine.addPoint(x2, y2);
            int z = m_Doc->itemAdd(PageItem::PolyLine, PageItem::Unspecified, baseX, baseY, 10, 10, strokewidth, CommonStrings::None, StrokeCol);
            m_Doc->Items->at(z)->PoLine = PoLine.copy();
            finishItem(m_Doc->Items->at(z));
        }
        else if (STag == "svg:rect")
        {
            x1 = ScCLocale::toDoubleC(pg.attribute("x")) * Conversion;
            y1 = ScCLocale::toDoubleC(pg.attribute("y")) * Conversion;
            x2 = ScCLocale::toDoubleC(pg.attribute("width")) * Conversion;
            y2 = ScCLocale::toDoubleC(pg.attribute("height")) * Conversion;
            int z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Rectangle, baseX + x1, baseY + y1, x2, y2, strokewidth, FillCol, StrokeCol);
            m_Doc->Items->at(z)->setLineJoin(LineJoin);
            m_Doc->Items->at(z)->setLineEnd(LineEnd);
            finishItem(m_Doc->Items->at(z));
        }
        else if ((STag == "svg:polygon") || (STag == "svg:polyline"))
        {
            bool bFirst = true;
            double x = 0.0;
            double y = 0.0;
            QString points = pg.attribute( "points" ).simplified().replace(',', " ");
            QStringList pointList = points.split(' ', QString::SkipEmptyParts);
            FirstM = true;
            for( QStringList::Iterator it = pointList.begin(); it != pointList.end(); it++ )
            {
                x = ScCLocale::toDoubleC(*(it++));
                y = ScCLocale::toDoubleC(*it);
                if( bFirst )
                {
                    svgMoveTo(x * Conversion, y * Conversion);
                    bFirst = false;
                    WasM = true;
                }
                else
                {
                    svgLineTo(&PoLine, x * Conversion, y * Conversion);
                }
            }
            if (STag == "svg:polygon")
                svgClosePath(&PoLine);
            if (PoLine.size() < 4)
            {
                DOC = DOC.nextSibling();
                continue;
            }
            int z;
            if (STag == "svg:polygon")
                z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, baseX, baseY, 10, 10, strokewidth, FillCol, StrokeCol);
            else
                z = m_Doc->itemAdd(PageItem::PolyLine, PageItem::Unspecified, baseX, baseY, 10, 10, strokewidth, CommonStrings::None, StrokeCol);
            m_Doc->Items->at(z)->PoLine = PoLine.copy();
            finishItem(m_Doc->Items->at(z));
        }
        else if ((STag == "svg:circle") || (STag == "svg:ellipse"))
        {
            x1 = ScCLocale::toDoubleC(pg.attribute("r")) * Conversion;
            y1 = ScCLocale::toDoubleC(pg.attribute("r")) * Conversion;
            x2 = ScCLocale::toDoubleC(pg.attribute("cx")) * Conversion - x1;
            y2 = ScCLocale::toDoubleC(pg.attribute("cy")) * Conversion - y1;
            x1 *= 2.0;
            y1 *= 2.0;
            int z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Ellipse, baseX + x1, baseY + y1, x2, y2, strokewidth, FillCol, StrokeCol);
            m_Doc->Items->at(z)->setLineJoin(LineJoin);
            m_Doc->Items->at(z)->setLineEnd(LineEnd);
            finishItem(m_Doc->Items->at(z));
        }
        else if (STag == "svg:path")
        {
            //	poly =
            parseSVG( pg.attribute( "d" ), &PoLine );
            if (PoLine.size() < 4)
            {
                DOC = DOC.nextSibling();
                continue;
            }
            int z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, baseX, baseY, 10, 10, strokewidth, FillCol, StrokeCol);
            m_Doc->Items->at(z)->PoLine = PoLine.copy();
            finishItem(m_Doc->Items->at(z));
        }
        else if (STag == "svg:g")
        {
            int z = m_Doc->itemAdd(PageItem::Group, PageItem::Rectangle, baseX, baseX, 1, 1, 0, CommonStrings::None, CommonStrings::None);
            PageItem *neu = m_Doc->Items->at(z);
            Elements.append(neu);
            if (groupStack.count() > 0)
                groupStack.top().append(neu);
            QList<PageItem*> gElements;
            groupStack.push(gElements);
            QDomNode child = DOC.firstChild();
            parseGroup(child);
            if (gElements.count() == 0)
            {
                groupStack.pop();
                Elements.removeAll(neu);
                groupStack.top().removeAll(neu);
                Selection tmpSelection(m_Doc, false);
                tmpSelection.addItem(neu);
                m_Doc->itemSelection_DeleteItem(&tmpSelection);
            }
            else
            {
                QList<PageItem*> gElem = groupStack.pop();
                double minx =  std::numeric_limits<double>::max();
                double miny =  std::numeric_limits<double>::max();
                double maxx = -std::numeric_limits<double>::max();
                double maxy = -std::numeric_limits<double>::max();
                for (int gr = 0; gr < gElements.count(); ++gr)
                {
                    PageItem* currItem = gElem.at(gr);
                    double x1, x2, y1, y2;
                    currItem->getVisualBoundingRect(&x1, &y1, &x2, &y2);
                    minx = qMin(minx, x1);
                    miny = qMin(miny, y1);
                    maxx = qMax(maxx, x2);
                    maxy = qMax(maxy, y2);
                }
                double gx = minx;
                double gy = miny;
                double gw = maxx - minx;
                double gh = maxy - miny;
                neu->setXYPos(gx, gy, true);
                neu->setWidthHeight(gw, gh, true);
                neu->SetRectFrame();
                neu->Clip = FlattenPath(neu->PoLine, neu->Segments);
                neu->setItemName( tr("Group%1").arg(m_Doc->GroupCounter));
                neu->AutoName = false;
                neu->gXpos = neu->xPos() - gx;
                neu->gYpos = neu->yPos() - gy;
                neu->groupWidth = gw;
                neu->groupHeight = gh;
                for (int gr = 0; gr < gElem.count(); ++gr)
                {
                    PageItem* currItem = gElem.at(gr);
                    currItem->gXpos = currItem->xPos() - gx;
                    currItem->gYpos = currItem->yPos() - gy;
                    currItem->gWidth = gw;
                    currItem->gHeight = gh;
                    currItem->Parent = neu;
                    neu->groupItemList.append(currItem);
                    m_Doc->Items->removeAll(currItem);
                    Elements.removeAll(currItem);
                }
                neu->setRedrawBounding();
                neu->setTextFlowMode(PageItem::TextFlowDisabled);
                m_Doc->GroupCounter++;
            }
        }
        DOC = DOC.nextSibling();
    }
}