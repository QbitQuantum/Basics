void ScopeI::wakeupRaw(int) {
  //  dbx("wakeup raw");
  try {
    int r = sleeper->poll();
    switch (r) {
    case Wakeup::Trig: // fall through to Poll stuff.
      if (seentrig) {
	nexttrig = rawsf->aux()->trig.t_latest  + rawsf->first();
	seentrig = false;
      }
    case Wakeup::Poll:
    {
      if (!rawpoll) {
	rawpoll=true;
	setStatus(rawstatus, Wakeup::Poll, rawpoll, rawsf);
      }
      if (freezeflag->isChecked())
	break;
      timeref_t sftime = rawsf->latest();
      timeref_t next;
      if (trigflag->isChecked()) {
	next = nexttrig + scopes->period() - pretrig->value()*FREQKHZ;
	if (next > sftime || next==scopes->latest())
	  break;
	seentrig = true;
      } else {
	timeref_t last = scopes->latest();
	next = last + scopes->period();
	if (next > sftime)
	  break;
	if (sftime - next > MAXLAG)
	  next = sftime; // lose some (partial) frames
	//      sdbx("Scope: refresh %.3f",next/25000.0);
      }
      scopes->refresh(next);
      timeref_t ival = next - scopes->first();
      time->setText(Sprintf("%.3f s",ival/1000./FREQKHZ).c_str());
    } break;
    case Wakeup::Start: {
      freeze(false);
      freezeflag->setChecked(false);
      rawpoll=false;
      setStatus(rawstatus, Wakeup::Start, rawpoll, rawsf);
      copybasics();
      scopes->restart();
      nexttrig = scopes->latest(); seentrig = true;
    } break;
    case Wakeup::Stop:
      rawpoll=false;
      setStatus(rawstatus, Wakeup::Stop, rawpoll, rawsf);
      break;
    default: break;
    }
  } catch (Expectable const &e) {
    // probably EOF
    e.report();
    reopen_raw();
  }
}