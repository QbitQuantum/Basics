void UI_Mainwindow::save_screenshot()
{
  int n;

  char str[128],
       opath[MAX_PATHLEN];

  QPainter painter;
#if QT_VERSION >= 0x050000
  painter.setRenderHint(QPainter::Qt4CompatiblePainting, true);
#endif

  QPainterPath path;

  if(device == NULL)
  {
    return;
  }

  scrn_timer->stop();

  scrn_thread->wait();

  tmc_write(":DISP:DATA?");

  QApplication::setOverrideCursor(Qt::WaitCursor);

  qApp->processEvents();

  n = tmc_read();

  QApplication::restoreOverrideCursor();

  if(n < 0)
  {
    strcpy(str, "Can not read from device.");
    goto OUT_ERROR;
  }

  if(device->sz != SCRN_SHOT_BMP_SZ)
  {
    strcpy(str, "Error, bitmap has wrong filesize\n");
    goto OUT_ERROR;
  }

  if(strncmp(device->buf, "BM", 2))
  {
    strcpy(str, "Error, file is not a bitmap\n");
    goto OUT_ERROR;
  }

  memcpy(devparms.screenshot_buf, device->buf, SCRN_SHOT_BMP_SZ);

  screenXpm.loadFromData((uchar *)(devparms.screenshot_buf), SCRN_SHOT_BMP_SZ);

  if(devparms.modelserie == 1)
  {
    painter.begin(&screenXpm);

    painter.fillRect(0, 0, 80, 29, Qt::black);

    painter.setPen(Qt::white);

    painter.drawText(5, 8, 65, 20, Qt::AlignCenter, devparms.modelname);

    painter.end();
  }
  else if(devparms.modelserie == 6)
    {
      painter.begin(&screenXpm);

      painter.fillRect(0, 0, 95, 29, QColor(48, 48, 48));

      path.addRoundedRect(5, 5, 85, 20, 3, 3);

      painter.fillPath(path, Qt::black);

      painter.setPen(Qt::white);

      painter.drawText(5, 5, 85, 20, Qt::AlignCenter, devparms.modelname);

      painter.end();
    }

  if(devparms.screenshot_inv)
  {
    screenXpm.invertPixels(QImage::InvertRgb);
  }

  opath[0] = 0;
  if(recent_savedir[0]!=0)
  {
    strcpy(opath, recent_savedir);
    strcat(opath, "/");
  }
  strcat(opath, "screenshot.png");

  strcpy(opath, QFileDialog::getSaveFileName(this, "Save file", opath, "PNG files (*.png *.PNG)").toLocal8Bit().data());

  if(!strcmp(opath, ""))
  {
    scrn_timer->start(devparms.screentimerival);

    return;
  }

  get_directory_from_path(recent_savedir, opath, MAX_PATHLEN);

  if(screenXpm.save(QString::fromLocal8Bit(opath), "PNG", 50) == false)
  {
    strcpy(str, "Could not save file (unknown error)");
    goto OUT_ERROR;
  }

  scrn_timer->start(devparms.screentimerival);

  return;

OUT_ERROR:

  scrn_timer->start(devparms.screentimerival);

  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Critical);
  msgBox.setText(str);
  msgBox.exec();
}