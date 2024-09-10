static
void drawDial ( const QStyleOptionSlider *option, QPainter *painter )
{
	QPalette pal = option->palette;
	QColor buttonColor = pal.button().color();
	const int width = option->rect.width();
	const int height = option->rect.height();
	const bool enabled = option->state & QStyle::State_Enabled;
	qreal r = qMin(width, height) / 2;
	r -= r/50;
	const qreal penSize = r/20.0;

	painter->save();
	painter->setRenderHint(QPainter::Antialiasing);

	// Draw notches
	if (option->subControls & QStyle::SC_DialTickmarks) {
		painter->setPen(option->palette.dark().color().darker(120));
		painter->drawLines(calcLines(option));
	}

	// Cache dial background
	QString a = QString::fromLatin1("qdial");
	QRect rect = option->rect;
	QPixmap internalPixmapCache;
	QImage imageCache;
	QPainter *p = painter;
	QString unique = uniqueName((a), option, option->rect.size());
	int txType = painter->deviceTransform().type() | painter->worldTransform().type();
	bool doPixmapCache = txType <= QTransform::TxTranslate;
	if (doPixmapCache && QPixmapCache::find(unique, internalPixmapCache)) {
		painter->drawPixmap(option->rect.topLeft(), internalPixmapCache);
	} else {
		if (doPixmapCache) {
			rect.setRect(0, 0, option->rect.width(), option->rect.height());
			imageCache = QImage(option->rect.size(), QImage::Format_ARGB32_Premultiplied);
			imageCache.fill(0);
			p = new QPainter(&imageCache);
		}
	//--BEGIN_STYLE_PIXMAPCACHE(QString::fromLatin1("qdial"));

		p->setRenderHint(QPainter::Antialiasing);

		const qreal d_ = r / 6;
		const qreal dx = option->rect.x() + d_ + (width - 2 * r) / 2 + 1;
		const qreal dy = option->rect.y() + d_ + (height - 2 * r) / 2 + 1;

		QRectF br = QRectF(dx + 0.5, dy + 0.5,
						   int(r * 2 - 2 * d_ - 2),
						   int(r * 2 - 2 * d_ - 2));
		buttonColor.setHsv(buttonColor .hue(),
						   qMin(140, buttonColor .saturation()),
						   qMax(180, buttonColor.value()));
		QColor shadowColor(0, 0, 0, 20);

		if (enabled) {
			// Drop shadow
			qreal shadowSize = qMax(1.0, penSize/2.0);
			QRectF shadowRect= br.adjusted(-2*shadowSize, -2*shadowSize,
										   2*shadowSize, 2*shadowSize);
			QRadialGradient shadowGradient(shadowRect.center().x(),
										   shadowRect.center().y(), shadowRect.width()/2.0,
										   shadowRect.center().x(), shadowRect.center().y());
			shadowGradient.setColorAt(qreal(0.91), QColor(0, 0, 0, 40));
			shadowGradient.setColorAt(qreal(1.0), Qt::transparent);
			p->setBrush(shadowGradient);
			p->setPen(Qt::NoPen);
			p->translate(shadowSize, shadowSize);
			p->drawEllipse(shadowRect);
			p->translate(-shadowSize, -shadowSize);

			// Main gradient
			QRadialGradient gradient(br.center().x() - br.width()/3, dy,
									 br.width()*1.3, br.center().x(),
									 br.center().y() - br.height()/2);
			gradient.setColorAt(0, buttonColor.lighter(110));
			gradient.setColorAt(qreal(0.5), buttonColor);
			gradient.setColorAt(qreal(0.501), buttonColor.darker(102));
			gradient.setColorAt(1, buttonColor.darker(115));
			p->setBrush(gradient);
		} else {
			p->setBrush(Qt::NoBrush);
		}

		p->setPen(QPen(buttonColor.darker(280)));
		p->drawEllipse(br);
		p->setBrush(Qt::NoBrush);
		p->setPen(buttonColor.lighter(110));
		p->drawEllipse(br.adjusted(1, 1, -1, -1));

		if (option->state & QStyle::State_HasFocus) {
			QColor highlight = pal.highlight().color();
			highlight.setHsv(highlight.hue(),
							 qMin(160, highlight.saturation()),
							 qMax(230, highlight.value()));
			highlight.setAlpha(127);
			p->setPen(QPen(highlight, 2.0));
			p->setBrush(Qt::NoBrush);
			p->drawEllipse(br.adjusted(-1, -1, 1, 1));
		}
	//--END_STYLE_PIXMAPCACHE
		if (doPixmapCache) {
			p->end();
			delete p;
			internalPixmapCache = QPixmap::fromImage(imageCache);
			painter->drawPixmap(option->rect.topLeft(), internalPixmapCache);
			QPixmapCache::insert(unique, internalPixmapCache);
		}
	}


	QPointF dp = calcRadialPos(option, qreal(0.70));
	buttonColor = buttonColor.lighter(104);
	buttonColor.setAlphaF(qreal(0.8));
	const qreal ds = r/qreal(7.0);
	QRectF dialRect(dp.x() - ds, dp.y() - ds, 2*ds, 2*ds);
	QRadialGradient dialGradient(dialRect.center().x() + dialRect.width()/2,
								 dialRect.center().y() + dialRect.width(),
								 dialRect.width()*2,
								 dialRect.center().x(), dialRect.center().y());
	dialGradient.setColorAt(1, buttonColor.darker(140));
	dialGradient.setColorAt(qreal(0.4), buttonColor.darker(120));
	dialGradient.setColorAt(0, buttonColor.darker(110));
	if (penSize > 3.0) {
		painter->setPen(QPen(QColor(0, 0, 0, 25), penSize));
		painter->drawLine(calcRadialPos(option, qreal(0.90)), calcRadialPos(option, qreal(0.96)));
	}

	painter->setBrush(dialGradient);
	painter->setPen(QColor(255, 255, 255, 150));
	painter->drawEllipse(dialRect.adjusted(-1, -1, 1, 1));
	painter->setPen(QColor(0, 0, 0, 80));
	painter->drawEllipse(dialRect);
	painter->restore();
}