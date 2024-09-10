void SocSystem_Analytical::getProcess(arr& A,arr& a,arr& B){
  uint N=x.N;
  A.setDiag(1.,N);
  B.setDiag(1.,N);
  a.resize(N); a.setZero();
}