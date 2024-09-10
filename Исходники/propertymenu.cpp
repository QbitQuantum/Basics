void ScoreView::elementPropertyAction(const QString& cmd, Element* e)
      {
      if (cmd == "a-props") {
            ArticulationProperties rp(static_cast<Articulation*>(e));
            rp.exec();
            }
      else if (cmd == "b-props") {
            Bend* bend = static_cast<Bend*>(e);
            BendProperties bp(bend, 0);
            if (bp.exec())
                  score()->undo(new ChangeBend(bend, bp.points()));
            }
      else if (cmd == "f-props") {
            BoxProperties vp(static_cast<Box*>(e), 0);
            vp.exec();
            }
      else if (cmd == "measure-props") {
            MeasureProperties vp(static_cast<Note*>(e)->chord()->segment()->measure());
            vp.exec();
            }
      else if (cmd == "frame-text") {
            Text* s = new Text(score());
//            s->setSubtype(TEXT_FRAME);
            s->setTextStyleType(TEXT_STYLE_FRAME);
            s->setParent(e);
            score()->undoAddElement(s);
            score()->select(s, SELECT_SINGLE, 0);
            startEdit(s);
            score()->setLayoutAll(true);
            }
      else if (cmd == "picture") {
            mscore->addImage(score(), static_cast<HBox*>(e));
            }
      else if (cmd == "frame-text") {
            Text* t = new Text(score());
            t->setTextStyleType(TEXT_STYLE_FRAME);
            t->setParent(e);
            score()->undoAddElement(t);
            score()->select(t, SELECT_SINGLE, 0);
            startEdit(t);
            }
      else if (cmd == "title-text") {
            Text* t = new Text(score());
            t->setTextStyleType(TEXT_STYLE_TITLE);
            t->setParent(e);
            score()->undoAddElement(t);
            score()->select(t, SELECT_SINGLE, 0);
            startEdit(t);
            }
      else if (cmd == "subtitle-text") {
            Text* t = new Text(score());
            t->setTextStyleType(TEXT_STYLE_SUBTITLE);
            t->setParent(e);
            score()->undoAddElement(t);
            score()->select(t, SELECT_SINGLE, 0);
            startEdit(t);
            }
      else if (cmd == "composer-text") {
            Text* t = new Text(score());
            t->setTextStyleType(TEXT_STYLE_COMPOSER);
            t->setParent(e);
            score()->undoAddElement(t);
            score()->select(t, SELECT_SINGLE, 0);
            startEdit(t);
            }
      else if (cmd == "poet-text") {
            Text* t = new Text(score());
            t->setTextStyleType(TEXT_STYLE_POET);
            t->setParent(e);
            score()->undoAddElement(t);
            score()->select(t, SELECT_SINGLE, 0);
            startEdit(t);
            }
      else if (cmd == "insert-hbox") {
            HBox* s = new HBox(score());
            double w = width() - s->leftMargin() * MScore::DPMM - s->rightMargin() * MScore::DPMM;
            s->setBoxWidth(Spatium(w / s->spatium()));
            s->setParent(e);
            score()->undoAddElement(s);
            score()->select(s, SELECT_SINGLE, 0);
            startEdit(s);
            }
      else if (cmd == "picture")
            mscore->addImage(score(), e);
      else if (cmd == "tuplet-props") {
            Tuplet* tuplet;
            QList<Element*> el;
            if (e->type() == NOTE) {
                  tuplet = static_cast<Note*>(e)->chord()->tuplet();
                  el.append(tuplet);
                  }
            else if (e->isChordRest()) {
                  tuplet = static_cast<ChordRest*>(e)->tuplet();
                  el.append(tuplet);
                  }
            else {
                  tuplet = static_cast<Tuplet*>(e);
                  el.append(score()->selection().elements());      // apply to all selected tuplets
                  }
            TupletProperties vp(tuplet);
            if (vp.exec()) {
                  int bracketType = vp.bracketType();
                  int numberType  = vp.numberType();
                  foreach(Element* e, el) {
                        if (e->type() == TUPLET) {
                              Tuplet* tuplet = static_cast<Tuplet*>(e);
                              if (bracketType != tuplet->bracketType())
                                    score()->undoChangeProperty(tuplet, P_BRACKET_TYPE, bracketType);
                              if (numberType != tuplet->numberType())
                                    score()->undoChangeProperty(tuplet, P_NUMBER_TYPE, numberType);
                              }
                        }
                  }