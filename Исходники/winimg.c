void
win_emoji_show(int x, int y, wchar * efn, int elen, ushort lattr)
{
  GpStatus s;

  static GdiplusStartupInput gi = (GdiplusStartupInput){1, NULL, FALSE, FALSE};
  static ULONG_PTR gis = 0;
  if (!gis) {
    s = GdiplusStartup(&gis, &gi, NULL);
    gpcheck("startup", s);
  }

  bool use_stream = true;
  IStream * fs = 0;
  if (use_stream) {
    s = GdipCreateStreamOnFile(efn, 0 /* FileMode.Open */, &fs);
    gpcheck("stream", s);
  }
  else
    s = NotImplemented;

  GpImage * img = 0;
  if (s == Ok) {
    s = GdipLoadImageFromStream(fs, &img);
    gpcheck("load stream", s);
  }
  else {
    // This is reported to generate a memory leak, so rather use the stream.
    s = GdipLoadImageFromFile(efn, &img);
    gpcheck("load file", s);
  }

  int col = PADDING + x * cell_width;
  int row = PADDING + y * cell_height;
  if ((lattr & LATTR_MODE) >= LATTR_BOT)
    row -= cell_height;
  int w = elen * cell_width;
  if ((lattr & LATTR_MODE) != LATTR_NORM)
    w *= 2;
  int h = cell_height;
  if ((lattr & LATTR_MODE) >= LATTR_TOP)
    h *= 2;

  if (cfg.emoji_placement) {
    uint iw, ih;
    s = GdipGetImageWidth(img, &iw);
    gpcheck("width", s);
    s = GdipGetImageHeight(img, &ih);
    gpcheck("height", s);
    // consider aspect ratio so that ih/iw == h/w;
    // if EMPL_FULL, always adjust w
    // if ih/iw > h/w, make w smaller
    // if iw/ih > w/h, make h smaller
    if (cfg.emoji_placement == EMPL_FULL && ih * w != h * iw) {
      w = h * iw / ih;
    }
    else if (ih * w > h * iw) {
      int w0 = w;
      w = h * iw / ih;
      if (cfg.emoji_placement == EMPL_MIDDLE) {
        // horizontally center
        col += (w0 - w) / 2;
      }
    }
    else if (iw * h > w * ih) {
      int h0 = h;
      h = w * ih / iw;
      // vertically center
      row += (h0 - h) / 2;
    }
  }

  GpGraphics * gr;
  s = GdipCreateFromHDC(GetDC(wnd), &gr);
  gpcheck("hdc", s);
  s = GdipDrawImageRectI(gr, img, col, row, w, h);
  gpcheck("draw", s);
  s = GdipFlush(gr, FlushIntentionFlush);
  gpcheck("flush", s);

  s = GdipDeleteGraphics(gr);
  gpcheck("delete gr", s);
  s = GdipDisposeImage(img);
  gpcheck("dispose img", s);
  if (fs) {
    // Release stream resources, close file.
    fs->lpVtbl->Release(fs);
  }
}