void AMDGPUAnnotateUniformValues::visitBranchInst(BranchInst &I) {
  if (I.isUnconditional())
    return;

  Value *Cond = I.getCondition();
  if (!DA->isUniform(Cond))
    return;

  setUniformMetadata(I.getParent()->getTerminator());
}