 forceinline double
 MeritFunction<View>::operator ()(const Space& home, View x, int i) {
   typename View::VarType y(x.varimp());
   return f(home,y,i);
 }