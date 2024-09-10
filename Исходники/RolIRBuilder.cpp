void RolIRBuilder::regReg(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicExpression *se;
  smt2lib::smtAstAbstractNode *expr, *op1, *op2;
  uint64 reg1     = this->operands[0].getValue();
  uint32 regSize1 = this->operands[0].getSize();

  /* Create the SMT semantic */
  op1 = ap.buildSymbolicRegOperand(reg1, regSize1);
  /*
   * Note that SMT2-LIB doesn't support expression as rotate's value.
   * The op2 must be the concretization's value.
   */
  op2 = smt2lib::decimal(ap.getRegisterValue(ID_RCX) & 0xff); /* 0xff -> There is only CL available */

  // Final expr
  expr = smt2lib::bvrol(op2, op1);

  /* Create the symbolic expression */
  se = ap.createRegSE(inst, expr, reg1, regSize1);

  /* Apply the taint */
  ap.aluSpreadTaintRegReg(se, reg1, reg1);

  /* Add the symbolic flags expression to the current inst */
  EflagsBuilder::cfRol(inst, se, ap, op2);
  EflagsBuilder::ofRol(inst, se, ap, regSize1, op2);
}