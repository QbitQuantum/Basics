void printSize(ostream &os,const Size &v) {
  printFloat(os,"h ",v.getW());
  printFloat(os,"w ",v.getH());
  printFloat(os,"d ",v.getD());
}