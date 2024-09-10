 //Point intersection of two lines
  Point meet( const Line& la, const Line& lb){
     Line r = la.reflect(lb);
     Line r2 = (la - r.unit()).unit();
     Point pori = Flat::loc(r2, Ori(1), false);
     Point tp = pori.re( lb ); 
     return ( ( (tp / tp[3]) + pori)/2.0 ).null(); 
   }