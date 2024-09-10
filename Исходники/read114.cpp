Score::FileError Score::read114(XmlReader& e)
      {
      if (parentScore())
            setMscVersion(parentScore()->mscVersion());

      for (unsigned int i = 0; i < sizeof(style114)/sizeof(*style114); ++i)
            style()->set(style114[i].idx, style114[i].val);

      // old text style defaults
      TextStyle ts = style()->textStyle("Chord Symbol");
      ts.setYoff(-4.0);
      style()->setTextStyle(ts);
      TempoMap tm;
      while (e.readNextStartElement()) {
            e.setTrack(-1);
            const QStringRef& tag(e.name());
            if (tag == "Staff")
                  readStaff(e);
            else if (tag == "KeySig") {               // not supported
                  KeySig* ks = new KeySig(this);
                  ks->read(e);
                  // customKeysigs.append(ks);
                  delete ks;
                  }
            else if (tag == "siglist")
                  _sigmap->read(e, _fileDivision);
            else if (tag == "programVersion") {
                  _mscoreVersion = e.readElementText();
                  parseVersion(_mscoreVersion);
                  }
            else if (tag == "programRevision")
                  _mscoreRevision = e.readInt();
            else if (tag == "Mag"
               || tag == "MagIdx"
               || tag == "xoff"
               || tag == "Symbols"
               || tag == "cursorTrack"
               || tag == "yoff")
                  e.skipCurrentElement();       // obsolete
            else if (tag == "tempolist") {
                  // store the tempo list to create invisible tempo text later
                  qreal tempo = e.attribute("fix","2.0").toDouble();
                  tm.setRelTempo(tempo);
                  while (e.readNextStartElement()) {
                        if (e.name() == "tempo") {
                              int tick = e.attribute("tick").toInt();
                              double tmp = e.readElementText().toDouble();
                              tick = (tick * MScore::division + _fileDivision/2) / _fileDivision;
                              auto pos = tm.find(tick);
                              if (pos != tm.end())
                                    tm.erase(pos);
                              tm.setTempo(tick, tmp);
                        }
                        else if (e.name() == "relTempo")
                              e.readElementText();
                        else
                              e.unknown();
                  }
            }
            else if (tag == "playMode")
                  _playMode = PlayMode(e.readInt());
            else if (tag == "SyntiSettings")
                  _synthesizerState.read(e);
            else if (tag == "Spatium")
                  _style.setSpatium (e.readDouble() * MScore::DPMM);
            else if (tag == "Division")
                  _fileDivision = e.readInt();
            else if (tag == "showInvisible")
                  _showInvisible = e.readInt();
            else if (tag == "showFrames")
                  _showFrames = e.readInt();
            else if (tag == "showMargins")
                  _showPageborders = e.readInt();
            else if (tag == "Style") {
                  qreal sp = _style.spatium();
                  _style.load(e);
                  // adjust this now so chords render properly on read
                  // other style adjustments can wait until reading is finished
                  if (style(StyleIdx::useGermanNoteNames).toBool())
                        style()->set(StyleIdx::useStandardNoteNames, false);
                  if (_layoutMode == LayoutMode::FLOAT) {
                        // style should not change spatium in
                        // float mode
                        _style.setSpatium(sp);
                        }
                  }
            else if (tag == "TextStyle") {
                  TextStyle s;
                  s.read(e);

                  qreal spMM = _style.spatium() / MScore::DPMM;
                  if (s.frameWidthMM() != 0.0)
                        s.setFrameWidth(Spatium(s.frameWidthMM() / spMM));
                  if (s.paddingWidthMM() != 0.0)
                        s.setPaddingWidth(Spatium(s.paddingWidthMM() / spMM));
\
                  // convert 1.2 text styles
                  s.setName(convertOldTextStyleNames(s.name()));

                  if (s.name() == "Lyrics Odd Lines" || s.name() == "Lyrics Even Lines")
                        s.setAlign((s.align() & ~ Align(AlignmentFlags::VMASK)) | AlignmentFlags::BASELINE);

                  _style.setTextStyle(s);
                  }
            else if (tag == "page-layout") {
                  if (_layoutMode != LayoutMode::FLOAT && _layoutMode != LayoutMode::SYSTEM) {
                        PageFormat pf;
                        pf.copy(*pageFormat());
                        pf.read(e, this);
                        setPageFormat(pf);
                        }
                  else
                        e.skipCurrentElement();
                  }
            else if (tag == "copyright" || tag == "rights") {
                  Text* text = new Text(this);
                  text->read(e);
                  text->layout();
                  setMetaTag("copyright", text->plainText());
                  delete text;
                  }
            else if (tag == "movement-number")
                  setMetaTag("movementNumber", e.readElementText());
            else if (tag == "movement-title")
                  setMetaTag("movementTitle", e.readElementText());
            else if (tag == "work-number")
                  setMetaTag("workNumber", e.readElementText());
            else if (tag == "work-title")
                  setMetaTag("workTitle", e.readElementText());
            else if (tag == "source")
                  setMetaTag("source", e.readElementText());
            else if (tag == "metaTag") {
                  QString name = e.attribute("name");
                  setMetaTag(name, e.readElementText());
                  }
            else if (tag == "Part") {
                  Part* part = new Part(this);
                  part->read114(e);
                  _parts.push_back(part);
                  }
            else if (tag == "Slur") {
                  Slur* slur = new Slur(this);
                  slur->read(e);
                  addSpanner(slur);
                  }
            else if ((tag == "HairPin")
                || (tag == "Ottava")
                || (tag == "TextLine")
                || (tag == "Volta")
                || (tag == "Trill")
                || (tag == "Pedal")) {
                  Spanner* s = static_cast<Spanner*>(Element::name2Element(tag, this));
                  s->read(e);
                  if (s->track() == -1)
                        s->setTrack(e.track());
                  else
                        e.setTrack(s->track());       // update current track
                  if (s->tick() == -1)
                        s->setTick(e.tick());
                  else
                        e.initTick(s->tick());      // update current tick
                  if (s->track2() == -1)
                        s->setTrack2(s->track());
                  if (s->ticks() == 0) {
                        delete s;
                        qDebug("zero spanner %s ticks: %d", s->name(), s->ticks());
                        }
                  else {
                        addSpanner(s);
                        }
                  }
            else if (tag == "Excerpt") {
                  if (MScore::noExcerpts)
                        e.skipCurrentElement();
                  else {
                        Excerpt* ex = new Excerpt(this);
                        ex->read(e);
                        _excerpts.append(ex);
                        }
                  }
            else if (tag == "Beam") {
                  Beam* beam = new Beam(this);
                  beam->read(e);
                  beam->setParent(0);
                  // _beams.append(beam);
                  }
            else if (tag == "name")
                  setName(e.readElementText());
            else
                  e.unknown();
            }

      if (e.error() != XmlStreamReader::NoError)
            return FileError::FILE_BAD_FORMAT;

      int n = nstaves();
      for (int idx = 0; idx < n; ++idx) {
            Staff* s = _staves[idx];
            int track = idx * VOICES;

            // check barLineSpan
            if (s->barLineSpan() > (n - idx)) {
                  qDebug("read114: invalid bar line span %d (max %d)",
                     s->barLineSpan(), n - idx);
                  s->setBarLineSpan(n - idx);
                  }
            for (auto i : e.clefs(idx)) {
                  int tick = i.first;
                  ClefType clefId = i.second;
                  Measure* m = tick2measure(tick);
                  if (!m)
                        continue;
                  if ((tick == m->tick()) && m->prevMeasure())
                        m = m->prevMeasure();
                  Segment* seg = m->getSegment(Segment::Type::Clef, tick);
                  if (seg->element(track))
                        static_cast<Clef*>(seg->element(track))->setGenerated(false);
                  else {
                        Clef* clef = new Clef(this);
                        clef->setClefType(clefId);
                        clef->setTrack(track);
                        clef->setParent(seg);
                        clef->setGenerated(false);
                        seg->add(clef);
                        }
                  }

            // create missing KeySig
            KeyList* km = s->keyList();
            for (auto i = km->begin(); i != km->end(); ++i) {
                  int tick = i->first;
                  if (tick < 0) {
                        qDebug("read114: Key tick %d", tick);
                        continue;
                        }
                  if (tick == 0 && i->second.key() == Key::C)
                        continue;
                  Measure* m = tick2measure(tick);
                  if (!m)           //empty score
                        break;
                  Segment* seg = m->getSegment(Segment::Type::KeySig, tick);
                  if (seg->element(track))
                        static_cast<KeySig*>(seg->element(track))->setGenerated(false);
                  else {
                        KeySigEvent ke = i->second;
                        KeySig* ks = new KeySig(this);
                        ks->setKeySigEvent(ke);
                        ks->setParent(seg);
                        ks->setTrack(track);
                        ks->setGenerated(false);
                        seg->add(ks);
                        }
                  }
            }

      for (std::pair<int,Spanner*> p : spanner()) {
            Spanner* s = p.second;
            if (s->type() != Element::Type::SLUR) {
                  if (s->type() == Element::Type::VOLTA) {
                        Volta* volta = static_cast<Volta*>(s);
                        volta->setAnchor(Spanner::Anchor::MEASURE);
                        }
                  }

            if (s->type() == Element::Type::OTTAVA
                || s->type() == Element::Type::PEDAL
                || s->type() == Element::Type::TRILL
                || s->type() == Element::Type::TEXTLINE) {
                  qreal yo = 0;
                  if (s->type() == Element::Type::OTTAVA) {
                      // fix ottava position
                      yo = styleS(StyleIdx::ottavaY).val() * spatium();
                      if (s->placement() == Element::Placement::BELOW)
                            yo = -yo + s->staff()->height();
                      }
                  else if (s->type() == Element::Type::PEDAL) {
                        yo = styleS(StyleIdx::pedalY).val() * spatium();
                        }
                  else if (s->type() == Element::Type::TRILL) {
                        yo = styleS(StyleIdx::trillY).val() * spatium();
                        }
                  else if (s->type() == Element::Type::TEXTLINE) {
                        yo = -5.0 * spatium();
                  }
                  if (!s->spannerSegments().isEmpty()) {
                        for (SpannerSegment* seg : s->spannerSegments()) {
                              if (!seg->userOff().isNull())
                                    seg->setUserYoffset(seg->userOff().y() - yo);
                              }
                        }
                  else {
                        s->setUserYoffset(-yo);
                        }
                  }
            }

      connectTies();

      //
      // remove "middle beam" flags from first ChordRest in
      // measure
      //
      for (Measure* m = firstMeasure(); m; m = m->nextMeasure()) {
            int tracks = nstaves() * VOICES;
            bool first = true;
            for (int track = 0; track < tracks; ++track) {
                  for (Segment* s = m->first(); s; s = s->next()) {
                        if (s->segmentType() != Segment::Type::ChordRest)
                              continue;
                        ChordRest* cr = static_cast<ChordRest*>(s->element(track));
                        if (cr) {
                              if(cr->type() == Element::Type::REST) {
                                    Rest* r = static_cast<Rest*>(cr);
                                    if (!r->userOff().isNull()) {
                                          int lineOffset = r->computeLineOffset();
                                          qreal lineDist = r->staff() ? r->staff()->staffType()->lineDistance().val() : 1.0;
                                          r->rUserYoffset() -= (lineOffset * .5 * lineDist * r->spatium());
                                          }
                                    }
                              if(!first) {
                                    switch(cr->beamMode()) {
                                          case Beam::Mode::AUTO:
                                          case Beam::Mode::BEGIN:
                                          case Beam::Mode::END:
                                          case Beam::Mode::NONE:
                                                break;
                                          case Beam::Mode::MID:
                                          case Beam::Mode::BEGIN32:
                                          case Beam::Mode::BEGIN64:
                                                cr->setBeamMode(Beam::Mode::BEGIN);
                                                break;
                                          case Beam::Mode::INVALID:
                                                if (cr->type() == Element::Type::CHORD)
                                                      cr->setBeamMode(Beam::Mode::AUTO);
                                                else
                                                      cr->setBeamMode(Beam::Mode::NONE);
                                                break;
                                          }
                                    first = false;
                                    }
                              }
                        }
                  }
            }
      for (MeasureBase* mb = _measures.first(); mb; mb = mb->next()) {
            if (mb->type() == Element::Type::VBOX) {
                  Box* b  = static_cast<Box*>(mb);
                  qreal y = point(styleS(StyleIdx::staffUpperBorder));
                  b->setBottomGap(y);
                  }
            }

      _fileDivision = MScore::division;

      //
      //    sanity check for barLineSpan and update ottavas
      //
      foreach(Staff* staff, _staves) {
            int barLineSpan = staff->barLineSpan();
            int idx = staffIdx(staff);
            int n = nstaves();
            if (idx + barLineSpan > n) {
                  qDebug("bad span: idx %d  span %d staves %d", idx, barLineSpan, n);
                  staff->setBarLineSpan(n - idx);
                  }
            staff->updateOttava();
            }