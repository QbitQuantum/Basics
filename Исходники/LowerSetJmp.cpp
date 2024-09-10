// visitReturnInst - We want to destroy the setjmp map upon exit from the
// function.
void LowerSetJmp::visitReturnInst(ReturnInst &RI) {
  Function* Func = RI.getParent()->getParent();
  CallInst::Create(DestroySJMap, GetSetJmpMap(Func), "", &RI);
}