void renderCodeUPCE(OROPage * page, const QRectF & r, const QString & _str, int align)
{
  int val[8];
  int i = 0;

  // initialize all the values just so we can be predictable
  for(i = 0; i < 8; i++)
    val[i] = -1;

  // verify that the passed in string is valid
  // if it's not either twelve or thirteen characters
  // then it must be invalid to begin with
  if(_str.length() != 8)
    return;
  // loop through and convert each char to a digit.
  // if we can't convert all characters then this is
  // an invalid number
  for(i = 0; i < _str.length(); i++)
  {
    val[i] = ((QChar)_str.at(i)).digitValue();
    if(val[i] == -1)
      return;
  }

  // calculate and append the checksum value
  // because everything is so messed up we don't calculate
  // the checksum and require that it be passed in already
  // however we do have to verify that the first digit is
  // either 0 or 1 as that is our parity
  if(val[0] != 0 && val[0] != 1)
    return;

  // lets determine some core attributes about this barcode
  qreal bar_width = 0.01; // the width of the base unit bar

  // this is are mandatory minimum quiet zone
  qreal quiet_zone = bar_width * 0.10;
  if(quiet_zone < 0.10)
    quiet_zone = 0.10;

  // what kind of area do we have to work with
  qreal draw_width = r.width();
  qreal draw_height = r.height() - 0.02;

  // L = 51X
  // L length of barcode (excluding quite zone) in units same as X and I
  // X the width of a bar (pixels in our case)
  qreal L;

  qreal X = bar_width;

  L = (51.0 * X);

  // now we have the actual width the barcode will be so can determine the actual
  // size of the quiet zone (we assume we center the barcode in the given area
  // what should we do if the area is too small????
  // At the moment the way the code is written is we will always start at the minimum
  // required quiet zone if we don't have enough space.... I guess we'll just have over-run
  // to the right
  //
  // calculate the starting position based on the alignment option
  // for left align we don't need to do anything as the values are already setup for it
  if(align == 1) // center
  {
    qreal nqz = (draw_width - L) / 2;
    if(nqz > quiet_zone)
      quiet_zone = nqz;
  }
  else if(align > 1) // right
    quiet_zone = draw_width - (L + quiet_zone);
  // else if(align < 1) {} // left : do nothing

  qreal pos = r.left() + quiet_zone;
  qreal top = r.top();

  QPen pen(Qt::NoPen);
  QBrush brush(QColor("black"));

  int b = 0;
  int w = 0;

  // render open guard
  ORORect * rect = new ORORect();
  rect->setPen(pen);
  rect->setBrush(brush);
  rect->setRect(QRectF(pos,top, bar_width,draw_height));
  page->addPrimitive(rect);

  pos += (bar_width * 2.0);

  rect = new ORORect();
  rect->setPen(pen);
  rect->setBrush(brush);
  rect->setRect(QRectF(pos,top, bar_width,draw_height));
  page->addPrimitive(rect);

  pos += bar_width;

  // render first set
  for(i = 0; i < 6; i++)
  {
    b = val[i+1];
    for(w = 0; w < 7; w++)
    {
      if(_encodings[b][_upcparenc[val[7]][val[0]][i]][w])
      {
	rect = new ORORect();
	rect->setPen(pen);
	rect->setBrush(brush);
	rect->setRect(QRectF(pos,top, bar_width,draw_height - 0.07));
	page->addPrimitive(rect);
      }
      pos += bar_width;
    }
  }

  // render center guard
  pos += bar_width;

  rect = new ORORect();
  rect->setPen(pen);
  rect->setBrush(brush);
  rect->setRect(QRectF(pos,top, bar_width,draw_height));
  page->addPrimitive(rect);

  pos += (bar_width * 2.0);

  rect = new ORORect();
  rect->setPen(pen);
  rect->setBrush(brush);
  rect->setRect(QRectF(pos,top, bar_width,draw_height));
  page->addPrimitive(rect);

  pos += (bar_width * 2.0);

  // render close guard

  rect = new ORORect();
  rect->setPen(pen);
  rect->setBrush(brush);
  rect->setRect(QRectF(pos,top, bar_width,draw_height));
  page->addPrimitive(rect);

  QString parstr = QString("%1").arg(val[0]);
  QString chkstr = QString("%1").arg(val[7]);
  QString leftstr = QString().sprintf("%d%d%d%d%d%d",
		     val[1], val[2], val[3], val[4], val[5], val[6]);
  QFont font("Arial",6);

  OROTextBox * tb = new OROTextBox();
  tb->setPosition(QPointF(r.left(), r.top() + draw_height - 0.12));
  tb->setSize(QSizeF(quiet_zone - 0.02, 0.12));
  tb->setFont(font);
  tb->setText(parstr);
  tb->setFlags(Qt::AlignRight | Qt::AlignTop);
  page->addPrimitive(tb);

  tb = new OROTextBox();
  tb->setPosition(QPointF(r.left() + quiet_zone + 0.03, (r.top() + draw_height) - 0.07));
  tb->setSize(QSizeF(0.42, 0.10));
  tb->setFont(font);
  tb->setText(leftstr);
  tb->setFlags(Qt::AlignHCenter | Qt::AlignTop);
  page->addPrimitive(tb);

  tb = new OROTextBox();
  tb->setPosition(QPointF(r.left() + quiet_zone + L + 0.02, r.top() + draw_height - 0.12));
  tb->setSize(QSizeF(0.08, 0.12));
  tb->setFont(font);
  tb->setText(chkstr);
  tb->setFlags(Qt::AlignLeft | Qt::AlignTop);
  page->addPrimitive(tb);

  return;
} 