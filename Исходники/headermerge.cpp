 bool operator()(Align const & a1, Align const & a2) const
 {
     if (a1.getStart() == a2.getStart())
         //return (&a1 > &a2);  // just arbitrarily pick the one with higher pointer
         return a1.getName() > a2.getName();
     else
         return (a1.getStart() > a2.getStart());
 }