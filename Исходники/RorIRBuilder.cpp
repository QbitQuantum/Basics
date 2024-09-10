void RorIRBuilder::memReg(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *op1, *op2;
  auto memSize = this->operands[0].getMem().getSize();
  auto mem = this->operands[0].getMem();

  /* Create the SMT semantic */
  op1 = ap.buildSymbolicMemOperand(mem, memSize);
  /*
   * Note that SMT2-LIB doesn't support expression as rotate's value.
   * The op2 must be the concretization's value.
   */
  op2 = smt2lib::decimal(ap.getRegisterValue(ID_TMP_RCX) & 0xff); /* 0xff -> There is only CL available */

  // Final expr
  expr = smt2lib::bvror(op2, op1);

  /* Create the symbolic expression */
  se = ap.createMemSE(inst, expr, mem, memSize);

  /* Apply the taint */
  ap.aluSpreadTaintMemMem(se, mem, mem, memSize);

  /* Add the symbolic flags expression to the current inst */
  EflagsBuilder::cfRor(inst, se, ap, memSize, op2);
  EflagsBuilder::ofRor(inst, se, ap, memSize, op2);
}