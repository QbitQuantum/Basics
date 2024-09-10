void LibraryFilterLineEdit::paintEvent(QPaintEvent *)
{
	QStylePainter p(this);
	QStyleOptionFrame o;
	initStyleOption(&o);
	o.palette = QApplication::palette();
	//o.rect.adjust(0, 0, -1, 0);

	p.fillRect(rect(), o.palette.base().color());
	QRect rLeft = QRect(o.rect.x(),
						o.rect.y() + 1,
						o.rect.height(),
						o.rect.y() + o.rect.height() - 2);
	QRect rRight = QRect(o.rect.x() + o.rect.width() - o.rect.height(),
						 o.rect.y() + 1,
						 o.rect.height(),
						 o.rect.y() + o.rect.height() - 2);
	QRect rText = QRect(rLeft.x() + rLeft.width(), rLeft.y(), rRight.x(), rRight.y() + rRight.height());
	//rLeft.adjust(0, 1, 0, -1);
	//rRight.adjust(0, 1, 0, -1);

	if (hasFocus()) {
		p.setPen(QPen(o.palette.highlight().color()));
	} else {
		p.setPen(QPen(o.palette.mid().color()));
	}
	p.save();
	p.setRenderHint(QPainter::Antialiasing, true);

	QPainterPath painterPath;
	// 2---1---->   Left curve is painted with 2 calls to cubicTo, starting in 1   <----10--9
	// |   |        First cubic call is with points p1, p2 and p3                       |   |
	// 3   +        Second is with points p3, p4 and p5                                 +   8
	// |   |        With that, a half circle can be filled with linear gradient         |   |
	// 4---5---->                                                                  <----6---7
	painterPath.moveTo(rLeft.x() + rLeft.width(), rLeft.y());
	painterPath.cubicTo(rLeft.x() + rLeft.width(), rLeft.y(),
						rLeft.x() + rLeft.width() / 2.0f, rLeft.y(),
						rLeft.x() + rLeft.width() / 2.0f, rLeft.y() + rLeft.height() / 2.0f);
	painterPath.cubicTo(rLeft.x() + rLeft.width() / 2.0f, rLeft.y() + rLeft.height() / 2.0f,
						rLeft.x() + rLeft.width() / 2.0f, rLeft.y() + rLeft.height(),
						rLeft.x() + rLeft.width(), rLeft.y() + rLeft.height());

	painterPath.lineTo(rRight.x(), rRight.y() + rRight.height());
	painterPath.cubicTo(rRight.x(), rRight.y() + rRight.height(),
						rRight.x() + rRight.width() / 2.0f, rRight.y() + rRight.height(),
						rRight.x() + rRight.width() / 2.0f, rRight.y() + rRight.height() / 2.0f);
	painterPath.cubicTo(rRight.x() + rRight.width() / 2.0f, rRight.y() + rRight.height() / 2.0f,
						rRight.x() + rRight.width() / 2.0f, rRight.y(),
						rRight.x(), rRight.y());

	painterPath.closeSubpath();
	p.drawPath(painterPath);

	p.setRenderHint(QPainter::Antialiasing, false);
	p.restore();

	// Paint text and cursor
	if (hasFocus() || !text().isEmpty()) {

		// Highlight selected text
		p.setPen(o.palette.text().color());
		if (hasSelectedText()) {

			QRect rectTextLeft, rectTextMid, rectTextRight;
			QString leftText, midText, rightText;

			int sStart = selectionStart();
			int sEnd = selectedText().length() - 1;

			// Four uses cases to highlight a text
			if (sStart > 0 && sEnd < text().size() - 1) {
				// a[b]cd
				leftText = text().left(sStart);
				midText = selectedText();
				rightText = text().mid(sStart + selectedText().length());

				rectTextLeft.setX(rText.x());
				rectTextLeft.setY(rText.y());
				rectTextLeft.setWidth(fontMetrics().width(leftText));
				rectTextLeft.setHeight(rText.height());

				rectTextMid.setX(rectTextLeft.x() + rectTextLeft.width());
				rectTextMid.setY(rText.y());
				rectTextMid.setWidth(fontMetrics().width(midText));
				rectTextMid.setHeight(rText.height());

				rectTextRight.setX(rectTextMid.x() + rectTextMid.width());
				rectTextRight.setY(rText.y());
				rectTextRight.setWidth(fontMetrics().width(rightText));
				rectTextRight.setHeight(rText.height());

				p.fillRect(rectTextLeft, o.palette.base());
				p.fillRect(rectTextMid, o.palette.highlight());
				p.fillRect(rectTextRight, o.palette.base());

				p.drawText(rectTextLeft, Qt::AlignLeft | Qt::AlignVCenter, leftText);
				p.save();
				p.setPen(o.palette.highlightedText().color());
				p.drawText(rectTextMid, Qt::AlignLeft | Qt::AlignVCenter, midText);
				p.restore();
				p.drawText(rectTextRight, Qt::AlignLeft | Qt::AlignVCenter, rightText);
			} else if (sStart == 0 && sEnd < text().size() - 1) {
				// [ab]cd
				midText = selectedText();
				rightText = text().mid(sStart + selectedText().length());

				rectTextMid.setX(rText.x());
				rectTextMid.setY(rText.y());
				rectTextMid.setWidth(fontMetrics().width(midText));
				rectTextMid.setHeight(rText.height());

				rectTextRight.setX(rectTextMid.x() + rectTextMid.width());
				rectTextRight.setY(rText.y());
				rectTextRight.setWidth(fontMetrics().width(rightText));
				rectTextRight.setHeight(rText.height());

				p.fillRect(rectTextMid, o.palette.highlight());
				p.fillRect(rectTextRight, o.palette.base());

				p.save();
				p.setPen(o.palette.highlightedText().color());
				p.drawText(rectTextMid, Qt::AlignLeft | Qt::AlignVCenter, midText);
				p.restore();
				p.drawText(rectTextRight, Qt::AlignLeft | Qt::AlignVCenter, rightText);
			} else if (sStart == 0 && sEnd == text().size() - 1) {
				// [abcd]
				midText = selectedText();

				rectTextMid.setX(rText.x());
				rectTextMid.setY(rText.y());
				rectTextMid.setWidth(fontMetrics().width(midText));
				rectTextMid.setHeight(rText.height());

				p.fillRect(rectTextMid, o.palette.highlight());

				p.save();
				p.setPen(o.palette.highlightedText().color());
				p.drawText(rectTextMid, Qt::AlignLeft | Qt::AlignVCenter, midText);
				p.restore();
			} else {
				// ab[cd]
				// never?
			}
		} else {
			p.drawText(rText, Qt::AlignLeft | Qt::AlignVCenter, text());
		}
		rText.adjust(0, 2, 0, -2);
		this->drawCursor(&p, rText);
	} else {
		p.setPen(o.palette.mid().color());
		p.drawText(rText, Qt::AlignLeft | Qt::AlignVCenter, placeholderText());
	}
}