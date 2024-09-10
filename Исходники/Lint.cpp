void Lint::visitReturnInst(ReturnInst &I) {
  Function *F = I.getParent()->getParent();
  Assert1(!F->doesNotReturn(),
          "Unusual: Return statement in function with noreturn attribute",
          &I);
}