void MeasureBase::undoSetBreak(bool v, LayoutBreak::Type type)
      {
      switch (type) {
            case LayoutBreak::LINE:
                  if (lineBreak() == v)
                        return;
                  setLineBreak(v);
                  break;
            case LayoutBreak::PAGE:
                  if (pageBreak() == v)
                        return;
                  if (v && lineBreak())
                        setLineBreak(false);
                  setPageBreak(v);
                  break;
            case LayoutBreak::SECTION:
                  if (sectionBreak() == v)
                        return;
                  if (v && lineBreak())
                        setLineBreak(false);
                  setSectionBreak(v);
                  break;
            case LayoutBreak::NOBREAK:
                  if (noBreak() == v)
                        return;
                  if (v) {
                        setLineBreak(false);
                        setPageBreak(false);
                        setSectionBreak(false);
                        }
                  setNoBreak(v);
                  break;
            }

      if (v) {
            LayoutBreak* lb = new LayoutBreak(score());
            lb->setLayoutBreakType(type);
            lb->setTrack(-1);       // this are system elements
            lb->setParent(this);
            score()->undoAddElement(lb);
            }
      cleanupLayoutBreaks(true);
      }