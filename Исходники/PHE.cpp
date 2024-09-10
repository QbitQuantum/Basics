/**************************
//Paillier HE system
//len: length of params p,q
**************************/
void Paillier(int len=512){
  ZZ n, n2, p, q, g, lamda;
  ZZ p1, q1, p1q1;
  ZZ miu;
  
  ZZ m1, m2;
  ZZ BSm, HEm; //baseline and HE result
  ZZ c, c1, c2, cm1, cm2, r;

  //key gen
  start = std::clock();

  GenPrime(p, len);
  GenPrime(q, len);
  mul(n, p, q);
  mul(n2, n, n);

  sub(p1,p,1);
  sub(q1,q,1);
  GCD(lamda,p1,q1);
  mul(p1q1,p1,q1);
  div(lamda, p1q1, lamda);

  RandomBnd(g, n2);

  PowerMod(miu,g,lamda,n2);
  sub(miu, miu, 1);
  div(miu,miu,n); //should add 1?
  InvMod(miu, miu, n);
  
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  cout<<"Pailler Setup:"<< duration <<'\n';

  //Enc
  start = std::clock();
  RandomBnd(m1,n);
  RandomBnd(m2,n);

  RandomBnd(r,n); //enc m1
  PowerMod(c1, g,m1,n2);
  PowerMod(c2, r,n,n2);
  MulMod(cm1, c1,c2, n2);

  RandomBnd(r,n); //enc m2
  PowerMod(c1, g,m2,n2);
  PowerMod(c2, r,n,n2);
  MulMod(cm2, c1,c2, n2);

  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  cout<<"Pailler Enc:"<< duration/2 <<'\n';

  //Evaluation
  start = std::clock();
  c=cm1;
  for(int i=0; i<TIMES; i++)
  	MulMod(c,c,cm2,n2);
  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  cout<<"Pailler Eval:"<< duration <<'\n';

  //c=cm2;
  //Dec  
  start = std::clock();
  PowerMod(c,c,lamda,n2);
  sub(c,c,1);
  div(c,c,n); //should add 1?
  MulMod(HEm, c, miu, n);  

  duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
  cout<<"Pailler Dec:"<< duration <<'\n';

  //baseline
  BSm=m1;
  for(int i=0; i<TIMES; i++)
  	AddMod(BSm,BSm,m2,n);

  assert(BSm==HEm);
}