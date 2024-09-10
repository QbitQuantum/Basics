FixClientMD::~FixClientMD()
{
  memory->destroy(xpbc);

  CSlib *cs = (CSlib *) lmp->cslib;

  // all-done message to server

  cs->send(-1,0);

  int nfield;
  int *fieldID,*fieldtype,*fieldlen;
  int msgID = cs->recv(nfield,fieldID,fieldtype,fieldlen);

  // clean-up

  delete cs;
  lmp->cslib = NULL;
}