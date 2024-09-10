bool AsyncTimeRemaining::createFrame(OutputFrame::Ptr f) {
  f->setType(ft02_Time_Remaining);
  f->packInt(rtime);
  if(f->getVersion() >= fv0_4){
    f->packInt(why); //reason
    f->packInt(Game::getGame()->getTurnNumber());
    f->packString(Game::getGame()->getTurnName());
  }
  return true;
}