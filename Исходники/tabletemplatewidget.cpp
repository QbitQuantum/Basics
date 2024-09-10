/*
 * Зберігаємо шаблон кросворду після редагування решітки
 */
void tableTemplateWidget::saveToDB()
{
  int previewSizeCell = 20, val;
  int W = numCol*previewSizeCell;
  int H = numRow*previewSizeCell;

  QPainter *pngPainter = new QPainter();
  QImage *image = new QImage(QSize(W, H), QImage::Format_ARGB32_Premultiplied);

  float t, l;
  QRectF src(0, 0, W, H);
  QRectF r;

  QTableWidgetItem *cell;
  QSqlQuery query;

  query.prepare("DELETE FROM crossword.grids WHERE _template = ?;");
  query.addBindValue(QVariant(templateId));
  query.exec();

  QSqlError le = query.lastError();
  if (le.type() != QSqlError::NoError)
    qDebug() << "saveToDB: " << le.text();

  query.prepare("INSERT INTO crossword.grids (_template, _row, _column, _value) "
                "VALUES (?, ?, ?, ?)");

  pb = new QProgressBar(this);
  pb->setRange(0, numRow*numCol);
  sb->addWidget(pb);

  QVariantList tmp, row, col, value;
  QString text;

  pngPainter->begin(image);
    int i, j, nw;
    for (i = 0; i < numRow; i++)
      {
        t = src.top() + i * previewSizeCell;
        for (j = 0; j < numCol; j++)
          {
            l = src.left() + j * previewSizeCell;

            r.setTop(t);
            r.setLeft(l);

            r.setRight(src.left() + l + previewSizeCell);
            r.setBottom(src.top() + t + previewSizeCell);

            cell = this->item(i, j);
            val = cell->data(Qt::UserRole).toInt();

            if (val)
              pngPainter->fillRect(r, fullCell);
            else
              pngPainter->fillRect(r, emptyCell);

            // прямокутник для ячейки
            pngPainter->drawRect(r);

            // виводимо номер слова
            nw = findWordByRC(i, j) + 1;
            if ( nw >= 1 )
              {
                text = QVariant(nw).toString();
                pngPainter->drawText(r, Qt::AlignLeft | Qt::AlignTop, text);
              }

            tmp << templateId;
            row << i;
            col << j;
            value << val;
          }

        pb->setValue(i*numRow + j*numCol);
      }
  pngPainter->end();

  query.addBindValue(tmp);
  query.addBindValue(row);
  query.addBindValue(col);
  query.addBindValue(value);

  QSqlDriver *drv = db->driver();
  drv->beginTransaction();
    query.execBatch(QSqlQuery::ValuesAsRows);
  drv->commitTransaction();

  le = query.lastError();
  if (le.type() != QSqlError::NoError)
    qDebug() << "saveToDB: " << le.text();

  QByteArray ba;
  QBuffer blob(&ba);
  blob.open(QIODevice::ReadWrite | QIODevice::Unbuffered);
    image->save(&blob, "PNG");
  blob.close();

  /*
   * ====== Run before update DB ======
   */
  scanTemplate();
  savePrivateData();

  query.prepare("UPDATE crossword.templates SET _rows = ?, _columns = ?, "
                "_preview = ?, _count_words = ? WHERE _id = ?;");
    query.addBindValue(QVariant(numRow));
    query.addBindValue(QVariant(numCol));
    query.addBindValue(QVariant(blob.data()));
    query.addBindValue(QVariant(wi.count()));
    query.addBindValue(QVariant(templateId));
  query.exec();

  le = query.lastError();
  if (le.type() != QSqlError::NoError)
    qDebug() << "saveToDB: " << le.text();

  delete image;
  delete pngPainter;

  sb->removeWidget(pb);
  sb->showMessage(tr("Template saved"), 2000);

  isDirty = false;

  // need for templateListWidget
  emit savedToDB(templateId);
}