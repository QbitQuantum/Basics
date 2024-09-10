int KstGuiData::vectorsToFile(const KstVectorList& vl, QFile *f, bool interpolate) {
  KstApp *app = KstApp::inst();
  int maxlen = -1;

  if (interpolate) { // code duplication is faster
    maxlen = 0;
    for (KstVectorList::ConstIterator v = vl.begin(); v != vl.end(); ++v) {
      (*v)->readLock();
      maxlen = KMAX(maxlen, (*v)->length());
    }
  } else {
    for (KstVectorList::ConstIterator v = vl.begin(); v != vl.end(); ++v) {
      (*v)->readLock();
      if (maxlen == -1) {
        maxlen = (*v)->length();
      } else {
        maxlen = KMIN(maxlen, (*v)->length());
      }
    }
  }

  QString saving = i18n("Saving vectors...");
  register int modval = kMax(maxlen/100, 100);
  app->slotUpdateProgress(maxlen, 0, QString::null);

  bool first = true;
  QString ltxt = ";";
  for (KstVectorList::ConstIterator v = vl.begin(); v != vl.end(); ++v) {
    ltxt += ' ';
    ltxt += (*v)->tagName();
  }
  ltxt += '\n';

  f->writeBlock(ltxt.ascii(), ltxt.length());
  ltxt.fill('-');
  ltxt[0] = ';';
  ltxt[1] = ' ';
  ltxt[ltxt.length() - 1] = '\n';
  f->writeBlock(ltxt.ascii(), ltxt.length());
#if QT_VERSION >= 0x030200
  ltxt.reserve(vl.count()*17);
#endif
  for (int line = 0; line < maxlen; ++line) {
    ltxt.truncate(0);
    first = true;
    for (KstVectorList::ConstIterator v = vl.begin(); v != vl.end(); ++v) {
      if (!first) {
        ltxt += ' ';
      } else {
        first = false;
      }
      double val;
      if (interpolate) {  // might be faster to put this outside the for loops
        val = (*v)->interpolate(line, maxlen);
      } else {
        val = (*v)->value()[line];
      } 
      ltxt += QString::number(val, 'g', 15);
    }
    ltxt += "\n";
    f->writeBlock(ltxt.ascii(), ltxt.length());
    if (line % modval == 0) {
      app->slotUpdateProgress(maxlen, line, saving);
    }
  }

  for (KstVectorList::ConstIterator v = vl.begin(); v != vl.end(); ++v) {
    (*v)->unlock();
  }

  app->slotUpdateProgress(0, 0, QString::null);

  return 0;
}