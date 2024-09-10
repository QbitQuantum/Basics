void MoveAnimation::animate() {
  const int sleepTime = 15;
  const int n = (int)size();
  beginPaint();
  for(bool cont = true; cont;) {
    for(int i = n; i--;) (*this)[i]->paint();
    endPaint();
    if(sleepTime) Sleep(sleepTime);
    cont = false;
    beginPaint();
    for(int i = 0; i < n; i++) {
      (*this)[i]->unpaint();
      cont |= (*this)[i]->step();
    }
  }
  endPaint();
}