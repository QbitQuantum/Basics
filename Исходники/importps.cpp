void EPSPlug::parseOutput(QString fn, bool eps)
{
	QString tmp, token, params, lasttoken, lastPath, currPath;
	int z, lcap, ljoin, dc, pagecount;
	int failedImages = 0;
	double dcp;
	bool fillRuleEvenOdd = true;
	PageItem* ite;
	QStack<PageItem*> groupStack;
	QStack< QList<PageItem*> > groupStackP;
	QStack<int>  gsStack;
	QStack<uint> gsStackMarks;
	QFile f(fn);
	lasttoken = "";
	pagecount = 1;
	if (f.open(QIODevice::ReadOnly))
	{
		int fProgress = 0;
		int fSize = (int) f.size();
		if (progressDialog) {
			progressDialog->setTotalSteps("GI", fSize);
			qApp->processEvents();
		}
		lastPath = "";
		currPath = "";
		LineW = 0;
		Opacity = 1;
		CurrColor = CommonStrings::None;
		JoinStyle = Qt::MiterJoin;
		CapStyle = Qt::FlatCap;
		DashPattern.clear();
		ScTextStream ts(&f);
		int line_cnt = 0;
		while (!ts.atEnd() && !cancel)
		{
			tmp = "";
			tmp = ts.readLine();
			if (progressDialog && (++line_cnt % 100 == 0)) {
				int fPos = f.pos();
				int progress = static_cast<int>(ceil(fPos / (double) fSize * 100));
				if (progress > fProgress)
				{
					progressDialog->setProgress("GI", fPos);
					qApp->processEvents();
					fProgress = progress;
				}
			}
			token = tmp.section(' ', 0, 0);
			params = tmp.section(' ', 1, -1, QString::SectionIncludeTrailingSep);
			if (lasttoken == "sp"  && !eps && token != "sp" ) //av: messes up anyway: && (!interactive))
			{
				m_Doc->addPage(pagecount);
				m_Doc->view()->addPage(pagecount, true);
				pagecount++;
			}
			if (token == "n")
			{
				Coords.resize(0);
				FirstM = true;
				WasM = false;
				ClosedPath = false;
			}
			else if (token == "m")
				WasM = true;
			else if (token == "c")
			{
				Curve(&Coords, params);
				currPath += params;
			}
			else if (token == "l")
			{
				LineTo(&Coords, params);
				currPath += params;
			}
			else if (token == "fill-winding")
			{
				fillRuleEvenOdd = false;
			}
			else if (token == "fill-evenodd")
			{
				fillRuleEvenOdd = true;
			}
			else if (token == "f")
			{
				//TODO: pattern -> Imageframe + Clip
				if (Coords.size() != 0)
				{
					if ((Elements.count() != 0) && (lastPath == currPath))
					{
						ite = Elements.last();
						ite->setFillColor(CurrColor);
						ite->setFillTransparency(1.0 - Opacity);
						lastPath = "";
					}
					else
					{
						if (ClosedPath)
							z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, baseX, baseY, 10, 10, LineW, CurrColor, CommonStrings::None);
						else
							z = m_Doc->itemAdd(PageItem::PolyLine, PageItem::Unspecified, baseX, baseY, 10, 10, LineW, CurrColor, CommonStrings::None);
						ite = m_Doc->Items->at(z);
						ite->PoLine = Coords.copy();  //FIXME: try to avoid copy if FPointArray when properly shared
						ite->PoLine.translate(m_Doc->currentPage()->xOffset(), m_Doc->currentPage()->yOffset());
						ite->ClipEdited = true;
						ite->FrameType = 3;
						ite->fillRule = (fillRuleEvenOdd);
						FPoint wh = getMaxClipF(&ite->PoLine);
						ite->setWidthHeight(wh.x(),wh.y());
						ite->Clip = FlattenPath(ite->PoLine, ite->Segments);
						ite->setFillTransparency(1.0 - Opacity);
						ite->setTextFlowMode(PageItem::TextFlowDisabled);
						m_Doc->AdjustItemSize(ite);
						if (ite->itemType() == PageItem::Polygon)
							ite->ContourLine = ite->PoLine.copy();
						if ((groupStack.count() != 0) && (groupStackP.count() != 0))
							groupStackP.top().append(ite);
						Elements.append(ite);
						lastPath = currPath;
					}
					currPath = "";
				}
			}
			else if (token == "s")
			{
				if (Coords.size() != 0)
				{
				//	LineW = qMax(LineW, 0.01); // Set Linewidth to be a least 0.01 pts, a Stroke without a Linewidth makes no sense
					if ((Elements.count() != 0) && (lastPath == currPath))
					{
						ite = Elements.last();
						ite->setLineColor(CurrColor);
						ite->setLineWidth(LineW);
						ite->PLineEnd = CapStyle;
						ite->PLineJoin = JoinStyle;
						ite->setLineTransparency(1.0 - Opacity);
						ite->DashOffset = DashOffset;
						ite->DashValues = DashPattern;
					}
					else
					{
						if (ClosedPath)
							z = m_Doc->itemAdd(PageItem::Polygon, PageItem::Unspecified, baseX, baseY, 10, 10, LineW, CommonStrings::None, CurrColor);
						else
							z = m_Doc->itemAdd(PageItem::PolyLine, PageItem::Unspecified, baseX, baseY, 10, 10, LineW, CommonStrings::None, CurrColor);
						ite = m_Doc->Items->at(z);
						ite->PoLine = Coords.copy(); //FIXME: try to avoid copy when FPointArray is properly shared
						ite->PoLine.translate(m_Doc->currentPage()->xOffset(), m_Doc->currentPage()->yOffset());
						ite->ClipEdited = true;
						ite->FrameType = 3;
						ite->PLineEnd = CapStyle;
						ite->PLineJoin = JoinStyle;
						ite->DashOffset = DashOffset;
						ite->DashValues = DashPattern;
						FPoint wh = getMaxClipF(&ite->PoLine);
						ite->setWidthHeight(wh.x(), wh.y());
						ite->Clip = FlattenPath(ite->PoLine, ite->Segments);
						ite->setLineTransparency(1.0 - Opacity);
						m_Doc->AdjustItemSize(ite);
						if (ite->itemType() == PageItem::Polygon)
							ite->ContourLine = ite->PoLine.copy();
						ite->setLineWidth(LineW);
						ite->setTextFlowMode(PageItem::TextFlowDisabled);
						if ((groupStack.count() != 0) && (groupStackP.count() != 0))
							groupStackP.top().append(ite);
						Elements.append(ite);
					}
					lastPath = "";
					currPath = "";
				}
			}
			else if (token == "co")
				CurrColor = parseColor(params, eps);
			else if (token == "corgb")
				CurrColor = parseColor(params, eps, colorModelRGB);
			else if (token == "ci")
			{
				if (Coords.size() != 0)
				{
					QPainterPath tmpPath = Coords.toQPainterPath(true);
					tmpPath = boundingBoxRect.intersected(tmpPath);
					if ((tmpPath.boundingRect().width() != 0) && (tmpPath.boundingRect().height() != 0))
					{
						clipCoords.fromQPainterPath(tmpPath);
						z = m_Doc->itemAdd(PageItem::Group, PageItem::Rectangle, baseX, baseY, 10, 10, 0, CommonStrings::None, CommonStrings::None);
						ite = m_Doc->Items->at(z);
						ite->PoLine = clipCoords.copy();  //FIXME: try to avoid copy if FPointArray when properly shared
						ite->PoLine.translate(m_Doc->currentPage()->xOffset(), m_Doc->currentPage()->yOffset());
						ite->ClipEdited = true;
						ite->FrameType = 3;
						FPoint wh = getMaxClipF(&ite->PoLine);
						ite->setWidthHeight(wh.x(),wh.y());
						ite->Clip = FlattenPath(ite->PoLine, ite->Segments);
						m_Doc->AdjustItemSize(ite, true);
						ite->ContourLine = ite->PoLine.copy();
						ite->setItemName( tr("Group%1").arg(m_Doc->GroupCounter));
						ite->setTextFlowMode(PageItem::TextFlowDisabled);
						Elements.append(ite);
						if ((groupStack.count() != 0) && (groupStackP.count() != 0))
							groupStackP.top().append(ite);
						groupStack.push(ite);
						QList<PageItem*> gElements;
						groupStackP.push(gElements);
						gsStackMarks.push(gsStack.count());
						m_Doc->GroupCounter++;
					}
				}
				Coords   = FPointArray(0);
				lastPath = "";
				currPath = "";
			}
			else if (token == "gs")
			{
				gsStack.push(1);
			}
			else if (token == "gr")
			{
				// #6834 : self defense against incorrectly balanced save/restore
				if (gsStack.count() > 0)
					gsStack.pop();
				if ((groupStack.count() != 0) && (groupStackP.count() != 0))
				{
					if (gsStack.count() < static_cast<int>(gsStackMarks.top()))
					{
						PageItem *ite = groupStack.pop();
						QList<PageItem*> gList = groupStackP.pop();
						for (int d = 0; d < gList.count(); d++)
						{
							Elements.removeAll(gList.at(d));
						}
						m_Doc->groupObjectsToItem(ite, gList);
						gsStackMarks.pop();
					}
				}
			}
			else if (token == "w")
			{
				ScTextStream Lw(&params, QIODevice::ReadOnly);
				Lw >> LineW;
			}
			else if (token == "ld")