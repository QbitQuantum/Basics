void sat_communication_f(crv::Channel<int>& s, crv::Channel<int>& t)
{
  t.send(1);
  crv::Internal<int> r(s.recv());
  s.send(r);
}