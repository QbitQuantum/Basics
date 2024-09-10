void GetFrictionConePlanes(const ContactFormation& s,int nFrictionConeEdges,SparseMatrix& A)
{
  int nc=NumContactPoints(s);
  A.resize(nFrictionConeEdges*nc,nc*3);
  A.setZero();

  int m=0;
  int p=0;
  for(size_t i=0;i<s.contacts.size();i++) {
    const vector<ContactPoint>& h=s.contacts[i];
    for(size_t j=0;j<h.size();j++,p++) {
      const ContactPoint& pt=h[j];
      FrictionConePolygon fc;
      fc.set(nFrictionConeEdges,pt.n,pt.kFriction);
      for(int i=0;i<nFrictionConeEdges;i++,m++) {
	A(m,p*3) = -fc.planes[i].x;
	A(m,p*3+1) = -fc.planes[i].y;
	A(m,p*3+2) = -fc.planes[i].z;
      }
    }
  }
}