void dccpktq_clear(DCCPktQ *q) {
  DCCPktElem *e;
  cli();
  while((e = q->read) != NULL) remove(q, e);
  sei();
}