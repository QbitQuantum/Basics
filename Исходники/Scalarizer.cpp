bool Scalarizer::visitSelectInst(SelectInst &SI) {
  VectorType *VT = dyn_cast<VectorType>(SI.getType());
  if (!VT)
    return false;

  unsigned NumElems = VT->getNumElements();
  IRBuilder<> Builder(SI.getParent(), &SI);
  Scatterer Op1 = scatter(&SI, SI.getOperand(1));
  Scatterer Op2 = scatter(&SI, SI.getOperand(2));
  assert(Op1.size() == NumElems && "Mismatched select");
  assert(Op2.size() == NumElems && "Mismatched select");
  ValueVector Res;
  Res.resize(NumElems);

  if (SI.getOperand(0)->getType()->isVectorTy()) {
    Scatterer Op0 = scatter(&SI, SI.getOperand(0));
    assert(Op0.size() == NumElems && "Mismatched select");
    for (unsigned I = 0; I < NumElems; ++I)
      Res[I] = Builder.CreateSelect(Op0[I], Op1[I], Op2[I],
                                    SI.getName() + ".i" + Twine(I));
  } else {
    Value *Op0 = SI.getOperand(0);
    for (unsigned I = 0; I < NumElems; ++I)
      Res[I] = Builder.CreateSelect(Op0, Op1[I], Op2[I],
                                    SI.getName() + ".i" + Twine(I));
  }
  gather(&SI, Res);
  return true;
}