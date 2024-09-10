static bool CountBeat(FrameT *frame) {
  static int lastFrame = 0;

  float lf = lastFrame / DemoBeat;
  float tf = frame->number / DemoBeat;
  float li, ti;

  lf = modff(lf, &li);
  tf = modff(tf, &ti);

  lastFrame = frame->number;

  return li < ti;
}