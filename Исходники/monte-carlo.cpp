double ran(){
  //<<<<<<< HEAD
  MTRand random;
  random.seed();
  return random.rand();
  // return rand()/double(RAND_MAX);
  //=======
  static MTRand my_mtrand;
  return my_mtrand.randExc(); // which is the range of [0,1)
  //>>>>>>> 2511a06ab322dcea9f3f70080c443d0938562932
}