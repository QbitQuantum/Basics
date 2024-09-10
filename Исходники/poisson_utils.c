void minmod2grav_mix(struct Gtype *U1, struct Gtype *U2){
  REAL Dm=U1->d;
  REAL Dp=U2->d;
  REAL beta=1.; // 1 MINBEE 2 SUPERBEE

  if(Dp>0){
    U1->d=FMAX(FMAX(0.,FMIN(beta*Dm,Dp)),FMIN(Dm,beta*Dp));
    U2->d=U1->d;
  }
  else{
    U1->d=FMIN(FMIN(0.,FMAX(beta*Dm,Dp)),FMAX(Dm,beta*Dp));
    U2->d=U1->d;
  }
}