/// Create a new event loop context
StatusCode EventSelector::createContext(Context*& refpCtxt) const
{
  // Max event is zero. Return begin = end
  refpCtxt = 0;
  if ( m_firstEvent < 0 ) {
    MsgStream log(msgSvc(), name());
    log << MSG::ERROR  << "First Event = " << m_firstEvent << " not valid" << endmsg;
    log << MSG::ERROR  << "It should be > 0 " << endmsg;
    return StatusCode::FAILURE;    // if failure => iterators = end();
  }
  EvtSelectorContext* ctxt = new EvtSelectorContext(this);
  ctxt->set(0, -1, 0, 0);
  firstOfNextStream(true, *ctxt).ignore();
  refpCtxt = ctxt;
  long nskip = m_firstEvent;
  while( --nskip > 0 )    {
    StatusCode sc = next(*refpCtxt);
    if ( sc.isFailure() ) {
      MsgStream log(msgSvc(), name());
      log << MSG::ERROR << " createContext() failed to start with event number "
          << m_firstEvent << endmsg;
      releaseContext(refpCtxt);
      refpCtxt = 0;
      return StatusCode::FAILURE;
    }
  }
  return StatusCode::SUCCESS;
}