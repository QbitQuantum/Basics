void Ambitus::updateRange()
      {
      if (!segment())
            return;
      Chord* chord;
      int   firstTrack  = track();
      int   lastTrack   = firstTrack + VOICES-1;
      int   pitchTop    = -1000;
      int   pitchBottom = 1000;
      int   tpcTop      = 0;  // Initialized to prevent warning
      int   tpcBottom   = 0;  // Initialized to prevent warning
      int   trk;
      Measure* meas     = segment()->measure();
      Segment* segm     = meas->findSegment(SegmentType::ChordRest, segment()->tick());
      bool     stop     = meas->sectionBreak();
      while (segm) {
            // moved to another measure?
            if (segm->measure() != meas) {
                  // if section break has been found, stop here
                  if (stop)
                        break;
                  // update meas and stop condition
                  meas = segm->measure();
                  stop = meas->sectionBreak();
                  }
            // scan all relevant tracks of this segment for chords
            for (trk = firstTrack; trk <= lastTrack; trk++) {
                  Element* e = segm->element(trk);
                  if (!e || !e->isChord())
                        continue;
                  chord = toChord(e);
                  // update pitch range (with associated tpc's)
                  for (Note* n : chord->notes()) {
                        if (!n->play())         // skip notes which are not to be played
                              continue;
                        int pitch = n->ppitch();
                        if (pitch > pitchTop) {
                              pitchTop = pitch;
                              tpcTop   = n->tpc();
                              }
                        if (pitch < pitchBottom) {
                              pitchBottom = pitch;
                              tpcBottom   = n->tpc();
                              }
                        }
                  }
            segm = segm->nextCR();
            }

      if (pitchTop > -1000) {             // if something has been found, update this
            _topPitch    = pitchTop;
            _bottomPitch = pitchBottom;
            _topTpc      = tpcTop;
            _bottomTpc   = tpcBottom;
            }
      }