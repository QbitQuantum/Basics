void FreezeInfo::scrollTo(int dt_ms) {
  timeref_t endtime = t0 + (dt_ms+width_ms)*FREQKHZ;
  sdbx("freezeinfo scrollto: %i - endtime=%Li",dt_ms,endtime);
  backend->refresh(endtime);
  timeref_t ival = endtime - backend->first();
  timereport->setText(Sprintf("%.3f s",ival/1000./FREQKHZ).c_str());
  sdbx("freezeinfo scrollto: refresh done");
}