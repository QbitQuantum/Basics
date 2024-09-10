/* Funkcja rectinrect sprawdza, czy prostokat r1 zawiera sie w prostokacie r2.
   Sprawdza, czy punkty ll i ur prostokata r1 naleza do r2, jesli tak to r1 zawiera sie w r2 */ 
int rectinrect(struct rect r1, struct rect r2){

  if(ptinrect(r1.ll,r2) == 1 && ptinrect(r1.ur,r2)==1) {return 1;}
  else return 0;
}