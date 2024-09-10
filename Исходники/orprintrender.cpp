void ORPrintRender::renderPage(ORODocument * pDocument, int pageNb, QPainter *painter, qreal xDpi, qreal yDpi, QSize margins, int printResolution)
{
  OROPage * p = pDocument->page(pageNb);

  if(((!p->backgroundImage().isNull()) && (p->backgroundOpacity() != 0)) ||
     ((!p->watermarkText().isEmpty()) && (p->watermarkOpacity() != 0)))
  {
    // Do some simple processing used by both Background and Watermark
    const int resolution = 100;
    bool doBgWm = false;
    int printMarginWidth = margins.width();
    int printMarginHeight = margins.height();

    QString pageSize = pDocument->pageOptions().getPageSize();
    int pageWidth = 0;
    int pageHeight = 0;
    if(pageSize == "Custom") {
      // if this is custom sized sheet of paper we will just use those values
      pageWidth = (int)(pDocument->pageOptions().getCustomWidth() * resolution);
      pageHeight = (int)(pDocument->pageOptions().getCustomHeight() * resolution);
    } else {
      // lookup the correct size information for the specified size paper
      PageSizeInfo pi = PageSizeInfo::getByName(pageSize);
      if(!pi.isNull())
      {
        pageWidth = (int)((pi.width() / 100.0) * resolution);
        pageHeight = (int)((pi.height() / 100.0) * resolution);
      }
    }
    if(!pDocument->pageOptions().isPortrait()) {
      int tmp = pageWidth;
      pageWidth = pageHeight;
      pageHeight = tmp;
    }
    if(pageWidth < 1 || pageHeight < 1) {
      // whoops we couldn't find it.... we will use the values from the painter
      // and add in the margins of the printer to get what should be the correct
      // size of the sheet of paper we are printing to.
      pageWidth = (int)(((painter->viewport().width() + printMarginWidth + printMarginWidth) / xDpi) * resolution);
      pageHeight = (int)(((painter->viewport().height() + printMarginHeight + printMarginHeight) / yDpi) * resolution);
    }

    QImage image = QImage(pageWidth, pageHeight, QImage::Format_RGB32);
    QPainter gPainter;
    if(gPainter.begin(&image))
      gPainter.fillRect(gPainter.viewport(), QColor(Qt::white));

    // Render Background
    if((!p->backgroundImage().isNull()) && (p->backgroundOpacity() != 0))
    {
      doBgWm = true;
      QPointF ps = p->backgroundPosition();
      QSizeF sz = p->backgroundSize();
      QRectF rc = QRectF(ps.x() * resolution, ps.y() * resolution, sz.width() * resolution, sz.height() * resolution);
      renderBackground(image, p->backgroundImage(), rc.toRect(),
        p->backgroundScale(), p->backgroundScaleMode(),
        p->backgroundAlign(), p->backgroundOpacity());
    }

    // Render Watermark
    if((!p->watermarkText().isEmpty()) && (p->watermarkOpacity() != 0))
    {
      doBgWm = true;
      renderWatermark(image, p->watermarkText(), p->watermarkFont(), p->watermarkOpacity(),
        ((pDocument->pageOptions().getMarginLeft() + pDocument->pageOptions().getMarginRight()) * resolution),
        ((pDocument->pageOptions().getMarginTop() + pDocument->pageOptions().getMarginBottom()) * resolution),
        pDocument->pageOptions().getMarginLeft() * resolution, pDocument->pageOptions().getMarginTop() * resolution);
    }

    if(doBgWm)
    {
      QRectF target(-printMarginWidth, -printMarginHeight, (painter->viewport().width() + printMarginWidth + printMarginWidth), (painter->viewport().height() + printMarginHeight + printMarginHeight));
      QRectF source(0, 0, image.width(), image.height());
      painter->drawImage(target, image, source);
    }
  }

  // Render Page Objects
  for(int i = 0; i < p->primitives(); i++)
  {
    OROPrimitive * prim = p->primitive(i);
    if(prim->type() == OROTextBox::TextBox)
    {
      OROTextBox * tb = (OROTextBox*)prim;
      QPointF ps = tb->position();
      QSizeF sz = tb->size();
      QRectF rc = QRectF(ps.x() * xDpi, ps.y() * yDpi, sz.width() * xDpi, sz.height() * yDpi);

      painter->save();
      painter->setFont(tb->font());
      painter->drawText(rc, tb->flags(), tb->text());
      painter->restore();
    }
    else if(prim->type() == OROLine::Line)
    {
      OROLine * ln = (OROLine*)prim;
      QPointF s = ln->startPoint();
      QPointF e = ln->endPoint();
      QPen pen(painter->pen());
      pen.setWidthF((ln->weight() / 100) * printResolution);

      painter->save();
      painter->setPen(pen);
      painter->drawLine(QLineF(s.x() * xDpi, s.y() * yDpi, e.x() * xDpi, e.y() * yDpi));
      painter->restore();
    }
    else if(prim->type() == OROImage::Image)
    {
      OROImage * im = (OROImage*)prim;
      QPointF ps = im->position();
      QSizeF sz = im->size();
      QRectF rc = QRectF(ps.x() * xDpi, ps.y() * yDpi, sz.width() * xDpi, sz.height() * yDpi);

      QImage img = im->image();
      if(im->scaled())
        img = img.scaled(rc.size().toSize(), (Qt::AspectRatioMode)im->aspectRatioMode(), (Qt::TransformationMode)im->transformationMode());

      QRectF sr = QRectF(QPointF(0.0, 0.0), rc.size().boundedTo(img.size()));
      painter->drawImage(rc.topLeft(), img, sr);
    }
    else if(prim->type() == ORORect::Rect)
    {
      ORORect * re = (ORORect*)prim;

      QPointF ps = re->position();
      QSizeF sz = re->size();
      QRectF rc = QRectF(ps.x() * xDpi, ps.y() * yDpi, sz.width() * xDpi, sz.height() * yDpi);
      QPen pen(re->pen());
      pen.setWidthF((re->weight() / 100) * printResolution);

      painter->save();
      painter->setPen(pen);
      painter->setBrush(re->brush());
      painter->drawRect(rc);
      painter->restore();
    }
    else
    {
      qDebug("unrecognized primitive type");
    }
  }
}