//---------------------------------------------------------
//   oscColorNote
//---------------------------------------------------------
void MuseScore::oscColorNote(QVariantList list)
      {
      qDebug() << list;
      if(!cs)
            return;
      if (list.length() != 2 && list.length() != 3)
            return;
      int tick;
      int pitch;
      QColor noteColor("red"); //default to red
      bool ok;
      tick = list[0].toInt(&ok);
      if (!ok)
            return;
      pitch = list[1].toInt(&ok);
      if (!ok)
            return;
      if(list.length() == 3 && list[2].canConvert(QVariant::String)) {
            QColor color(list[2].toString());
            if(color.isValid())
                  noteColor = color;
            }

      Measure* measure = cs->tick2measure(tick);
      if(!measure)
            return;
      Segment* s = measure->findSegment(Segment::SegChordRest, tick);
      if (!s)
            return;
      //get all chords in segment...
      int n = cs->nstaves() * VOICES;
      for (int i = 0; i < n; i++) {
            Element* e = s->element(i);
            if (e && e->isChordRest()) {
                  ChordRest* cr = static_cast<ChordRest*>(e);
                  if(cr->type() == Element::CHORD) {
                        Chord* chord = static_cast<Chord*>(cr);
                        for (int idx = 0; idx < chord->notes().length(); idx++) {
                              Note* note = chord->notes()[idx];
                              if (note->pitch() == pitch) {
                                    cs->startCmd();
                                    cs->undo(new ChangeProperty(note, P_COLOR, noteColor));
                                    cs->endCmd();
                                    cs->end();
                                    return;
                                    }
                              }
                        }
                  }
            }
      }