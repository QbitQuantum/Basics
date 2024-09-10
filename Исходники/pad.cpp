QString Pad::makeLayerSvg(ViewLayer::ViewLayerID viewLayerID, double mmW, double mmH, double milsW, double milsH) 
{
	Q_UNUSED(milsW);
	Q_UNUSED(milsH);

	switch (viewLayerID) {
		case ViewLayer::Copper0:
		case ViewLayer::Copper1:
			break;
		default:
			return "";
	}

	double wpx = mmW > 0 ? GraphicsUtils::mm2pixels(mmW) : OriginalWidth;
	double hpx = mmH > 0 ? GraphicsUtils::mm2pixels(mmH) : OriginalHeight;

	QString connectAt = m_modelPart->localProp("connect").toString();
	QRectF terminal;
	double minW = qMin((double) 1.0, wpx / 3);
	double minH = qMin((double) 1.0, hpx / 3);
	if (connectAt.compare("center", Qt::CaseInsensitive) == 0) {
		terminal.setRect(2, 2, wpx, hpx);
	}
	else if (connectAt.compare("north", Qt::CaseInsensitive) == 0) {
		terminal.setRect(2, 2, wpx, minH);
	}
	else if (connectAt.compare("south", Qt::CaseInsensitive) == 0) {
		terminal.setRect(2, 2 + hpx - minH, wpx, minH);
	}
	else if (connectAt.compare("east", Qt::CaseInsensitive) == 0) {
		terminal.setRect(2 + wpx - minW, 2, minW, hpx);
	}
	else if (connectAt.compare("west", Qt::CaseInsensitive) == 0) {
		terminal.setRect(2, 2, minW, hpx);
	}

    QString blockerColor = (viewLayerID == ViewLayer::Copper0) ? "#A26A00" : "#aF8B33";
    QString copperColor = (viewLayerID == ViewLayer::Copper0) ? ViewLayer::Copper0Color : ViewLayer::Copper1Color;
	QString svg = QString("<svg version='1.1' xmlns='http://www.w3.org/2000/svg'  x='0px' y='0px' width='%1px' height='%2px' viewBox='0 0 %1 %2'>\n"
							"<g id='%5'>\n"
							"<rect  id='%8pad' x='2' y='2' fill='%6' fill-opacity='%7' stroke='%9' stroke-width='%10' width='%3' height='%4'/>\n"
							)
					.arg(wpx + TheOffset)
					.arg(hpx + TheOffset)
					.arg(wpx)
					.arg(hpx)
					.arg(ViewLayer::viewLayerXmlNameFromID(viewLayerID))
                    .arg(copperBlocker() ? blockerColor : copperColor)
                    .arg(copperBlocker() ? 0.0 : 1.0)
                    .arg(copperBlocker() ? "zzz" : "connector0")
                    .arg(copperBlocker() ? blockerColor : "none")
                    .arg(copperBlocker() ? TheOffset : 0)
					;

    if (copperBlocker()) {
        svg += QString("<line stroke='%5' stroke-width='1' x1='%1' y1='%2' x2='%3'  y2='%4'/>\n")
                    .arg(0)
                    .arg(0)
                    .arg(wpx + TheOffset)
                    .arg(hpx + TheOffset)
                    .arg(blockerColor)
                   ;
        svg += QString("<line stroke='%5' stroke-width='1' x1='%1' y1='%2' x2='%3'  y2='%4'/>\n")
                    .arg(wpx + TheOffset)
                    .arg(0)
                    .arg(0)
                    .arg(hpx + TheOffset)
                    .arg(blockerColor)
                   ;

    }
    else {
        svg += QString("<rect  id='%12terminal' x='%1' y='%2' fill='none' stroke='none' stroke-width='0' width='%3' height='%4'/>\n")
					.arg(terminal.left())
					.arg(terminal.top())
					.arg(terminal.width())
					.arg(terminal.height())
                    ;

    }

    svg += "</g>\n</svg>";

	//DebugDialog::debug("pad svg: " + svg);
	return svg;
}