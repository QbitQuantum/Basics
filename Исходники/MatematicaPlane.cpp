int Piano::Impact(Vettore *Pos,Vettore *Vel) {
  double Dist = Distance(Pos);
  if(Dist > Rad) return 0;
  Vettore PosS = ProjOnSurf(Pos);
  if(!IsOnSurf(&PosS)) return 0;
  Vettore Vel1 = Reflect(Vel);
  Vel->Copy(&Vel1);
}