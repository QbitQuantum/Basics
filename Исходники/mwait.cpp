void fun() {

  _mm_monitor(lock,0,0);
  _mm_mwait(0,0);


  std::cout << "hi " << lock[0] << std::endl;

}