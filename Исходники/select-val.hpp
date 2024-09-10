 forceinline int
 ValSplitMin<View>::val(Space&, View x) const {
   return (x.width() == 2) ? x.min() : ((x.min()+x.max()) / 2);
 }