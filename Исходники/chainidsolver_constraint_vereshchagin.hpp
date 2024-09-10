 segment_info(unsigned int nc) {
     E.resize(6, nc);
     E_tilde.resize(6, nc);
     G.resize(nc);
     M.resize(nc, nc);
     EZ.resize(nc);
     E.setZero();
     E_tilde.setZero();
     M.setZero();
     G.setZero();
     EZ.setZero();
 };