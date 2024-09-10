void MidiInstrument::read(Xml& xml)
      {
      bool ok;
      int base = 10;
      _nullvalue = -1;
      for (;;) {
            Xml::Token token = xml.parse();
            const QString& tag = xml.s1();
            switch (token) {
                  case Xml::Error:
                  case Xml::End:
                        return;
                  case Xml::TagStart:
                        if (tag == "Patch") {
                              Patch* patch = new Patch;
                              patch->read(xml);
                              if (pg.empty()) {
                                    PatchGroup* p = new PatchGroup;
                                    p->patches.push_back(patch);
                                    pg.push_back(p);
                                    }
                              else
                                    pg[0]->patches.push_back(patch);
                              }
                        else if (tag == "PatchGroup") {
                              PatchGroup* p = new PatchGroup;
                              p->read(xml);
                              pg.push_back(p);
                              }
                        else if (tag == "Controller") {
                              MidiController* mc = new MidiController();
                              mc->read(xml);
                              // Added by Tim. Copied from muse 2.
                              //
                              // HACK: make predefined "Program" controller overloadable
                              //
                              if (mc->name() == "Program") {
                                    for (iMidiController i = _controller->begin(); i != _controller->end(); ++i) {
                                          if (i->second->name() == mc->name()) {
                                                delete i->second;
                                                _controller->erase(i);
                                                break;
                                                }
                                          }
                                    }
                                    
                              _controller->add(mc);
                              }
                        else if (tag == "Drummaps") {
                              readDrummaps(xml);
                              }
                        else if (tag == "Init")
                              readEventList(xml, _midiInit, "Init");
                        else if (tag == "Reset")
                              readEventList(xml, _midiReset, "Reset");
                        else if (tag == "State")
                              readEventList(xml, _midiState, "State");
                        else if (tag == "InitScript") {
                              if (_initScript)
                                    delete _initScript;
                              QByteArray ba = xml.parse1().toLatin1();
                              const char* istr = ba.constData();
                              int len = ba.length() +1;
                              if (len > 1) {
                                    _initScript = new char[len];
                                    memcpy(_initScript, istr, len);
                                    }
                              }
                        else if (tag == "SysEx") {
                              SysEx* se = new SysEx;
                              if(!se->read(xml))
                              {
                                delete se;
                                printf("MidiInstrument::read():SysEx: reading sysex failed\n");
                              }
                              else
                                _sysex.append(se);
                              }
                        else
                              xml.unknown("MidiInstrument");
                        break;
                  case Xml::Attribut:
                        if (tag == "name")
                              setIName(xml.s2());
                        else if(tag == "nullparam") {
                              _nullvalue = xml.s2().toInt(&ok, base);
                        }
                        break;
                  case Xml::TagEnd:
                        if (tag == "MidiInstrument")
                              return;
                  default:
                        break;
                  }
            }
      }