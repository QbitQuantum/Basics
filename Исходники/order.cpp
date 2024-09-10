void Order::createFrame(OutputFrame::Ptr f, int pos)
{
  f->setType(ft02_Order);
  if(f->getVersion() <= fv0_3){
    f->packInt(Game::getGame()->getOrderManager()->getOrderQueue(orderqueueid)->getObjectId());
  }else{
    f->packInt(orderqueueid);
  }
  f->packInt(pos);
  f->packInt(type);
  f->packInt(turns);
  f->packIdMap(resources);
  std::for_each( parameters.begin(), parameters.end(), boost::bind( &OrderParameter::pack, _1, f ) );
}