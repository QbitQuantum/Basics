// process a single acquisition
int RtRoiDifference::process(ACE_Message_Block *mb) {
  ACE_TRACE(("RtRoiDifference::process"));

  RtStreamMessage *msg = (RtStreamMessage*) mb->rd_ptr();

  cout << "PROCESSING " << endl;

  // find the data with the right data IDs
  RtActivation *posact
      = (RtActivation*) msg->getData(posRoiModuleID,
                                     posRoiDataName,
                                     posRoiRoiID);
  RtActivation *negact
      = (RtActivation*) msg->getData(negRoiModuleID,
                                     negRoiDataName,
                                     negRoiRoiID);

  double p = 0;
  if(posact != NULL) {
    p = posact->getPixel(0);
  }

  double n = 0;
  if(negact != NULL) {
    n = negact->getPixel(0);
  }

  // create a one element activation image
  RtActivation *diff = new RtActivation(1);

  // setup the data id
  diff->getDataID().setFromInputData(*posact,*this);
  diff->getDataID().setDataName(NAME_ROIDIFF);
  diff->getDataID().setRoiID(posRoiRoiID + "-" + negRoiRoiID);


  // compute the difference
  diff->setPixel(0,  p - n);

  setResult(msg, diff);

  return 0;
}