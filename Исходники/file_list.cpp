void FileList::onPaint(ui::PaintEvent& ev)
{
  Graphics* g = ev.getGraphics();
  SkinTheme* theme = static_cast<SkinTheme*>(getTheme());
  View* view = View::getView(this);
  gfx::Rect vp = view->getViewportBounds();
  gfx::Rect bounds = getClientBounds();
  int x, y = bounds.y;
  int evenRow = 0;
  gfx::Color bgcolor;
  gfx::Color fgcolor;
  she::Surface* thumbnail = NULL;
  int thumbnail_y = 0;

  g->fillRect(theme->getColor(ThemeColor::Background), bounds);

  // rows
  for (FileItemList::iterator
         it=m_list.begin(), end=m_list.end(); it!=end; ++it) {
    IFileItem* fi = *it;
    gfx::Size itemSize = getFileItemSize(fi);

    if (fi == m_selected) {
      fgcolor = theme->getColor(ThemeColor::FileListSelectedRowText);
      bgcolor = theme->getColor(ThemeColor::FileListSelectedRowFace);
    }
    else {
      bgcolor = evenRow ? theme->getColor(ThemeColor::FileListEvenRowFace):
                          theme->getColor(ThemeColor::FileListOddRowFace);

      if (fi->isFolder() && !fi->isBrowsable())
        fgcolor = theme->getColor(ThemeColor::FileListDisabledRowText);
      else
        fgcolor = evenRow ? theme->getColor(ThemeColor::FileListEvenRowText):
                            theme->getColor(ThemeColor::FileListOddRowText);
    }

    x = bounds.x+2*jguiscale();

    // Item background
    g->fillRect(bgcolor, gfx::Rect(bounds.x, y, bounds.w, itemSize.h));

    if (fi->isFolder()) {
      int icon_w = getFont()->textLength("[+]");

      g->drawUIString("[+]", fgcolor, bgcolor, gfx::Point(x, y+2*jguiscale()));
      x += icon_w+2*jguiscale();
    }

    // item name
    g->drawString(
      fi->getDisplayName().c_str(),
      fgcolor, bgcolor, gfx::Point(x, y+2*jguiscale()));

    // draw progress bars
    double progress;
    ThumbnailGenerator::WorkerStatus workerStatus =
      ThumbnailGenerator::instance()->getWorkerStatus(fi, progress);

    if (workerStatus == ThumbnailGenerator::WorkingOnThumbnail) {
      int barw = 64*jguiscale();

      theme->paintProgressBar(g,
        gfx::Rect(
          bounds.x2()-2*jguiscale()-barw,
          y+itemSize.h/2-3*jguiscale(),
          barw, 6*jguiscale()),
        progress);
    }

    // Thumbnail position
    if (fi == m_selected) {
      thumbnail = fi->getThumbnail();
      if (thumbnail)
        thumbnail_y = y + itemSize.h/2;
    }

    y += itemSize.h;
    evenRow ^= 1;
  }

  // Draw the thumbnail
  if (thumbnail) {
    x = vp.x+vp.w - 2*jguiscale() - thumbnail->width();
    y = thumbnail_y - thumbnail->height()/2 + getBounds().y;
    y = MID(vp.y+2*jguiscale(), y, vp.y+vp.h-3*jguiscale()-thumbnail->height());
    x -= getBounds().x;
    y -= getBounds().y;

    g->blit(thumbnail, 0, 0, x, y, thumbnail->width(), thumbnail->height());
    g->drawRect(gfx::rgba(0, 0, 0),
      gfx::Rect(x-1, y-1, thumbnail->width()+1, thumbnail->height()+1));
  }
}