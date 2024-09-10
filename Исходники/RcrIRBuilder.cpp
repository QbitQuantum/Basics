void RcrIRBuilder::regReg(AnalysisProcessor &ap, Inst &inst) const {
  SymbolicExpression *se1, *se2;
  smt2lib::smtAstAbstractNode *expr, *op1, *op2, *cf, *res;
  uint64 reg1     = this->operands[0].getValue();
  uint32 regSize1 = this->operands[0].getSize();

  /* Create the SMT semantic */
  cf = ap.buildSymbolicFlagOperand(ID_CF);
  op1 = ap.buildSymbolicRegOperand(reg1, regSize1);
  /*
   * Note that SMT2-LIB doesn't support expression as rotate's value.
   * The op2 must be the concretization's value.
   */
  op2 = smt2lib::decimal(ap.getRegisterValue(ID_RCX) & 0xff); /* 0xff -> There is only CL available */

  /* Rcl expression */
  expr = smt2lib::bvror(
            op2,
            smt2lib::concat(cf, op1)
          );

  /* Temporary extended expression */
  se1 = ap.createSE(inst, expr, "Temporary Extended Expression");

  /* Apply the taint */
  ap.assignmentSpreadTaintExprReg(se1, reg1);

  /* Result expression */
  res = smt2lib::extract((regSize1 * REG_SIZE) - 1, 0, expr);

  /* Create the symbolic expression */
  se2 = ap.createRegSE(inst, res, reg1, regSize1);

  /* Apply the taint */
  ap.aluSpreadTaintRegReg(se2, reg1, reg1);

  /* Add the symbolic flags expression to the current inst */
  EflagsBuilder::cfRcl(inst, se1, ap, regSize1, op2); /* Same as RCL */
  EflagsBuilder::ofRor(inst, se2, ap, regSize1, op2); /* Same as ROR */
}